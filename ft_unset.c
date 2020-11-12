/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 14:08:38 by darodrig          #+#    #+#             */
/*   Updated: 2020/07/01 08:48:24 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	existe(t_sh *sh, const char *s)
{
	int		i;
	char	*aux;
	char	*saux;

	i = 0;
	while (sh->envp[i])
	{
		aux = ft_strjoin(sh->envp[i], "=");
		saux = ft_strjoin(s, "=");
		if (ft_strncmp(saux, aux, ft_strlen(saux)) == 0)
		{
			free(aux);
			free(saux);
			return (i);
		}
		else
		{
			free(saux);
			free(aux);
		}
		i++;
	}
	return (-1);
}

void
	free_vars(t_sh *sh)
{
	int i;

	i = array_counter(sh->envp);
	while (i > 0)
	{
		free(sh->envp[i - 1]);
		i--;
	}
}

void
	auxprint(char *str)
{
	if (ft_strchr(str, '='))
	{
		ft_putstr("unset: `");
		ft_putstr(str);
		ft_putstr(": not a valid identifier\n");
	}
}

void
	aux_loop(t_sh *sh, int pos)
{
	int		j;
	int		size;
	char	**new;

	j = 0;
	size = array_counter(sh->envp);
	new = malloc(sizeof(char*) * size);
	while (j < size - 1)
	{
		if (j >= pos)
			new[j] = ft_strdup(sh->envp[j + 1]);
		else
			new[j] = ft_strdup(sh->envp[j]);
		j++;
	}
	new[j] = NULL;
	free_vars(sh);
	free(sh->envp);
	sh->envp = new;
}

int
	ft_unset(t_sh *sh, t_comm *com)
{
	int		pos;
	int		i;

	i = 0;
	while (com->params && com->params[++i])
	{
		if ((pos = existe(sh, com->params[i])) != -1)
			aux_loop(sh, pos);
		else
			auxprint(com->params[i]);
	}
	return (0);
}
