/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_line.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 12:06:57 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/01 11:45:23 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_LINE_H
# define SPRITE_LINE_H

# include <data.h>

typedef struct s_sprite_line
{
	t_data	*texture;
	float	dist;
	float	x_offset;
	float	shade;
	int		bottom;
	int		height;
}	t_sprite_line;

#endif	/*SPRITE_LINE_H*/
