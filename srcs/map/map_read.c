/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 09:33:42 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/30 13:26:09 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <error.h>
#include <map.h>
#include <get_next_line.h>
#include <string_utils.h>

int	parse_params(t_map *map, char *line);
int	parse_field_line(t_map *map, char *line, int *player_count);
int	valid_field(t_map *map, int player_count);
int	skip_empty_lines(int fd, char **line);

static void	map_fatal(t_map *map, int errnum)
{
	map_free(map);
	fatal(errnum);
}

static int	check_params(t_map *map)
{
	return (map->no_path && map->so_path && map->we_path
		&& map->ea_path && map->floor_color != -1 && map->cell_color != -1);
}

static int	read_field(t_map *map, int fd)
{
	char	*line;
	int		stat;
	int		player_count;

	stat = skip_empty_lines(fd, &line);
	if (stat)
		return (stat);
	stat = 1;
	player_count = 0;
	while (stat > 0)
	{
		stat = parse_field_line(map, line, &player_count);
		if (stat)
		{
			free(line);
			return (stat);
		}
		stat = get_next_line(fd, &line);
	}
	if (!stat && is_empty(line))
		free(line);
	if (stat)
		return (stat);
	return (valid_field(map, player_count));
}

static int	read_params(t_map *map, int fd)
{
	char	*line;
	int		read_stat;
	int		parse_stat;

	parse_stat = 0;
	read_stat = 1;
	while (read_stat && !parse_stat && !check_params(map))
	{
		read_stat = get_next_line(fd, &line);
		if (read_stat == -1)
			return (-1);
		if (!is_empty(line))
			parse_stat = parse_params(map, line);
		free(line);
	}
	if (parse_stat)
		return (parse_stat);
	if (!check_params(map))
		return (ENOPARAM);
	return (0);
}

void	map_read_from_file(t_map *map, char *path)
{
	int		parse_stat;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		map_fatal(map, -1);
	parse_stat = read_params(map, fd);
	if (!parse_stat)
		parse_stat = read_field(map, fd);
	close(fd);
	if (parse_stat)
		map_fatal(map, parse_stat);
	fd = -1;
	map->field.width = 0;
	while (++fd < map->field.size)
	{
		parse_stat = mstrlen(map->field.arr[fd]);
		if (map->field.width < parse_stat)
			map->field.width = parse_stat;
	}
}
