/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tables_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:17:36 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/31 10:17:37 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include <vars_bonus.h>

static int	allocate_memory(t_vars *vars)
{
	vars->sin_table = malloc(sizeof(float) * vars->angle.angle360);
	if (vars->sin_table)
		vars->cos_table = malloc(sizeof(float) * vars->angle.angle360);
	if (vars->cos_table)
		vars->tan_table = malloc(sizeof(float) * vars->angle.angle360);
	if (vars->tan_table)
		vars->fish_table = malloc(sizeof(float) * vars->angle.angle60 + 1);
	if (vars->fish_table)
		vars->x_step_table = malloc(sizeof(float) * vars->angle.angle360);
	if (vars->x_step_table)
		vars->y_step_table = malloc(sizeof(float) * vars->angle.angle360);
	return (-!vars->y_step_table);
}

static void	fill_step_tables(t_vars *vars, int i)
{
	vars->x_step_table[i] = vars->block_width / vars->tan_table[i];
	if (i >= vars->angle.angle90 && i < vars->angle.angle270)
	{
		if (vars->x_step_table[i] > 0)
			vars->x_step_table[i] = -vars->x_step_table[i];
	}
	else if (vars->x_step_table[i] < 0)
		vars->x_step_table[i] = -vars->x_step_table[i];
	vars->y_step_table[i] = vars->block_width * vars->tan_table[i];
	if (i >= vars->angle.angle0 && i < vars->angle.angle180)
	{
		if (vars->y_step_table[i] < 0)
			vars->y_step_table[i] = -vars->y_step_table[i];
	}
	else if (vars->y_step_table[i] > 0)
		vars->y_step_table[i] = -vars->y_step_table[i];
}

int	init_tables(t_vars *vars)
{
	float	radian;
	int		i;

	if (allocate_memory(vars) == -1)
		return (-1);
	i = -1;
	while (++i < vars->angle.angle360)
	{
		radian = (float)i * M_PI / vars->angle.angle180 + 0.0001;
		vars->sin_table[i] = sin(radian);
		vars->cos_table[i] = cos(radian);
		vars->tan_table[i] = tan(radian);
		fill_step_tables(vars, i);
	}
	i = -vars->angle.angle30 - 1;
	while (++i <= vars->angle.angle30)
		vars->fish_table[i + vars->angle.angle30]
			= cos((float)i * M_PI / vars->angle.angle180);
	return (0);
}
