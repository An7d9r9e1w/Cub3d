/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:07:44 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 18:07:18 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vars_bonus.h>
#include <collision.h>

static void	init_collision(t_vars *vars, int move, int angle, t_collision *coll)
{
	coll->dx = move * vars->cos_table[angle] * vars->camera.move_speed;
	coll->dy = move * vars->sin_table[angle] * vars->camera.move_speed;
	vars->camera.x += coll->dx;
	vars->camera.y += coll->dy;
	coll->x_index = vars->camera.x / vars->block_width;
	coll->y_index = vars->camera.y / vars->block_width;
	coll->x_offset = vars->camera.x % vars->block_width;
	coll->y_offset = vars->camera.y % vars->block_width;
	coll->min_dist = vars->block_width * 0.2;
}

static int	check_collision(char c)
{
	return (c == '1' || c == '3');
}

void	update_move(t_vars *vars, int move, int angle)
{
	t_collision	cl;

	init_collision(vars, move, angle, &cl);
	if (cl.dx > 0)
	{
		if (check_collision(vars->map.field.arr[cl.y_index][cl.x_index + 1])
				&& cl.x_offset > (vars->block_width - cl.min_dist))
			vars->camera.x -= cl.x_offset
				- (vars->block_width - cl.min_dist);
	}
	else if (check_collision(
			vars->map.field.arr[cl.y_index][cl.x_index - 1])
			&& cl.x_offset < cl.min_dist)
		vars->camera.x += cl.min_dist - cl.x_offset;
	if (cl.dy > 0)
	{
		if (check_collision(vars->map.field.arr[cl.y_index + 1][cl.x_index])
				&& cl.y_offset > (vars->block_width - cl.min_dist))
			vars->camera.y -= cl.y_offset
				- (vars->block_width - cl.min_dist);
	}
	else if (check_collision(vars->map.field.arr[cl.y_index - 1][cl.x_index])
			&& cl.y_offset < cl.min_dist)
		vars->camera.y += cl.min_dist - cl.y_offset;
}
