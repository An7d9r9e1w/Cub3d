/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 08:13:11 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/27 13:55:33 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <error.h>
#include <string_utils.h>
#include <map.h>

void	run_cub(t_map map);

void	check_args(int argc, char *argv)
{
	int	len;

	if (argc != 1)
		fatal(ENOARG);
	len = mstrlen(argv);
	if (len < 5 || mstrcmp(argv + len - 4, ".cub") || argv[len - 5] == '/')
		fatal(EINVARG);
}

int	main(int argc, char *argv[])
{
	t_map	map;

	check_args(argc - 1, argv[1]);
	if (map_init(&map) == -1)
		fatal(-1);
	map_read_from_file(&map, argv[1]);
	run_cub(map);
	return (0);
}
