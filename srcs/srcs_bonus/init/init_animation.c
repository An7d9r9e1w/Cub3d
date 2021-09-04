/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 17:08:31 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 14:55:07 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vars_bonus.h>

void	set_animation_options(t_vars *vars)
{
	vars->sprite.shift = 32 * vars->sprite.bits_per_pixel;
	vars->sprite.addr += vars->sprite.shift;
	vars->sprite.width = 32;
	vars->sprite.height = 32;
	vars->sprite.counter = 0;
	vars->sprite.speed = 30;
	vars->sprite.frame = 0;
	vars->sprite.frames = 3;
}
