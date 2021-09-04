/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 08:48:22 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/26 13:41:21 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_field
{
	char	**arr;
	int		size;
	int		capacity;
	int		width;
}	t_field;

typedef struct s_map
{
	t_field	field;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		cell_color;
}	t_map;

int		map_init(t_map *map);
int		map_add_line(t_map *map, char *line);
void	map_free(t_map *map);

void	map_read_from_file(t_map *map, char *path);

#endif	/*MAP_H*/
