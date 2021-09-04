/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_lines_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 09:03:46 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/01 09:13:38 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include <vars_bonus.h>
#include <sprite_line_bonus.h>
#include <drawer.h>

static void	correct_drawer(t_drawer *drawer, t_sprite_line *sl)
{
	if (sl->bottom + sl->height >= HEIGHT)
	{
		if (sl->bottom >= 0)
			sl->height = HEIGHT - sl->bottom;
		else
		{
			drawer->row = drawer->step * -sl->bottom;
			sl->height = HEIGHT;
			sl->bottom = 0;
		}
	}
	else if (sl->bottom < 0)
	{
		drawer->row = drawer->step * -sl->bottom;
		sl->height += sl->bottom;
		sl->bottom = 0;
	}
}

static void	set_drawer(t_vars *vars, int x, t_sprite_line *sl,
		t_drawer *drawer)
{
	drawer->step = (float)sl->texture->height / ++sl->height;
	drawer->row = 0.0;
	correct_drawer(drawer, sl);
	drawer->back_addr = vars->back.addr + sl->bottom * vars->back.length
		+ x * vars->back.bits_per_pixel;
	drawer->texture_addr = sl->texture->addr + (int)drawer->row
		* sl->texture->length + (int)(sl->x_offset * sl->texture->width)
		*sl->texture->bits_per_pixel;
	drawer->row -= (int)drawer->row;
	sl->shade = 1.0 - floor(sl->dist)
		/ (vars->map.field.width * vars->block_width);
	if (sl->shade < 0.15)
		sl->shade = 0.15;
}

void	draw_vertical_line(t_vars *vars, int x, t_sprite_line *sl)
{
	t_drawer	drawer;

	if (sl->height <= 0 || sl->bottom + sl->height <= 0
		|| sl->bottom >= HEIGHT)
		return ;
	set_drawer(vars, x, sl, &drawer);
	while (sl->height--)
	{
		*drawer.back_addr = (*drawer.texture_addr & 0xff) * sl->shade;
		drawer.back_addr[1] = (drawer.texture_addr[1] & 0xff) * sl->shade;
		drawer.back_addr[2] = (drawer.texture_addr[2] & 0xff) * sl->shade;
		drawer.back_addr[3] = 0;
		drawer.back_addr += vars->back.length;
		drawer.row += drawer.step;
		if (drawer.row >= 1.0)
		{
			drawer.texture_addr += sl->texture->length * (int)drawer.row;
			drawer.row -= (int)drawer.row;
		}
	}
}

void	draw_vertical_line_transparent(t_vars *vars, int x, t_sprite_line *sl)
{
	t_drawer	drawer;

	if (sl->height <= 0 || sl->bottom + sl->height <= 0
		|| sl->bottom >= HEIGHT)
		return ;
	set_drawer(vars, x, sl, &drawer);
	while (sl->height--)
	{
		if (*drawer.texture_addr || drawer.texture_addr[1]
			|| drawer.texture_addr[2])
		{
			*drawer.back_addr = (*drawer.texture_addr & 0xff) * sl->shade;
			drawer.back_addr[1] = (drawer.texture_addr[1] & 0xff) * sl->shade;
			drawer.back_addr[2] = (drawer.texture_addr[2] & 0xff) * sl->shade;
			drawer.back_addr[3] = 0;
		}
		drawer.back_addr += vars->back.length;
		drawer.row += drawer.step;
		if (drawer.row >= 1.0)
		{
			drawer.texture_addr += sl->texture->length * (int)drawer.row;
			drawer.row -= (int)drawer.row;
		}
	}
}
