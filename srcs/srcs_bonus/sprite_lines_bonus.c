/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_lines_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 09:21:16 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/31 10:03:41 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <sprite_lines_bonus.h>

int	init_sprite_lines(t_sprite_lines *sls, int capacity)
{
	if (capacity <= 0)
		return (-1);
	sls->arr = malloc(sizeof(t_sprite_line) * capacity);
	if (!sls->arr)
		return (-1);
	sls->capacity = capacity;
	sls->size = 0;
	return (0);
}

static int	sprite_lines_realloc(t_sprite_lines *sls)
{
	t_sprite_line	*arr;
	int				i;

	arr = malloc(sizeof(t_sprite_line) * (sls->capacity << 1));
	if (!arr)
		return (-1);
	i = -1;
	while (++i < sls->size)
		arr[i] = sls->arr[i];
	free(sls->arr);
	sls->arr = arr;
	sls->capacity <<= 1;
	return (0);
}

int	sprite_lines_add(t_sprite_lines *sls, t_sprite_line *sl)
{
	if (sls->size == sls->capacity && sprite_lines_realloc(sls) == -1)
		return (-1);
	sls->arr[sls->size++] = *sl;
	return (0);
}
