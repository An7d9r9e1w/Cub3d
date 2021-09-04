/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/27 12:28:00 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/01 08:36:26 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWER_H
# define DRAWER_H

typedef struct s_drawer
{
	char	*back_addr;
	char	*texture_addr;
	float	step;
	float	row;
}	t_drawer;

#endif	/*DRAWER_H*/
