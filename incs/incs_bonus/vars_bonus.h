/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 08:08:36 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 16:49:28 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VARS_BONUS_H
# define VARS_BONUS_H

# include <map.h>
# include <data_bonus.h>
# include <sprite_lines_bonus.h>
# include <door_bonus.h>

# define FIELD_OF_VIEW 60

/*** Screen resolution ***/
# define WIDTH 1920//480
# define HEIGHT 1080//360

/*** Key codes ***/
# define ESC_KEY 53
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define W_KEY 13
# define LEFT_ARROW_KEY 123
# define RIGHT_ARROW_KEY 124
# define DOWN_ARROW_KEY 125
# define UP_ARROW_KEY 126

# define DEFAULT_SPRITE "textures/bat_sprite.xpm"
# define DEFAULT_DOOR "textures/door.xpm"

typedef struct s_angle
{
	int	angle0;
	int	angle5;
	int	angle10;
	int	angle15;
	int	angle30;
	int	angle45;
	int	angle60;
	int	angle90;
	int	angle180;
	int	angle270;
	int	angle360;
}	t_angle;

typedef struct s_camera
{
	int	x;
	int	y;
	int	pov;
	int	focal_length;
	int	height;
	int	move_speed;
	int	rotate_speed;
	int	cy;
}	t_camera;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_data			back;
	t_angle			angle;
	t_camera		camera;
	t_map			map;
	t_sprite_lines	h_sls;
	t_sprite_lines	v_sls;
	t_data			wall_N;
	t_data			wall_S;
	t_data			wall_E;
	t_data			wall_W;
	t_data			sprite;
	t_data			door;
	t_door_queue	dq;
	float			*sin_table;
	float			*cos_table;
	float			*tan_table;
	float			*fish_table;
	float			*x_step_table;
	float			*y_step_table;
	int				block_width;
	int				block_height;
	int				moveWS;
	int				moveAD;
	int				rotate;
}	t_vars;

int		vars_init(t_vars *vars);
void	vars_free(t_vars *vars);

#endif	/*VARS_BONUS_H*/
