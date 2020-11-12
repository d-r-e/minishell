/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:39:22 by darodrig          #+#    #+#             */
/*   Updated: 2020/07/01 09:07:11 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	print_not_found(t_sh *sh, const char *s)
{
	ft_putstr("minishell: command not found: ");
	ft_putstr(s);
	ft_putstr("\n");
	sh->status = 127;
	return (1);
}

int
	run_comms(t_comm *com, t_sh *sh, int i)
{
	int ok;

	ok = -1;
	redir_open(sh, &com->sub[i]);
	if (ft_strcmp(com->sub[i].command, sh->commands[6]) == 0 && (ok = 1))
	{
		ft_exit(sh, com->sub[i].params);
		while (1)
			exit(sh->exitvalue);
	}
	if (ft_strcmp(com->sub[i].command, sh->commands[0]) == 0 && (ok = 1))
		ft_pwd(sh);
	if (ft_strcmp(com->sub[i].command, sh->commands[1]) == 0 && (ok = 1))
		ft_echo(com->sub[i].params, sh);
	if (ft_strcmp(com->sub[i].command, sh->commands[4]) == 0 && (ok = 1))
		ft_env(sh, &com->sub[i]);
	if (ft_strcmp(com->sub[i].command, sh->commands[5]) == 0 && (ok = 1))
		ft_unset(sh, &com->sub[i]);
	if (ft_strcmp(com->sub[i].command, sh->commands[3]) == 0 && (ok = 1))
		ft_export(sh, &com->sub[i]);
	if (ok == -1)
		run_built_in(com, sh, i);
	redir_close(sh, &com->sub[i]);
	return (ok);
}

void
	ft_son(t_sh *sh, t_comm *com, int len, int i)
{
	dup2(com->sub[i].pipes[SIDEIN], STDOUT);
	if (i > 0)
		dup2(com->sub[i - 1].pipes[SIDEOUT], STDIN);
	if (i == len - 1)
		dup2(sh->stdo, STDOUT);
	sh->ok = run_comms(com, sh, i);
	exit(sh->ok);
}

void
	ft_father(t_sh *sh, t_comm *com, int len, int i)
{
	waitpid(sh->pid, &sh->status, 0);
	com->flag_file_in = 0;
	com->flag_file_out = 0;
	if (len > 1)
	{
		close(com->sub[i].pipes[SIDEIN]);
		if (i == len)
			close(com->sub[i].pipes[SIDEOUT]);
		if (i > 0)
			close(com->sub[i - 1].pipes[SIDEOUT]);
		if (WIFEXITED(sh->status))
			sh->ok = WEXITSTATUS(sh->status);
	}
}

/*
** Returns 0 if no command was executed, 1 otherwise.
*/

int
	run_ours(t_sh *sh, t_comm *com, int i)
{
	if (ft_strcmp(com->sub[i].command, sh->commands[6]) == 0)
		ft_exit(sh, com->sub[i].params);
	else if (ft_strcmp(com->sub[i].command, sh->commands[2]) == 0)
	{
		ft_cd(sh, com->sub[i].params);
	}
	else if (ft_strcmp(com->sub[i].command, sh->commands[3]) == 0)
	{
		ft_export(sh, &com->sub[i]);
	}
	else if (ft_strcmp(com->sub[i].command, sh->commands[5]) == 0)
	{
		ft_unset(sh, &com->sub[i]);
	}
	else
		return (0);
	return (1);
}
