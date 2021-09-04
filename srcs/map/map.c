/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 08:48:22 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/01 09:46:35 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <error.h>
#include <map.h>

#define FIELD_CAPACITY 8

static int	field_realloc(t_field *field)
{
	char	**arr;
	int		i;

	field->capacity <<= 1;
	arr = malloc(sizeof(void *) * field->capacity);
	if (!arr)
		return (-1);
	i = -1;
	while (++i < field->size)
		arr[i] = field->arr[i];
	free(field->arr);
	field->arr = arr;
	return (0);
}

static void	field_free(t_map *map)
{
	char	**tmp;
	int		i;

	tmp = map->field.arr;
	i = map->field.size;
	while (i--)
		free(*tmp++);
	free(map->field.arr);
	map->field.size = 0;
}

void	map_free(t_map *map)
{
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);
	field_free(map);
}

int	map_add_line(t_map *map, char *line)
{
	t_field	*field;

	if (!line)
		return (-1);
	field = &map->field;
	if (field->size + 1 > field->capacity && field_realloc(field) == -1)
	{
		free(line);
		field_free(map);
		return (-1);
	}
	field->arr[field->size++] = line;
	return (0);
}

int	map_init(t_map *map)
{
	map->field.arr = malloc(sizeof(void *) * FIELD_CAPACITY);
	if (!map->field.arr)
		return (-1);
	map->field.size = 0;
	map->field.capacity = FIELD_CAPACITY;
	map->no_path = NULL;
	map->so_path = NULL;
	map->we_path = NULL;
	map->ea_path = NULL;
	map->floor_color = -1;
	map->cell_color = -1;
	return (0);
}
