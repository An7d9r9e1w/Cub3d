/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:20:47 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/01 08:24:38 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <vars.h>
#include <sprite_line.h>
#include <drawer.h>

void	get_sprite_line(t_vars *vars, t_sprite_line *sprite_line,
			int angle, int colm);

static void	draw_floor_and_cell(t_vars *vars)
{
	const int		y_limit = (HEIGHT >> 1);
	unsigned int	*back;
	unsigned int	color;
	int				y;
	int				x;

	back = (unsigned int *)(vars->back.addr);
	color = vars->map.cell_color;
	y = -1;
	while (++y < y_limit)
	{
		x = -1;
		while (++x < WIDTH)
			*back++ = color;
	}
	color = vars->map.floor_color;
	--y;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			*back++ = color;
	}
}

static void	set_drawer(t_vars *vars, int x, t_sprite_line *sl,
		t_drawer *drawer)
{
	drawer->step = (float)sl->texture->height / ++sl->height;
	if (sl->height >= HEIGHT)
	{
		drawer->row = drawer->step * -sl->bottom;
		sl->height = HEIGHT;
		drawer->back_addr = vars->back.addr + x * vars->back.bits_per_pixel;
		drawer->texture_addr = sl->texture->addr + (int)drawer->row
			* sl->texture->length + (int)(sl->x_offset * sl->texture->width)
			*sl->texture->bits_per_pixel;
		drawer->row -= (int)drawer->row;
	}
	else
	{
		drawer->row = 0.0;
		drawer->back_addr = vars->back.addr + sl->bottom * vars->back.length
			+ x * vars->back.bits_per_pixel;
		drawer->texture_addr = sl->texture->addr + (int)(sl->x_offset
				*sl->texture->width) *sl->texture->bits_per_pixel;
	}
}

static void	draw_vertical_line(t_vars *vars, int x, t_sprite_line *sprite_line)
{
	t_drawer	drawer;

	if (sprite_line->height < 0)
		return ;
	set_drawer(vars, x, sprite_line, &drawer);
	while (sprite_line->height--)
	{
		*drawer.back_addr = *drawer.texture_addr;
		drawer.back_addr[1] = drawer.texture_addr[1];
		drawer.back_addr[2] = drawer.texture_addr[2];
		drawer.back_addr[3] = 0;
		drawer.back_addr += vars->back.length;
		drawer.row += drawer.step;
		if (drawer.row >= 1.0)
		{
			drawer.texture_addr += sprite_line->texture->length
				* (int)drawer.row;
			drawer.row -= (int)drawer.row;
		}
	}
}

static void	draw_walls(t_vars *vars)
{
	const int		angle360 = vars->angle.angle360;
	t_sprite_line	sprite_line;
	int				colm;
	int				angle;

	angle = vars->camera.pov - vars->angle.angle30;
	if (angle < 0)
		angle += angle360;
	colm = -1;
	while (++colm < WIDTH)
	{
		get_sprite_line(vars, &sprite_line, angle, colm);
		draw_vertical_line(vars, colm, &sprite_line);
		if (++angle >= angle360)
			angle -= angle360;
	}
}

void	render(t_vars *vars)
{
	draw_floor_and_cell(vars);
	draw_walls(vars);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->back.img, 0, 0);
}
