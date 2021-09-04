/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 08:07:59 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/31 08:08:25 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <vars_bonus.h>
#include <error.h>

void	update(t_vars *vars);
void	render(t_vars *vars);

int	game_loop(t_vars *vars)
{
	update(vars);
	render(vars);
	return (0);
}

void	run_cub(t_map map)
{
	t_vars	vars;

	vars.map = map;
	if (vars_init(&vars) == -1)
	{
		vars_free(&vars);
		fatal(-1);
	}
	mlx_loop(vars.mlx);
}
