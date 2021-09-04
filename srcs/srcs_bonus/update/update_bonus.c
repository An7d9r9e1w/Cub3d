/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:07:44 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 17:02:49 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <vars_bonus.h>

void	update_sprites(t_vars *vars);
void	update_move(t_vars *vars, int move, int angle);
void	update_door_queue(t_vars *vars);

static void	correct_rotate(t_vars *vars, int h_rotate, int v_rotate)
{
	vars->camera.pov += (vars->angle.angle5 * h_rotate) >> 6;
	if (vars->camera.pov < 0)
		vars->camera.pov += vars->angle.angle360;
	else if (vars->camera.pov >= vars->angle.angle360)
		vars->camera.pov -= vars->angle.angle360;
	vars->camera.cy -= (v_rotate << 1);
	if (vars->camera.cy < -HEIGHT)
		vars->camera.cy = -HEIGHT;
	else if (vars->camera.cy > (HEIGHT + (HEIGHT >> 1)))
		vars->camera.cy = HEIGHT + (HEIGHT >> 1);
}

int	motion_event(int x, int y, t_vars *vars)
{
	static int	mouseX = (WIDTH >> 1);
	static int	mouseY = (HEIGHT >> 1);
	const int	h_rotate = (x - mouseX) % WIDTH;
	const int	v_rotate = (y - mouseY) % HEIGHT;

	if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
	{
		if (x < 0)
			x += WIDTH;
		else if (x >= WIDTH)
			x -= WIDTH;
		if (y < 0)
			y += HEIGHT;
		else if (y >= HEIGHT)
			y -= HEIGHT;
		mlx_mouse_move(vars->win, x, y);
	}
	mouseX = x;
	mouseY = y;
	correct_rotate(vars, h_rotate, v_rotate);
	return (0);
}

void	update(t_vars *vars)
{
	if (vars->moveWS)
		update_move(vars, vars->moveWS, vars->camera.pov);
	if (vars->moveAD)
		update_move(vars, vars->moveAD, (vars->camera.pov
				+ vars->angle.angle90) % vars->angle.angle360);
	update_sprites(vars);
	update_door_queue(vars);
}
