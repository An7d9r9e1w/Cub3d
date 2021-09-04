/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 13:54:53 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/31 10:08:13 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_BONUS_H
# define EVENTS_BONUS_H

# include <vars_bonus.h>

int	key_press_event(int keycode, t_vars *vars);
int	key_release_event(int keycode, t_vars *vars);
int	motion_event(int x, int y, t_vars *vars);
int	destroy_event(t_vars *vars);
int	game_loop(t_vars *vars);

#endif	/*EVENTS_BONUS_H*/
