/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 15:56:52 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 17:17:42 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <door_bonus.h>

int	queue_init(t_door_queue *dq, int capacity)
{
	dq->arr = malloc(sizeof(t_door) * capacity);
	if (!dq->arr)
		return (-1);
	dq->capacity = capacity;
	dq->first = 0;
	dq->size = 0;
	return (0);
}

static int	queue_realloc(t_door_queue *dq)
{
	t_door	*arr;
	int		i;
	int		counter;
	int		capacity;

	capacity = (dq->capacity << 1);
	arr = malloc(sizeof(t_door) * capacity);
	if (!arr)
		return (-1);
	i = dq->first + capacity - dq->capacity;
	counter = -1;
	while (++counter < dq->size)
	{
		arr[i] = dq->arr[dq->first];
		i = (i + 1) % capacity;
		dq->first = (dq->first + 1) % dq->capacity;
	}
	free(dq->arr);
	dq->arr = arr;
	dq->first = (i + capacity - dq->size) % capacity;
	dq->capacity = capacity;
	return (0);
}

int	queue_push(t_door_queue *dq, t_door *door)
{
	int	i;
	int	counter;

	i = dq->first;
	counter = -1;
	while (++counter < dq->size)
	{
		if (dq->arr[i].x_index == door->x_index
			&& dq->arr[i].y_index == door->y_index)
			return (0);
		if (++i == dq->capacity)
			i = 0;
	}
	if (dq->size == dq->capacity && queue_realloc(dq) == -1)
		return (-1);
	dq->arr[(dq->first + dq->size++) % dq->capacity] = *door;
	return (0);
}

int	queue_get_shift(t_door_queue *dq, int x, int y)
{
	int	i;
	int	counter;

	if (!dq->size)
		return (0);
	i = dq->first - 1;
	counter = -1;
	while (++i < dq->capacity && ++counter < dq->size)
		if (dq->arr[i].x_index == x && dq->arr[i].y_index == y)
			return ((int)dq->arr[i].shift);
	i = 0;
	while (++counter < dq->size)
	{
		if (dq->arr[i].x_index == x && dq->arr[i].y_index == y)
			return ((int)dq->arr[i].shift);
		++i;
	}
	return (0);
}
