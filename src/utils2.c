/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:50:54 by darodrig          #+#    #+#             */
/*   Updated: 2020/06/30 13:25:32 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	print_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_putstr(arr[i]);
		ft_putstr("\n");
		i++;
	}
}

void
	array_trim(char **arr, char *set)
{
	int		i;
	char	*aux;

	i = 0;
	while (arr[i] != NULL)
	{
		aux = ft_strtrim(arr[i], set);
		free(arr[i]);
		arr[i] = aux;
		i++;
	}
}

void
	append_toall(char **arr, char *str)
{
	int		len;
	int		i;
	char	*temp;

	len = array_counter(arr);
	i = -1;
	while (++i < len)
	{
		temp = ft_strjoin(arr[i], str);
		free(arr[i]);
		arr[i] = temp;
	}
}

void
	add_str_to_arr(char **arr, char *str)
{
	char	**temp;
	int		max;
	int		i;

	max = array_counter(arr);
	temp = malloc(sizeof(char*) * (array_counter(arr) + 2));
	i = 0;
	while (i < max)
	{
		temp[i] = arr[i];
		i++;
	}
	temp[i] = ft_strdup(str);
	temp[i + 1] = NULL;
	print_array(temp);
	arr = temp;
}

void
	ft_debug(const char *str, int n)
{
	ft_putstr(str);
	ft_putstr(" ");
	ft_putnbr_fd(n, 1);
	ft_putstr("\n");
}
