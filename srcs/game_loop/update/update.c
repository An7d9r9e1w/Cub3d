/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 10:22:06 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/27 13:55:14 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vars.h>

static void	update_move(t_vars *vars, int move, int angle)
{
	if (move == 1)
	{
		vars->camera.x += vars->cos_table[angle]
			* vars->camera.move_speed;
		vars->camera.y += vars->sin_table[angle]
			* vars->camera.move_speed;
	}
	else
	{
		vars->camera.x -= vars->cos_table[angle]
			* vars->camera.move_speed;
		vars->camera.y -= vars->sin_table[angle]
			* vars->camera.move_speed;
	}
}

static void	update_rotate(t_vars *vars)
{
	if (vars->rotate == -1)
	{
		vars->camera.pov -= vars->camera.rotate_speed;
		if (vars->camera.pov < 0)
			vars->camera.pov += vars->angle.angle360;
	}
	else
	{
		vars->camera.pov += vars->camera.rotate_speed;
		if (vars->camera.pov >= vars->angle.angle360)
			vars->camera.pov -= vars->angle.angle360;
	}
}

void	update(t_vars *vars)
{
	if (vars->moveWS)
		update_move(vars, vars->moveWS, vars->camera.pov);
	if (vars->moveAD)
		update_move(vars, vars->moveAD, (vars->camera.pov
				+ vars->angle.angle90) % vars->angle.angle360);
	if (vars->rotate)
		update_rotate(vars);
}
