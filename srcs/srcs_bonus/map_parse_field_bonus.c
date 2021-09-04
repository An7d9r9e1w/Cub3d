/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_field_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/30 13:52:51 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 11:02:27 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <error.h>
#include <map.h>
#include <get_next_line.h>
#include <string_utils.h>

static int	only_ones(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '1')
			return (0);
		++line;
	}
	return (1);
}

static int	valid_line(char *ul, char *l, char *dl, int *lens)
{
	int	len;
	int	i;

	len = lens[1] - 1;
	i = 0;
	while (i < len && l[i] == ' ')
		++i;
	while (len > i && l[len] == ' ')
		--len;
	if (l[i] != '1' || l[len] != '1')
		return (EUCLSFIELD);
	while (++i < len)
	{
		if ((l[i] != '1' && l[i] != ' ' && (l[i - 1] == ' ' || l[i + 1] == ' '
					|| i > lens[0] || ul[i - 1] == ' ' || i >= lens[0]
					|| ul[i] == ' ' || (i + 1) >= lens[0] || ul[i + 1] == ' '
					|| i > lens[2] || dl[i - 1] == ' ' || i >= lens[2]
					|| dl[i] == ' ' || (i + 1) >= lens[2] || dl[i + 1] == ' ')))
			return (EUCLSFIELD);
		if ((l[i] == '3' && (l[i - 1] != '1' || l[i + 1] != '1')
				&& (i >= lens[0] || ul[i] != '1' || i >= lens[2]
					|| dl[i] != '1')))
			return (EDOOR);
	}
	return (0);
}

int	valid_field(t_map *map, int player_count)
{
	t_field	*field;
	int		len[3];
	int		i;
	int		stat;

	if (!player_count)
		return (EPLR);
	field = &map->field;
	if (field->size < 3 || !only_ones(field->arr[0])
		|| !only_ones(field->arr[field->size - 1]))
		return (EUCLSFIELD);
	len[1] = mstrlen(field->arr[0]);
	len[2] = mstrlen(field->arr[1]);
	i = 1;
	stat = 0;
	while (!stat && ++i < field->size)
	{
		len[0] = len[1];
		len[1] = len[2];
		len[2] = mstrlen(field->arr[i]);
		stat = valid_line(field->arr[i - 2], field->arr[i - 1],
				field->arr[i], len);
	}
	return (stat);
}

int	skip_empty_lines(int fd, char **line)
{
	int		read_stat;

	read_stat = get_next_line(fd, line);
	while (read_stat == 1 && is_empty(*line))
	{
		free(*line);
		read_stat = get_next_line(fd, line);
	}
	if (read_stat == -1)
		return (-1);
	if (is_empty(*line))
	{
		free(*line);
		return (ENOFIELD);
	}
	return (0);
}

int	parse_field_line(t_map *map, char *line, int *player_count)
{
	const char	*begin = line;
	int			count;

	count = 0;
	while (*line)
	{
		if (*line == 'N' || *line == 'S' || *line == 'E' || *line == 'W')
			++count;
		else if (*line != ' ' && *line != '0' && *line != '1'
			&& *line != '2' && *line != '3')
			return (EINVFIELD);
		++line;
	}
	*player_count += count;
	if (*player_count > 1)
		return (EPLR);
	if (map_add_line(map, (char *)begin) == -1)
		return (-1);
	return (0);
}
