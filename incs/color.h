/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 14:00:16 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/17 14:02:45 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

int	get_color(int red, int green, int blue, int alpha);
int	get_red(int color);
int	get_green(int color);
int	get_blue(int color);
int	get_alpha(int color);

#endif	/*COLOR_H*/
