/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 09:55:32 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/26 10:04:28 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

# include <vars.h>

int	key_press_event(int keycode, t_vars *vars);
int	key_release_event(int keycode, t_vars *vars);
int	destroy_event(t_vars *vars);
int	game_loop(t_vars *vars);

#endif	/*EVENTS_H*/
