/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 10:03:20 by nnamor            #+#    #+#             */
/*   Updated: 2021/08/17 12:00:14 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <string_utils.h>
#include <char_checkers.h>

int	mstrcmp(const char *s1, const char *s2)
{
	if (!s1 || !s2)
		return ((int)(s1 - s2));
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

char	*mstrndup(const char *str, unsigned int n)
{
	char			*dup;
	char			*p;
	unsigned int	len;

	len = mstrlen(str) + 1;
	if (len > n)
		len = n;
	dup = malloc(len);
	if (!dup)
		return (NULL);
	p = dup;
	if (str)
		while (len--)
			*p++ = *str++;
	*p = 0;
	return (dup);
}

int	is_empty(char *str)
{
	while (*str)
		if (!is_space(*str++))
			return (0);
	return (1);
}

char	*trim(const char *s1)
{
	int	len;

	s1 = skip_spaces(s1);
	len = mstrlen(s1) - 1;
	while (is_space(s1[len]))
		--len;
	return (mstrndup(s1, len + 1));
}
