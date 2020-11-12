/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:42:01 by darodrig          #+#    #+#             */
/*   Updated: 2020/03/09 17:33:22 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	echo_print(char **args, int i, t_sh *sh)
{
	int j;

	while (args[i])
	{
		j = -1;
		while (args[i][++j])
		{
			set_special_chars(sh, args[i][j]);
			if (args[i][j] == '\"' && sh->squotes == 1 && sh->dquotes == 0
				&& sh->bar == 0)
				ft_putchar_fd(args[i][j], 1);
			else if (args[i][j] != '\"' && args[i][j] != '\\' &&
				args[i][j] != '\'' && sh->bar == 0)
				ft_putchar_fd(args[i][j], 1);
			else if (args[i][j] == '\'' && sh->squotes == 0 && sh->dquotes == 1
				&& sh->bar == 0)
				ft_putchar_fd(args[i][j], 1);
			else if (args[i][j] == '\\' && sh->bar == 0)
				ft_putchar_fd(args[i][j], 1);
		}
		i++;
		if (args[i])
			ft_putstr(" ");
	}
}

int
	ft_echo(char **args, t_sh *sh)
{
	int i;
	int	no_nl;

	if (!args[1])
	{
		ft_putstr("\n");
		return (0);
	}
	i = 1;
	no_nl = 0;
	if (ft_strcmp(args[1], "-n") == 0)
	{
		i = i + 1;
		no_nl = 1;
	}
	echo_print(args, i, sh);
	if (no_nl == 0)
		ft_putstr("\n");
	return (0);
}
