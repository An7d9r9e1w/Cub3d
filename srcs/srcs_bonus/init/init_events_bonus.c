/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_events_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 12:36:55 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/29 13:42:12 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <events_bonus.h>

void	init_events(t_vars *vars)
{
	mlx_mouse_hide();
	mlx_mouse_move(vars->win, (WIDTH >> 1), (HEIGHT >> 1));
	mlx_hook(vars->win, 2, 0, key_press_event, vars);
	mlx_hook(vars->win, 3, 0, key_release_event, vars);
	mlx_hook(vars->win, 6, 0, motion_event, vars);
	mlx_hook(vars->win, 17, 0, destroy_event, vars);
	mlx_loop_hook(vars->mlx, game_loop, vars);
}
