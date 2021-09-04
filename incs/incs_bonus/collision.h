/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 11:13:58 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/28 11:19:28 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_H
# define COLLISION_H

typedef struct s_collision
{
	float	dx;
	float	dy;
	int		x_index;
	int		y_index;
	int		x_offset;
	int		y_offset;
	int		min_dist;
}	t_collision;

#endif	/*COLLISION_H*/
