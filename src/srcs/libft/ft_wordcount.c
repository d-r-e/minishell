/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 15:49:55 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/25 15:15:15 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static	int
	getcount(char *s, int count, int c)
{
	while (*s)
	{
		if (*s == '\"')
		{
			s++;
			while (*s && *s != '\"')
				s++;
		}
		if (*s == '\'')
		{
			s++;
			while (*s && *s != '\'')
				s++;
		}
		if (*s == '\0')
			return (count);
		if (*s && (*(s - 1) != c && *s == c))
			count++;
		s++;
	}
	if (*(s - 1) != c)
		count++;
	return (count);
}

int
	ft_wordcount(char *s, char c)
{
	int count;

	count = 0;
	if (*s == '\0')
		return (0);
	s++;
	if (*s == '\0' && *(s - 1) != c)
		return (1);
	count = getcount(s, count, c);
	return (count);
}
