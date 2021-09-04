/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 08:44:45 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 18:08:03 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <vars_bonus.h>
#include <sprite_line_bonus.h>

void	get_sprite_line(t_vars *vars, t_sprite_line *sprite_line,
			int angle, int colm);
void	draw_floor_and_cell(t_vars *vars);
void	draw_minimap(t_vars *vars);
void	draw_vertical_line(t_vars *vars, int x, t_sprite_line *sl);
void	draw_vertical_line_transparent(t_vars *vars, int x, t_sprite_line *sl);

static void	draw_rest_sprites(t_vars *vars, float wall_dist, int colm)
{
	while (vars->h_sls.size || vars->v_sls.size)
	{
		if (!vars->v_sls.size || (vars->h_sls.size
				&& vars->h_sls.arr[vars->h_sls.size - 1].dist
				> vars->v_sls.arr[vars->v_sls.size - 1].dist))
		{
			if (vars->h_sls.arr[--vars->h_sls.size].dist <= wall_dist)
				draw_vertical_line_transparent(vars, colm,
					vars->h_sls.arr + vars->h_sls.size);
		}
		else if (vars->v_sls.arr[--vars->v_sls.size].dist <= wall_dist)
			draw_vertical_line_transparent(vars, colm,
				vars->v_sls.arr + vars->v_sls.size);
	}
}

static void	draw_sprites(t_vars *vars)
{
	const int		angle360 = vars->angle.angle360;
	t_sprite_line	sprite_line;
	int				colm;
	int				angle;

	angle = vars->camera.pov - vars->angle.angle30;
	if (angle < 0)
		angle += angle360;
	colm = -1;
	while (++colm < WIDTH)
	{
		get_sprite_line(vars, &sprite_line, angle, colm);
		draw_vertical_line(vars, colm, &sprite_line);
		if (vars->h_sls.size || vars->v_sls.size)
			draw_rest_sprites(vars, sprite_line.dist, colm);
		if (++angle >= angle360)
			angle -= angle360;
	}
}

void	render(t_vars *vars)
{
	draw_floor_and_cell(vars);
	draw_sprites(vars);
	draw_minimap(vars);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->back.img, 0, 0);
}
