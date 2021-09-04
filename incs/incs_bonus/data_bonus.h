/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:39:18 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/01 16:39:37 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_BONUS_H
# define DATA_BONUS_H

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		length;
	int		endian;
	int		width;
	int		height;
	int		shift;
	int		counter;
	int		speed;
	int		frame;
	int		frames;
}	t_data;

#endif	/*DATA_BONUS_H*/
