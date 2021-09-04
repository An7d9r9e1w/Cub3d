/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 07:14:14 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/27 07:14:52 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		length;
	int		endian;
	int		width;
	int		height;
}	t_data;

#endif	/*DATA_H*/
