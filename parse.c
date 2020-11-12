/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:30:15 by darodrig          #+#    #+#             */
/*   Updated: 2020/03/10 16:55:51 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	swap_var(t_comm *com, t_sh *sh)
{
	int i;

	i = 1;
	set_var(&com->command, sh);
	while (com->params[i] != NULL)
	{
		set_var(&com->params[i], sh);
		i++;
	}
}

int
	set_var_aux(int j, char **s, t_sh *sh, int i)
{
	char *var;
	char *aux;
	char *aux2;

	if (s[0][1] == '?' && (aux = ft_itoa(WEXITSTATUS(sh->status))))
		j++;
	else
	{
		while (ft_isalnum(s[0][i + j]) == 1)
			j++;
		var = ft_substr(&s[0][i], 0, j);
		aux = get_var(var, sh->envp);
		free(var);
	}
	if (aux == NULL)
		aux = "";
	var = ft_substr(s[0], 0, i - 1);
	aux2 = ft_strjoin(var, aux);
	free(var);
	var = ft_strjoin(aux2, &s[0][i + j]);
	free(s[0]);
	free(aux2);
	s[0] = var;
	return (j);
}

void
	set_var(char **s, t_sh *sh)
{
	int i;
	int	j;

	j = 0;
	i = -1;
	while (s[0][++i])
	{
		set_special_chars(sh, s[0][i]);
		if (((sh->squotes == 0 && sh->dquotes == 1 && sh->bar == 0) ||
			(sh->squotes == 1 && sh->dquotes == 1 && sh->bar == 0) ||
			(sh->squotes == 0 && sh->dquotes == 0 && sh->bar == 0)) &&
			s[0][i] == '$')
		{
			i++;
			i += set_var_aux(j, s, sh, i);
		}
		else if (sh->bar == 1 && s[0][i] != '\\')
			sh->bar = 0;
	}
}
