/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 13:55:25 by ejina             #+#    #+#             */
/*   Updated: 2021/08/29 13:55:50 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

/*** Minimap ***/
# define SCALE 10
# define COLOR_MAP 0xFFFFFF
# define COLOR_PLR 0x111111

typedef struct s_position
{
	int		x;
	int		y;
}	t_position;

#endif	/*MINIMAP_H*/
