/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 08:19:09 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 10:55:55 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/errno.h>
#include <string.h>

#include <error.h>
#include <string_utils.h>

#define EUNDEF_M "Undefined error"
#define ENOARG_M "Wrong number of arguments: must be only one"
#define EINVARG_M "Invalid argument: must be: *.cub"
#define EINVPARAM_M "Invalid parameter"
#define EEMPTYPARAM_M "Empty parameter"
#define ENOPARAM_M "Wrong number of parameters"
#define EDUPPARAM_M "Duplicate parameters"
#define EINVCOLOR_M "Invalid color"
#define ENOFIELD_M "Empty map"
#define EINVFIELD_M "Invalid map"
#define EPLR_M "Wrong number of player's position"
#define EUCLSFIELD_M "Map is unclosed"
#define EDOOR_M "A not surrounded door found"

void	fatal(int errnum)
{
	const char	*msgs[] = {EUNDEF_M, ENOARG_M, EINVARG_M, EINVPARAM_M,
		EEMPTYPARAM_M, ENOPARAM_M, EDUPPARAM_M, EINVCOLOR_M, ENOFIELD_M,
		EINVFIELD_M, EPLR_M, EUCLSFIELD_M, EDOOR_M};
	char		*msg;

	if (errnum < 0)
		msg = strerror(errno);
	else if (errnum < (int) sizeof(msgs))
		msg = (char *)msgs[errnum];
	else
		msg = EUNDEF_M;
	write(2, "Error\n", 6);
	write(2, msg, mstrlen(msg));
	write(2, "\n", 1);
	if (errnum == -1)
		exit(errno);
	exit(errnum);
}
