/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_vars_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 15:05:31 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 16:55:31 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <mlx.h>
#include <vars_bonus.h>

void	set_to_null(t_vars *vars)
{
	vars->mlx = NULL;
	vars->win = NULL;
	vars->back.img = NULL;
	vars->wall_N.img = NULL;
	vars->wall_S.img = NULL;
	vars->wall_E.img = NULL;
	vars->wall_W.img = NULL;
	vars->sprite.img = NULL;
	vars->door.img = NULL;
	vars->dq.arr = NULL;
	vars->sin_table = NULL;
	vars->cos_table = NULL;
	vars->tan_table = NULL;
	vars->fish_table = NULL;
	vars->x_step_table = NULL;
	vars->y_step_table = NULL;
	vars->h_sls.arr = NULL;
	vars->v_sls.arr = NULL;
}

static void	vars_free_tables(t_vars *vars)
{
	if (vars->sin_table)
		free(vars->sin_table);
	if (vars->cos_table)
		free(vars->cos_table);
	if (vars->tan_table)
		free(vars->tan_table);
	if (vars->fish_table)
		free(vars->fish_table);
	if (vars->x_step_table)
		free(vars->x_step_table);
	if (vars->y_step_table)
		free(vars->y_step_table);
}

void	vars_free(t_vars *vars)
{
	vars_free_tables(vars);
	map_free(&vars->map);
	if (vars->h_sls.arr)
		free(vars->h_sls.arr);
	if (vars->v_sls.arr)
		free(vars->v_sls.arr);
	if (vars->dq.arr)
		free(vars->dq.arr);
	if (vars->wall_N.img)
		mlx_destroy_image(vars->mlx, vars->wall_N.img);
	if (vars->wall_S.img)
		mlx_destroy_image(vars->mlx, vars->wall_S.img);
	if (vars->wall_E.img)
		mlx_destroy_image(vars->mlx, vars->wall_E.img);
	if (vars->wall_W.img)
		mlx_destroy_image(vars->mlx, vars->wall_W.img);
	if (vars->sprite.img)
		mlx_destroy_image(vars->mlx, vars->sprite.img);
	if (vars->door.img)
		mlx_destroy_image(vars->mlx, vars->door.img);
	if (vars->back.img)
		mlx_destroy_image(vars->mlx, vars->back.img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
}
