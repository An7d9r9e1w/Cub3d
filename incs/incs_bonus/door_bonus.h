/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:43:57 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 17:29:07 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOR_BONUS_H
# define DOOR_BONUS_H

# define DEFAULT_DOOR_SPEED 0.03
# define DEFAULT_DOOR_TIME_LIMIT 330

typedef struct s_door
{
	float	shift;
	float	speed;
	int		x_index;
	int		y_index;
	int		time;
	int		time_limit;
}	t_door;

typedef struct s_door_queue
{
	t_door	*arr;
	int		first;
	int		size;
	int		capacity;
}	t_door_queue;

int		queue_init(t_door_queue *dq, int capacity);
int		queue_push(t_door_queue *dq, t_door *door);
int		queue_get_shift(t_door_queue *dq, int x, int y);

#endif	/*DOOR_BONUS_H*/
