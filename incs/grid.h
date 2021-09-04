/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:24:20 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/01 14:26:29 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRID_H
# define GRID_H

typedef struct s_grid
{
	float	x;
	float	y;
	float	x_delta;
	float	y_delta;
	int		x_index;
	int		y_index;
	int		colm;
}	t_grid;

#endif	/*GRID_H*/
