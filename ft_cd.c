/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 14:33:14 by darodrig          #+#    #+#             */
/*   Updated: 2020/03/10 16:03:14 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	update_env(t_sh *sh)
{
	char *path;
	char *aux;

	path = malloc(sizeof(char) * MAXPATHLEN + 1);
	path[MAXPATHLEN] = 0;
	getcwd(path, MAXPATHLEN);
	aux = ft_strjoin("PWD=", path);
	substitute_var_in_env(sh, aux);
	free(aux);
	free(path);
}

int
	ft_cd(t_sh *sh, char **args)
{
	int		i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putstr("cd: too many arguments\n");
		return (-1);
	}
	if (i == 1 || ft_strcmp(args[1], "~") == 0)
	{
		if (chdir(get_var("HOME", sh->envp)) == 0)
		{
			update_env(sh);
			return (0);
		}
	}
	else if (i == 2 && chdir(args[1]) == 0)
	{
		update_env(sh);
		return (0);
	}
	ft_putstr("Error: No such file or directory\n");
	return (-1);
}
