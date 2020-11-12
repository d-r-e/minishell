/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 12:11:02 by asegovia          #+#    #+#             */
/*   Updated: 2020/07/01 08:57:02 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	check_var(t_sh *sh, char *str)
{
	int i;
	int ret;

	i = 0;
	if ((ret = ft_isalpha(str[0])) == 0)
		return (-1);
	while ((ret = ft_isalnum(str[i])) == 1)
	{
		i++;
		if (str[i] == '=')
		{
			if (substitute_var_in_env(sh, str) == 1)
				return (0);
			return (1);
		}
		if (!str[i])
			return (0);
	}
	return (-1);
}

int
	substitute_var_in_env(t_sh *sh, char *var)
{
	int		i;
	char	*half_var;
	int		pos;

	i = 0;
	pos = 0;
	while (var[i] && var[i] != '=')
		i++;
	half_var = ft_substr(var, 0, i + 1);
	pos = search_str_in_arr(half_var, sh->envp);
	if (pos == 0)
	{
		free(half_var);
		return (0);
	}
	free(sh->envp[pos]);
	free(half_var);
	sh->envp[pos] = ft_strdup(var);
	return (1);
}

char
	**add_var(t_sh *sh, char *var)
{
	char	**temp;
	int		i;

	i = 0;
	temp = malloc(sizeof(char *) * (array_counter(sh->envp) + 2));
	while (sh->envp[i])
	{
		temp[i] = sh->envp[i];
		i++;
	}
	temp[i] = var;
	temp[i + 1] = NULL;
	return (temp);
}

int
	ft_export(t_sh *sh, t_comm *sub)
{
	int		i;
	char	*aux;
	char	**temp;

	i = 0;
	while (sub->params[++i])
	{
		aux = ft_strtrim(sub->params[i], " \'\"");
		if (check_var(sh, aux) == 0)
			free(aux);
		else if (check_var(sh, aux) == 1 && (temp = add_var(sh, aux)))
		{
			free(sh->envp);
			sh->envp = temp;
		}
		else if (check_var(sh, aux) == -1)
		{
			ft_putstr("export: `");
			ft_putstr(aux);
			free(aux);
			ft_putstr("\': not a valid identifier\n");
		}
	}
	return (0);
}
