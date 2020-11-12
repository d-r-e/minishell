/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 16:10:56 by asegovia          #+#    #+#             */
/*   Updated: 2020/02/27 12:23:56 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(t_sh *sh)
{
	char *str;

	(void)sh;
	str = malloc(sizeof(char) * MAXPATHLEN + 1);
	str[MAXPATHLEN] = 0;
	getcwd(str, MAXPATHLEN);
	ft_putstr(str);
	ft_putstr("\n");
	free(str);
	return (0);
}
