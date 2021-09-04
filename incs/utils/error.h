/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 08:24:09 by nnamor            #+#    #+#             */
/*   Updated: 2021/09/02 10:59:15 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define EUNDEF 0
# define ENOARG 1
# define EINVARG 2
# define EINVPARAM 3
# define EEMPTYPARAM 4
# define ENOPARAM 5
# define EDUPPARAM 6
# define EINVCOLOR 7
# define ENOFIELD 8
# define EINVFIELD 9
# define EPLR 10
# define EUCLSFIELD 11
# define EDOOR 12

void	fatal(int errnum);

#endif	/*ERROR_H*/
