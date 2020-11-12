/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 12:42:32 by asegovia          #+#    #+#             */
/*   Updated: 2020/06/30 13:11:58 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*get_var(char *var, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(var, env[i], ft_strlen(var)) == 0 &&
			env[i][ft_strlen(var)] == '=')
			return (&env[i][ft_strlen(var) + 1]);
		i++;
	}
	return (NULL);
}

void
	envp_dup(t_sh *sh, char **envp)
{
	int		i;
	int		size;
	char	**new;

	i = 0;
	size = array_counter(envp);
	new = malloc(sizeof(char*) * size + 1);
	while (i < size)
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = NULL;
	sh->envp = new;
}

int
	array_counter(char **arr)
{
	int i;

	i = 0;
	while (arr && arr[i] != NULL)
		i++;
	return (i);
}

int
	set_special_chars(t_sh *sh, char c)
{
	if (c == '\'' && sh->bar == 0)
	{
		sh->squotes = !sh->squotes;
	}
	else if (c == '\"' && sh->bar == 0 && sh->squotes == 0)
		sh->dquotes = !sh->dquotes;
	else if (c == '\\')
		sh->bar = !sh->bar;
	if (c != '\\' && sh->bar == 1 && c != '$')
		sh->bar = 0;
	if (sh->dquotes == 0 && sh->squotes == 0 && sh->bar == 0)
		return (1);
	if (sh->dquotes == 1 && sh->squotes == 0 && sh->bar == 0)
		return (1);
	if (sh->dquotes == 0 && sh->squotes == 1 && sh->bar == 0)
		return (1);
	return (0);
}

int
	search_str_in_arr(char *str, char **arr)
{
	int i;
	int var_len;

	var_len = ft_strlen(str);
	i = -1;
	while (arr[++i])
	{
		if (ft_strncmp(str, arr[i], var_len) == 0)
			return (i);
	}
	return (0);
}
