/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 12:17:55 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 10:06:59 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vars_bonus.h>
#include <sprite_line_bonus.h>
#include <grid.h>

void	get_sprite_lines(t_vars *vars, const t_grid *grid, const int angle,
			t_sprite_lines *sls);
void	get_hdoor_sprite_lines(t_vars *vars, const t_grid *grid,
			const int angle);
void	get_vdoor_sprite_lines(t_vars *vars, const t_grid *grid,
			const int angle);

static void	set_grid_horizontal(t_vars *vars, int angle, int colm, t_grid *grid)
{
	grid->x_delta = vars->x_step_table[angle];
	if (angle > 0 && angle < vars->angle.angle180)
	{
		grid->y = (vars->camera.y / vars->block_width)
			* vars->block_width + vars->block_width;
		grid->x = vars->camera.x + (grid->y - vars->camera.y)
			/ vars->tan_table[angle];
		grid->y_delta = vars->block_width;
	}
	else
	{
		grid->y = (vars->camera.y / vars->block_width)
			* vars->block_width;
		grid->x = vars->camera.x + (grid->y-- - vars->camera.y)
			/ vars->tan_table[angle];
		grid->y_delta = -vars->block_width;
	}
	grid->colm = colm;
}

static float	cast_ray_horizontal(t_vars *vars, int angle, float *x_offset,
		int colm)
{
	t_grid	grid;

	if (angle == 0 || angle == vars->angle.angle180)
		return (1.0 / 0.0);
	set_grid_horizontal(vars, angle, colm, &grid);
	while (1)
	{
		grid.x_index = (int)grid.x / vars->block_width;
		grid.y_index = (int)grid.y / vars->block_width;
		if (grid.x_index < 0 || grid.x_index >= vars->map.field.width
			|| grid.y_index < 0 || grid.y_index >= vars->map.field.size)
			return (1.0 / 0.0);
		else if (vars->map.field.arr[grid.y_index][grid.x_index] == '1')
		{
			*x_offset = (float)((int)grid.x % vars->block_width)
				/ vars->block_width;
			return ((grid.x - vars->camera.x) / vars->cos_table[angle]);
		}
		else if (vars->map.field.arr[grid.y_index][grid.x_index] == '2')
			get_sprite_lines(vars, &grid, angle, &vars->h_sls);
		else if (vars->map.field.arr[grid.y_index][grid.x_index] == '3')
			get_hdoor_sprite_lines(vars, &grid, angle);
		grid.x += grid.x_delta;
		grid.y += grid.y_delta;
	}
}

static void	set_grid_vertical(t_vars *vars, int angle, int colm, t_grid *grid)
{
	grid->y_delta = vars->y_step_table[angle];
	if (angle < vars->angle.angle90 || angle > vars->angle.angle270)
	{
		grid->x = (vars->camera.x / vars->block_width)
			* vars->block_width + vars->block_width;
		grid->y = vars->camera.y + (grid->x - vars->camera.x)
			* vars->tan_table[angle];
		grid->x_delta = vars->block_width;
	}
	else
	{
		grid->x = (vars->camera.x / vars->block_width)
			* vars->block_width;
		grid->y = vars->camera.y + (grid->x-- - vars->camera.x)
			* vars->tan_table[angle];
		grid->x_delta = -vars->block_width;
	}
	grid->colm = colm;
}

static float	cast_ray_vertical(t_vars *vars, int angle, float *x_offset,
		int colm)
{
	t_grid	grid;

	if (angle == vars->angle.angle90 || angle == vars->angle.angle270)
		return (1.0 / 0.0);
	set_grid_vertical(vars, angle, colm, &grid);
	while (1)
	{
		grid.x_index = (int)grid.x / vars->block_width;
		grid.y_index = (int)grid.y / vars->block_width;
		if (grid.x_index < 0 || grid.x_index >= vars->map.field.width
			|| grid.y_index < 0 || grid.y_index >= vars->map.field.size)
			return (1.0 / 0.0);
		else if (vars->map.field.arr[grid.y_index][grid.x_index] == '1')
		{
			*x_offset = (float)((int)grid.y % vars->block_width)
				/ vars->block_width;
			return ((grid.y - vars->camera.y) / vars->sin_table[angle]);
		}
		else if (vars->map.field.arr[grid.y_index][grid.x_index] == '2')
			get_sprite_lines(vars, &grid, angle, &vars->v_sls);
		else if (vars->map.field.arr[grid.y_index][grid.x_index] == '3')
			get_vdoor_sprite_lines(vars, &grid, angle);
		grid.x += grid.x_delta;
		grid.y += grid.y_delta;
	}
}

void	get_sprite_line(t_vars *vars, t_sprite_line *sl,
		int angle, int colm)
{
	float	dist_v;
	float	x_v;

	x_v = 0.0;
	sl->dist = cast_ray_horizontal(vars, angle, &sl->x_offset, colm);
	dist_v = cast_ray_vertical(vars, angle, &x_v, colm);
	if (dist_v < sl->dist)
	{
		sl->dist = dist_v * vars->fish_table[colm];
		sl->x_offset = x_v;
		if (angle < vars->angle.angle90 || angle > vars->angle.angle270)
			sl->texture = &vars->wall_E;
		else
			sl->texture = &vars->wall_W;
	}
	else
	{
		sl->dist *= vars->fish_table[colm];
		if (angle > 0 && angle < vars->angle.angle180)
			sl->texture = &vars->wall_S;
		else
			sl->texture = &vars->wall_N;
	}
	sl->height = vars->block_height * vars->camera.focal_length / sl->dist;
	sl->bottom = vars->camera.cy - (sl->height >> 1);
}
