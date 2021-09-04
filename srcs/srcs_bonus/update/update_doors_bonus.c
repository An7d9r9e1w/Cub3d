/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_door_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:56:52 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 18:00:43 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vars_bonus.h>

static void	update_door(t_vars *vars, t_door *door)
{
	if (door->time < door->time_limit)
	{
		++door->time;
		if ((int)door->shift < vars->block_width)
			door->shift += vars->block_width * door->speed;
		else if (vars->map.field.arr[door->y_index][door->x_index] == '3')
			vars->map.field.arr[door->y_index][door->x_index] = '0';
	}
	else if ((int)vars->camera.x / vars->block_width != door->x_index
		|| (int)vars->camera.y / vars->block_width != door->y_index)
	{
		if (vars->map.field.arr[door->y_index][door->x_index] == '0')
			vars->map.field.arr[door->y_index][door->x_index] = '3';
		door->shift -= vars->block_width * door->speed;
		if (door->shift <= 0.0)
		{
			vars->dq.first = (vars->dq.first + 1) % vars->dq.capacity;
			--vars->dq.size;
		}
	}
}

void	update_door_queue(t_vars *vars)
{
	int	i;
	int	counter;

	if (!vars->dq.size)
		return ;
	counter = -1;
	i = vars->dq.first;
	while (++counter < vars->dq.size)
	{
		update_door(vars, vars->dq.arr + i);
		if (++i == vars->dq.capacity)
			i = 0;
	}
}
