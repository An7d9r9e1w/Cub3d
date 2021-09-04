/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 09:33:42 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/18 10:22:06 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <error.h>
#include <map.h>
#include <string_utils.h>
#include <char_checkers.h>
#include <color.h>

static int	parse_channel(char **line)
{
	char	*str;
	int		color;

	str = *line;
	color = 0;
	if (*str >= '1' && *str <= '9')
	{
		while (*str >= '0' && *str <= '9' && color <= 255)
			color = color * 10 + *str++ - '0';
	}
	else if (*str == '0')
		++str;
	else
		return (-1);
	*line = str + (*str == ',');
	if (color > 255)
		return (-1);
	return (color);
}

static int	parse_color(int *color, char *line)
{
	int	channels[3];
	int	i;

	if (*color != -1)
		return (EDUPPARAM);
	line = skip_spaces(line + 1);
	i = -1;
	channels[0] = -1;
	channels[1] = -1;
	channels[2] = -1;
	while (*line && ++i < 3)
		channels[i] = parse_channel(&line);
	if (channels[0] == -1 || channels[1] == -1 || channels[2] == -1
		|| (*line && !is_space(*line)))
		return (EINVCOLOR);
	*color = get_color(channels[0], channels[1], channels[2], 0);
	return (0);
}

static int	parse_path(char **path, char *line)
{
	if (*path)
		return (EDUPPARAM);
	*path = trim(line + 3);
	if (!*path)
		return (-1);
	if (is_empty(*path))
		return (EEMPTYPARAM);
	return (0);
}

int	parse_params(t_map *map, char *line)
{
	if (!mstrncmp(line, "NO", 2) && is_space(line[2]))
		return (parse_path(&map->no_path, line));
	else if (!mstrncmp(line, "SO", 2) && is_space(line[2]))
		return (parse_path(&map->so_path, line));
	else if (!mstrncmp(line, "WE", 2) && is_space(line[2]))
		return (parse_path(&map->we_path, line));
	else if (!mstrncmp(line, "EA", 2) && is_space(line[2]))
		return (parse_path(&map->ea_path, line));
	else if (!mstrncmp(line, "F", 1) && is_space(line[1]))
		return (parse_color(&map->floor_color, line));
	else if (!mstrncmp(line, "C", 1) && is_space(line[1]))
		return (parse_color(&map->cell_color, line));
	return (EINVPARAM);
}
