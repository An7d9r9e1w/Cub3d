/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:36:09 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/01 17:00:32 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vars_bonus.h>

void	update_sprites(t_vars *vars)
{
	if (++vars->sprite.counter == vars->sprite.speed)
	{
		vars->sprite.counter = 0;
		if (++vars->sprite.frame == vars->sprite.frames)
		{
			vars->sprite.addr -= vars->sprite.shift * (vars->sprite.frames - 1);
			vars->sprite.frame = 0;
		}
		else
			vars->sprite.addr += vars->sprite.shift;
	}
}
