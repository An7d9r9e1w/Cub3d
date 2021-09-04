/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 10:17:49 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 12:08:09 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <mlx.h>
#include <vars_bonus.h>
#include <get_next_line.h>
#include <string_utils.h>

int		realloc_lines(char ***lines, int *capacity);
void	free_lines(char **lines, int size);
void	set_animation_options(t_vars *vars);

static int	check_line(char **lines, int size)
{
	int	len;

	if (*lines[size] == '\"')
	{
		len = mstrlen(lines[size]) - 1;
		lines[size][len - (lines[size][len - 1] == '\"')] = '\0';
		++lines[size];
		return (1);
	}
	free(lines[size]);
	return (0);
}

static int	read_xpm(int fd, char ***lines, int capacity)
{
	char	**tmp;
	int		size;
	int		stat;

	size = 0;
	stat = 1;
	tmp = *lines;
	while (stat > 0)
	{
		stat = get_next_line(fd, tmp + size);
		if (stat == -1 || (size + 1 == capacity
				&& realloc_lines(&tmp, &capacity) == -1))
		{
			free_lines(tmp, size);
			return (-1);
		}
		if (check_line(tmp, size))
			++size;
	}
	*lines = tmp;
	return (size);
}

static void	*xpm_file_to_image(void *mlx, char *path, int *width, int *height)
{
	void	*img;
	char	**lines;
	int		size;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	lines = malloc(sizeof(void *) * 128);
	if (!lines)
	{
		close(fd);
		return (NULL);
	}
	size = read_xpm(fd, &lines, 128);
	close(fd);
	if (size == -1)
		return (NULL);
	img = mlx_xpm_to_image(mlx, lines, width, height);
	free_lines(lines, size);
	return (img);
}

static void	set_addrs(t_vars *vars)
{
	vars->wall_N.addr = mlx_get_data_addr(vars->wall_N.img,
			&vars->wall_N.bits_per_pixel, &vars->wall_N.length,
			&vars->wall_N.endian);
	vars->wall_S.addr = mlx_get_data_addr(vars->wall_S.img,
			&vars->wall_S.bits_per_pixel, &vars->wall_S.length,
			&vars->wall_S.endian);
	vars->wall_W.addr = mlx_get_data_addr(vars->wall_W.img,
			&vars->wall_W.bits_per_pixel, &vars->wall_W.length,
			&vars->wall_W.endian);
	vars->wall_E.addr = mlx_get_data_addr(vars->wall_E.img,
			&vars->wall_E.bits_per_pixel, &vars->wall_E.length,
			&vars->wall_E.endian);
	vars->sprite.addr = mlx_get_data_addr(vars->sprite.img,
			&vars->sprite.bits_per_pixel, &vars->sprite.length,
			&vars->sprite.endian);
	vars->door.addr = mlx_get_data_addr(vars->door.img,
			&vars->door.bits_per_pixel, &vars->door.length,
			&vars->door.endian);
	vars->wall_N.bits_per_pixel >>= 3;
	vars->wall_S.bits_per_pixel >>= 3;
	vars->wall_W.bits_per_pixel >>= 3;
	vars->wall_E.bits_per_pixel >>= 3;
	vars->sprite.bits_per_pixel >>= 3;
	vars->door.bits_per_pixel >>= 3;
}

int	init_textures(t_vars *vars)
{
	vars->wall_N.img = xpm_file_to_image(vars->mlx, vars->map.no_path,
			&vars->wall_N.width, &vars->wall_N.height);
	if (vars->wall_N.img)
		vars->wall_S.img = xpm_file_to_image(vars->mlx, vars->map.so_path,
				&vars->wall_S.width, &vars->wall_S.height);
	if (vars->wall_S.img)
		vars->wall_W.img = xpm_file_to_image(vars->mlx, vars->map.we_path,
				&vars->wall_W.width, &vars->wall_W.height);
	if (vars->wall_W.img)
		vars->wall_E.img = xpm_file_to_image(vars->mlx, vars->map.ea_path,
				&vars->wall_E.width, &vars->wall_E.height);
	if (vars->wall_E.img)
		vars->sprite.img = xpm_file_to_image(vars->mlx, DEFAULT_SPRITE,
				&vars->sprite.width, &vars->sprite.height);
	if (vars->sprite.img)
		vars->door.img = xpm_file_to_image(vars->mlx, DEFAULT_DOOR,
				&vars->door.width, &vars->door.height);
	if (!vars->door.img)
		return (-1);
	set_addrs(vars);
	set_animation_options(vars);
	return (0);
}
