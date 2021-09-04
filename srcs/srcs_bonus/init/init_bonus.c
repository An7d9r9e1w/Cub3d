/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:17:18 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 17:32:20 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include <mlx.h>
#include <vars_bonus.h>

void	set_to_null(t_vars *vars);
int		init_textures(t_vars *vars);
int		init_tables(t_vars *vars);
void	init_events(t_vars *vars);

static void	set_angles(t_angle *angle)
{
	angle->angle60 = WIDTH;
	angle->angle30 = (angle->angle60 >> 1);
	angle->angle15 = (angle->angle30 >> 1);
	angle->angle90 = (angle->angle30 * 3);
	angle->angle180 = (angle->angle90 << 1);
	angle->angle270 = (angle->angle90 * 3);
	angle->angle360 = (angle->angle60 * 6);
	angle->angle0 = 0;
	angle->angle5 = (angle->angle30 / 3);
	angle->angle10 = (angle->angle5 >> 1);
	angle->angle45 = (angle->angle15 * 3);
}

static void	set_point_of_view(t_vars *vars, char c)
{
	if (c == 'E')
		vars->camera.pov = vars->angle.angle0;
	else if (c == 'S')
		vars->camera.pov = vars->angle.angle90;
	else if (c == 'W')
		vars->camera.pov = vars->angle.angle180;
	else
		vars->camera.pov = vars->angle.angle270;
}

static void	set_camera_pos(t_vars *vars)
{
	char	*line;
	int		x;
	int		y;

	y = -1;
	while (++y < vars->map.field.size)
	{
		x = -1;
		line = vars->map.field.arr[y];
		while (line[++x])
		{
			if (line[x] == 'N' || line[x] == 'S'
				|| line[x] == 'W' || line[x] == 'E')
			{
				vars->camera.x = x * vars->block_width
					+ (vars->block_width >> 1);
				vars->camera.y = y * vars->block_width
					+ (vars->block_width >> 1);
				set_point_of_view(vars, line[x]);
				return ;
			}
		}
	}
}

static void	set_defaults(t_vars *vars)
{
	vars->block_width = WIDTH / 5;
	vars->block_height = WIDTH / 5;
	vars->moveWS = 0;
	vars->moveAD = 0;
	vars->rotate = 0;
	vars->camera.focal_length = (WIDTH >> 1) / tan(FIELD_OF_VIEW * M_PI / 360);
	vars->camera.height = (HEIGHT >> 1);
	vars->camera.move_speed = (vars->block_width >> 4);
	vars->camera.rotate_speed = (vars->angle.angle5 >> 3);
	vars->camera.cy = (HEIGHT >> 1);
	set_camera_pos(vars);
}

int	vars_init(t_vars *vars)
{
	set_to_null(vars);
	set_angles(&vars->angle);
	set_defaults(vars);
	vars->mlx = mlx_init();
	if (!vars->mlx)
		return (-1);
	vars->back.img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->back.img || init_textures(vars) == -1)
		return (-1);
	vars->back.addr = mlx_get_data_addr(vars->back.img,
			&vars->back.bits_per_pixel, &vars->back.length, &vars->back.endian);
	vars->back.bits_per_pixel >>= 3;
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!vars->win || init_tables(vars) == -1
		|| init_sprite_lines(&vars->h_sls, 8) == -1
		|| init_sprite_lines(&vars->v_sls, 8) == -1
		|| queue_init(&vars->dq, 8) == -1)
		return (-1);
	init_events(vars);
	return (0);
}
