/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 09:59:32 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/27 13:27:02 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <events.h>

void	init_events(t_vars *vars)
{
	mlx_hook(vars->win, 2, 0, key_press_event, vars);
	mlx_hook(vars->win, 3, 0, key_release_event, vars);
	mlx_hook(vars->win, 17, 0, destroy_event, vars);
	mlx_loop_hook(vars->mlx, game_loop, vars);
}
