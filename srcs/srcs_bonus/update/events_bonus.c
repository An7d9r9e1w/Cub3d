/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 13:43:17 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/29 13:44:49 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <mlx.h>
#include <events_bonus.h>

static void	close(t_vars *vars)
{
	vars_free(vars);
	mlx_mouse_show();
	exit(0);
}

int	key_press_event(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY)
		close(vars);
	if (keycode == W_KEY)
		vars->moveWS = 1;
	else if (keycode == S_KEY)
		vars->moveWS = -1;
	else if (keycode == A_KEY)
		vars->moveAD = -1;
	else if (keycode == D_KEY)
		vars->moveAD = 1;
	return (0);
}

int	key_release_event(int keycode, t_vars *vars)
{
	if (keycode == W_KEY || keycode == S_KEY)
		vars->moveWS = 0;
	else if (keycode == A_KEY || keycode == D_KEY)
		vars->moveAD = 0;
	return (0);
}

int	destroy_event(t_vars *vars)
{
	close(vars);
	return (0);
}
