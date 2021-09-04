/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprite_lines_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 11:58:19 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 18:03:49 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>

#include <vars_bonus.h>
#include <grid.h>
#include <error.h>

#define SCALE 0.4

static void	door_for_queue(t_vars *vars, const t_grid *grid)
{
	t_door	door;

	door.shift = 0.0;
	door.speed = DEFAULT_DOOR_SPEED;
	door.x_index = grid->x_index;
	door.y_index = grid->y_index;
	door.time = 0;
	door.time_limit = DEFAULT_DOOR_TIME_LIMIT;
	if (queue_push(&vars->dq, &door) == -1)
	{
		vars_free(vars);
		fatal(-1);
	}
}

void	get_hdoor_sprite_lines(t_vars *vars, const t_grid *grid,
			const int angle)
{
	t_sprite_line	sl;
	int				dx;

	if (grid->x < 0.0)
		dx = grid->x + grid->x_delta / 2
			+ queue_get_shift(&vars->dq, grid->x_index, grid->y_index);
	else
		dx = grid->x + grid->x_delta / 2
			- queue_get_shift(&vars->dq, grid->x_index, grid->y_index);
	if ((int)dx / vars->block_width != grid->x_index)
		return ;
	sl.dist = ((grid->y + grid->y_delta / 2 - vars->camera.y)
			/ vars->sin_table[angle]) * vars->fish_table[grid->colm];
	if ((int)sl.dist <= vars->block_width)
		door_for_queue(vars, grid);
	sl.x_offset = (float)((int)dx % vars->block_width) / vars->block_width;
	sl.height = vars->block_height * vars->camera.focal_length / sl.dist;
	sl.bottom = vars->camera.cy - (sl.height >> 1);
	sl.texture = &vars->door;
	if (sprite_lines_add(&vars->h_sls, &sl) == -1)
	{
		vars_free(vars);
		fatal(-1);
	}
}

void	get_vdoor_sprite_lines(t_vars *vars, const t_grid *grid,
			const int angle)
{
	t_sprite_line	sl;
	int				dy;

	if (grid->y < 0.0)
		dy = grid->y + grid->y_delta / 2
			+ queue_get_shift(&vars->dq, grid->x_index, grid->y_index);
	else
		dy = grid->y + grid->y_delta / 2
			- queue_get_shift(&vars->dq, grid->x_index, grid->y_index);
	if ((int)dy / vars->block_width != grid->y_index)
		return ;
	sl.dist = ((grid->x + grid->x_delta / 2 - vars->camera.x)
			/ vars->cos_table[angle]) * vars->fish_table[grid->colm];
	if ((int)sl.dist <= vars->block_width)
		door_for_queue(vars, grid);
	sl.x_offset = (float)((int)dy % vars->block_width) / vars->block_width;
	sl.height = vars->block_height * vars->camera.focal_length / sl.dist;
	sl.bottom = vars->camera.cy - (sl.height >> 1);
	sl.texture = &vars->door;
	if (sprite_lines_add(&vars->v_sls, &sl) == -1)
	{
		vars_free(vars);
		fatal(-1);
	}
}

static void	set_sprite_line(t_vars *vars, int angle, t_sprite_line *sl,
		const int width)
{
	if (angle < 0)
		sl->x_offset = (float)(width - sl->x_offset) / (width << 1);
	else
		sl->x_offset = (float)(width + sl->x_offset) / (width << 1);
	sl->height = vars->block_height * SCALE
		* vars->camera.focal_length / sl->dist;
	sl->bottom = vars->camera.cy;
	sl->texture = &vars->sprite;
}

void	get_sprite_lines(t_vars *vars, const t_grid *grid, const int angle,
			t_sprite_lines *sls)
{
	const int		width = (vars->block_width >> 1) * SCALE;
	t_sprite_line	sl;
	int				dx;
	int				dy;
	int				dang;

	dx = grid->x_index * vars->block_width + (vars->block_width >> 1)
		- vars->camera.x;
	dy = grid->y_index * vars->block_width + (vars->block_width >> 1)
		- vars->camera.y;
	dang = atan((float)dy / (float)dx) / M_PI * vars->angle.angle180;
	sl.dist = sqrt(dx * dx + dy * dy) * vars->fish_table[grid->colm];
	sl.x_offset = sl.dist * vars->tan_table[abs(dang - angle)
		% vars->angle.angle360];
	if (fabs(sl.x_offset) > width)
		return ;
	set_sprite_line(vars, dang - angle, &sl, width);
	if (sprite_lines_add(sls, &sl) == -1)
	{
		vars_free(vars);
		fatal(-1);
	}
}
