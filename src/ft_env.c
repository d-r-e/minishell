/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:10:34 by asegovia          #+#    #+#             */
/*   Updated: 2020/03/06 09:53:54 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(t_sh *sh, t_comm *sub)
{
	int i;

	i = 0;
	if (sub->params[1] != NULL)
	{
		ft_putstr("env: too many arguments\n");
		return (0);
	}
	while (sh->envp[i])
	{
		ft_putstr(sh->envp[i]);
		ft_putstr("\n");
		i++;
	}
	return (0);
}
