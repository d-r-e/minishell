/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:35:34 by darodrig          #+#    #+#             */
/*   Updated: 2020/03/10 16:37:57 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	parse_com(t_comm *com, int n)
{
	int		i;
	int		len;
	char	**aux;

	i = 0;
	len = 0;
	if (com->pipesplit && com->pipesplit[n])
		len = ft_strlen(com->pipesplit[n]);
	while (com->pipesplit[n][i] != ' ' && com->pipesplit[n][i] != '\0')
		i++;
	com->sub[n].command = ft_substr(com->pipesplit[n], 0, i);
	while (ft_isspace(com->pipesplit[n][i]))
		i++;
	com->sub[n].parstr = ft_substr(com->pipesplit[n], i, len - i);
	find_redirections(&com->sub[n]);
	com->sub[n].params = ft_split2(com->sub[n].parstr, ' ');
	aux = new_params(com, 1 + array_counter(com->sub[n].params), n);
	free(com->sub[n].params);
	free(com->pipesplit[n]);
	com->sub[n].params = aux;
	return (0);
}

void
	command_trim(t_sh *sh)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	while (sh->split[i])
	{
		j = 0;
		while (sh->com[i].pipesplit[j])
		{
			aux = ft_strtrim(sh->com[i].pipesplit[j], " \t");
			free(sh->com[i].pipesplit[j]);
			sh->com[i].pipesplit[j] = aux;
			j++;
		}
		i++;
	}
}

int
	get_commands(t_sh *sh)
{
	int	i;

	i = 0;
	sh->split = ft_split2(sh->string, ';');
	while (sh->split[i])
		i++;
	sh->com = malloc(sizeof(t_comm) * (i + 1));
	i = 0;
	while (sh->split[i])
	{
		sh->com[i].pipesplit = ft_split2(sh->split[i], '|');
		i++;
	}
	command_trim(sh);
	return (0);
}

char
	**new_params(t_comm *com, int i, int n)
{
	char	**new;
	int		j;

	new = malloc(sizeof(char*) * (i + 2));
	new[0] = ft_strdup("");
	j = 0;
	while (j < i)
	{
		new[j + 1] = com->sub[n].params[j];
		j++;
	}
	new[j + 1] = NULL;
	return (new);
}

int
	init_com(t_comm *com)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (com->pipesplit && com->pipesplit[i])
		i++;
	com->sub = malloc(sizeof(t_comm) * (i + 1));
	while (j < i)
	{
		parse_com(com, j);
		j++;
	}
	return (0);
}
