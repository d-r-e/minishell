/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 16:20:21 by darodrig          #+#    #+#             */
/*   Updated: 2020/03/10 15:38:52 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	split_redit_aux(char *str, t_comm *com)
{
	int i;
	int j;
	int c;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i + 1] == '>' && (i += 1))
				com->redir[j] = ft_strdup(">>");
			else
				com->redir[j] = ft_substr(str, i, 1);
		}
		else
		{
			c = 0;
			while (str[i + c] != '>' && str[i + c] != '<' && str[i + c] != '\0')
				c++;
			com->redir[j] = ft_substr(str, i, c);
			i += c - 1;
		}
		j++;
	}
}

static void
	split_redir(char *str, t_comm *com)
{
	int i;
	int c;

	i = -1;
	c = 0;
	while (str[++i])
	{
		if ((str[i] == '>' || str[i] == '<') && (c = c + 1))
		{
			if (str[i + 1] == '>')
				i++;
		}
	}
	if (c == 0)
		return ;
	com->redir = (char**)malloc(sizeof(char*) * (c * 2 + 1));
	com->redir[c * 2] = NULL;
	split_redit_aux(str, com);
	array_trim(com->redir, " \'\"");
}

void
	check_redirections(t_comm *com)
{
	int i;

	i = -1;
	if (!com->redir)
		return ;
	while (com->redir[++i])
	{
		if (com->redir[i][0] == '<' && com->redir[i + 1] &&
				com->file_in == NULL)
			com->file_in = ft_strdup(com->redir[i + 1]);
		else if (com->redir[i][0] == '>' && com->redir[i + 1] &&
				com->redir[i + 2] == NULL)
			com->file_out = ft_strdup(com->redir[i + 1]);
		else if (com->redir[i][0] == '>' && com->redir[i + 1])
		{
			if (com->redir[i][1] == '>')
				close(open(com->redir[i + 1], O_CREAT | O_APPEND, 0666));
			else
				close(open(com->redir[i + 1], O_CREAT | O_TRUNC, 0666));
		}
	}
	i = -1;
}

void
	find_redirections(t_comm *com)
{
	int i;
	int redir;

	i = 0;
	redir = 0;
	while (com->parstr && com->parstr[i])
	{
		if (com->parstr[i] == '>' || com->parstr[i] == '<')
		{
			split_redir(&com->parstr[i], com);
			com->parstr[i] = '\0';
			redir = 1;
			break ;
		}
		i++;
	}
	com->file_in = NULL;
	com->file_out = NULL;
	if (redir == 1)
		check_redirections(com);
}
