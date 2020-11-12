/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 11:09:44 by darodrig          #+#    #+#             */
/*   Updated: 2020/03/10 15:37:06 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	redir_open(t_sh *sh, t_comm *com)
{
	com->flag_file_in = 0;
	com->flag_file_out = 0;
	if (com->file_in)
	{
		com->flag_file_in = 1;
		if ((sh->fdin = open(com->file_in, O_RDONLY)) < 0)
		{
			ft_putstr(com->file_in);
			com->file_in = NULL;
			ft_putstr(": No existe el archivo o directorio\n");
		}
		dup2(sh->fdin, 0);
	}
	if (com->file_out)
	{
		com->flag_file_out = 1;
		if (com->redir[search_str_in_arr(com->file_out,
				com->redir) - 1][1] == '>')
			sh->fdout = open(com->file_out, O_CREAT | O_RDWR | O_APPEND, 0600);
		else
			sh->fdout = open(com->file_out, O_CREAT | O_RDWR | O_TRUNC, 0600);
		dup2(sh->fdout, 1);
	}
}

void
	redir_close(t_sh *sh, t_comm *com)
{
	int i;

	if (com->flag_file_out == 1 && com->file_out != NULL)
	{
		dup2(sh->stdo, 1);
		free(com->file_out);
		com->file_out = NULL;
	}
	if (com->flag_file_in == 1 && com->file_in != NULL)
	{
		dup2(sh->stdo, 0);
		free(com->file_in);
		com->file_in = NULL;
	}
	if (com->flag_file_out == 1 || com->flag_file_in == 1)
	{
		i = -1;
		while (com->redir && com->redir[++i])
			free(com->redir[i]);
		free(com->redir);
	}
	com->flag_file_in = 0;
	com->flag_file_out = 0;
}
