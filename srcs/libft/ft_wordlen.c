/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wordlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 14:32:34 by darodrig          #+#    #+#             */
/*   Updated: 2020/02/25 15:40:24 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns the length of a word in a string, until the first ocurrence of c.
*/

#include "libft.h"
#include <stdio.h>

int	ft_wordlen(char *s, char c)
{
	int count;

	count = 0;
	while (*s != '\0' && *s != c)
	{
		if (*s == '\"')
		{
			count++;
			s++;
			while (*s && *s != '\"' && (count = count + 1))
				s++;
		}
		if (*s == '\'')
		{
			s++;
			count++;
			while (*s && *s != '\'' && (count = count + 1))
				s++;
		}
		count++;
		if (*s == 0)
			return (count);
		s++;
	}
	return (count);
}
