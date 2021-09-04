/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_lines_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 09:21:16 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/31 11:30:24 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_LINES_BONUS_H
# define SPRITE_LINES_BONUS_H

# include <sprite_line_bonus.h>

typedef struct s_sprite_lines
{
	t_sprite_line	*arr;
	int				size;
	int				capacity;
}	t_sprite_lines;

int	init_sprite_lines(t_sprite_lines *sls, int capacity);
int	sprite_lines_add(t_sprite_lines *sls, t_sprite_line *sl);

#endif	/*SPRITE_LINES_BONUS_H*/
