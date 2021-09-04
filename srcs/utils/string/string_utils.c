/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:14 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/28 11:49:18 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string_utils.h>
#include <char_checkers.h>

int	mstrlen(const char *str)
{
	const char *const	begin = str;

	if (str)
		while (*str)
			str++;
	return (str - begin);
}

char	*skip_spaces(const char *str)
{
	if (str)
		while (is_space(*str))
			++str;
	return ((char *)str);
}

int	mstrlcpy(char *dst, const char *src, int dstsize)
{
	int	srcsize;

	if (!dst || !src)
		return (0);
	srcsize = mstrlen(src);
	if (dstsize > 0)
	{
		if (dstsize > srcsize + 1)
			dstsize = srcsize + 1;
		while (dstsize--)
			*dst++ = *src++;
		*dst = 0;
	}
	return (srcsize);
}

int	mstrncmp(const char *s1, const char *s2, unsigned int n)
{
	if (!s1 || !s2)
		return ((int)(s1 - s2));
	while (--n && *s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
