/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:56:41 by darodrig          #+#    #+#             */
/*   Updated: 2020/03/10 15:58:02 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(t_sh *sh, char **args)
{
	if (!args[1])
		exit(0);
	else
		sh->exitvalue = ft_atoi(args[1]);
	sh->ok = 1;
	exit(sh->exitvalue);
}
