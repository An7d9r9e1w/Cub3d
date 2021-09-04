/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_lines_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:17:59 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/31 10:18:01 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	realloc_lines(char ***lines, int *capacity)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(void *) * (*capacity << 1));
	if (!tmp)
		return (-1);
	i = -1;
	while (++i < *capacity)
		tmp[i] = (*lines)[i];
	free(*lines);
	*lines = tmp;
	*capacity <<= 1;
	return (0);
}

void	free_lines(char **lines, int size)
{
	while (size-- > 0)
		free(lines[size] - 1);
	free(lines);
}
