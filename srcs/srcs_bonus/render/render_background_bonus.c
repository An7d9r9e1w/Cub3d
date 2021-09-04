/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 09:36:14 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/31 10:07:20 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vars_bonus.h>

static int	get_color_dark(int color, float coef)
{
	if (coef >= 1.0)
		return (color);
	if (coef <= 0.0)
		return (0);
	return (((int)(((color >> 16) & 0xff) * coef) << 16)
			| ((int)(((color >> 8) & 0xff) * coef) << 8)
			| (int)((color & 0xff) * coef));
}

static int	draw_cell(t_vars *vars, unsigned int **back_p)
{
	const unsigned int	color = vars->map.cell_color;
	unsigned int		*back;
	int					y;
	int					x;
	int					y_limit;

	back = *back_p;
	if (vars->camera.cy < HEIGHT)
		y_limit = vars->camera.cy;
	else
		y_limit = HEIGHT - 1;
	y = -1;
	while (++y < y_limit)
	{
		x = -1;
		while (++x < WIDTH)
			*back++ = color;
	}
	*back_p = back;
	return (y);
}

static void	draw_floor(t_vars *vars, unsigned int *back, int y)
{
	const float		step = 180.0 / 255.0 / (HEIGHT >> 1);
	float			coef;
	unsigned int	color;
	int				x;

	coef = 1.0 - 180.0 / 255.0;
	color = get_color_dark(vars->map.floor_color, coef);
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			*back++ = color;
		coef += step;
		color = get_color_dark(vars->map.floor_color, coef);
	}
}

void	draw_floor_and_cell(t_vars *vars)
{
	unsigned int	*back;
	int				y;

	back = (unsigned int *)(vars->back.addr);
	y = draw_cell(vars, &back);
	draw_floor(vars, back, y - 1);
}
