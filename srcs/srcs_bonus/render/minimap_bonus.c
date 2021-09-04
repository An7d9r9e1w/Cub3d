/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejina <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 13:52:52 by ejina             #+#    #+#             */
/*   Updated: 2021/09/01 09:46:53 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <vars_bonus.h>
#include <minimap.h>

static void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
	{
		dst = data->addr
			+ (y * data->length + x * (data->bits_per_pixel));
		*(unsigned int *) dst = color;
	}
}

void	in_alg(t_vars *vars, t_position *pos, int x, int rad)
{
	int	tmpy;
	int	tmpx;

	tmpy = pos->y - rad;
	while (tmpy <= pos->y + rad)
	{
		my_mlx_pixel_put(&vars->back, pos->x + x, tmpy, COLOR_PLR);
		my_mlx_pixel_put(&vars->back, pos->x - x, tmpy, COLOR_PLR);
		tmpy++;
	}
	tmpx = pos->x - rad;
	while (tmpx <= pos->x + rad)
	{
		my_mlx_pixel_put(&vars->back, tmpx, pos->y - x, COLOR_PLR);
		my_mlx_pixel_put(&vars->back, tmpx, pos->y + x, COLOR_PLR);
		tmpx++;
	}
}

void	alg_brz(t_vars *vars, t_position *pos, int rad)
{
	int	x;
	int	delta;
	int	error;

	delta = 1 - 2 * rad;
	error = 0;
	x = 0;
	while (rad >= x)
	{
		in_alg(vars, pos, x, rad);
		error = 2 * (delta + rad) - 1;
		if (delta < 0 && error <= 0)
		{
			delta += 2 * ++x + 1;
			continue ;
		}
		if (delta > 0 && error > 0)
		{
			delta -= 2 * --rad + 1;
			continue ;
		}
		delta += 2 * (++x - --rad);
	}
}

void	draw_player(t_vars *vars)
{
	int			rad;
	t_position	pos;

	pos.y = vars->camera.y / (vars->block_width / SCALE);
	pos.x = vars->camera.x / (vars->block_width / SCALE);
	rad = SCALE >> 1;
	alg_brz(vars, &pos, rad);
}

void	draw_minimap(t_vars *vars)
{
	t_position	pos;
	int			i;
	int			j;

	i = -1;
	while (++i < vars->map.field.size)
	{
		j = -1;
		while (vars->map.field.arr[i][++j])
		{
			if (vars->map.field.arr[i][j] == '1')
			{
				pos.y = i * SCALE;
				while (pos.y++ < i * SCALE + SCALE)
				{
					pos.x = j * SCALE;
					while (pos.x++ < j * SCALE + SCALE)
					{
						my_mlx_pixel_put(&vars->back, pos.x, pos.y, COLOR_MAP);
					}
				}
			}
		}
	}
	draw_player(vars);
}
