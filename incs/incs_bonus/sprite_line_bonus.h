/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_line_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:59:02 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 14:54:56 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_LINE_BONUS_H
# define SPRITE_LINE_BONUS_H

# include <data_bonus.h>

typedef struct s_sprite_line
{
	t_data	*texture;
	float	dist;
	float	x_offset;
	float	shade;
	int		bottom;
	int		height;
}	t_sprite_line;

#endif	/*SPRITE_LINE_BONUS_H*/
