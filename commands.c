/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:00:40 by darodrig          #+#    #+#             */
/*   Updated: 2020/07/01 09:08:07 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	init_run(t_sh *sh, int *i, int *len, t_comm *com)
{
	*len = 0;
	sh->ok = EXIT_SUCCESS;
	if (com->pipesplit)
		*len = array_counter(com->pipesplit);
	*i = -1;
}

void
	run(t_comm *com, t_sh *sh)
{
	int i;
	int len;

	init_run(sh, &i, &len, com);
	while (com->pipesplit && com->pipesplit[++i] != NULL)
	{
		swap_var(&com->sub[i], sh);
		if (run_ours(sh, com, i))
			break ;
		if (len > 1)
			pipe(com->sub[i].pipes);
		com->flag_file_in = 0;
		com->flag_file_out = 0;
		sh->pid = fork();
		if (sh->pid == 0)
			ft_son(sh, com, len, i);
		else
			ft_father(sh, com, len, i);
		redir_close(sh, &com->sub[i]);
	}
}

int
	run_built_in(t_comm *com, t_sh *sh, int i)
{
	char	*command;
	int		c;
	int		j;

	init_paths(sh);
	j = 0;
	if ((c = -1) && !sh->pathcount && print_not_found(sh, com->sub[i].command))
		return (0);
	while (c == -1 && j < sh->pathcount + 1)
	{
		if (j == sh->pathcount)
			command = ft_strdup(com->sub[i].command);
		else
			command = ft_strjoin(sh->pos_paths[j], com->sub[i].command);
		j++;
		array_trim(com->sub[i].params, "\"\'");
		free(command);
		c = execve(command, com->sub[i].params, sh->envp);
		if (j == sh->pathcount + 1 && c == -1)
			print_not_found(sh, com->sub[i].command);
		if (j == sh->pathcount + 1 && c == -1)
			exit(127);
	}
	return (0);
}

void
	free_all(t_comm *com)
{
	int i;
	int j;

	i = 0;
	while (com->pipesplit && com->pipesplit[i])
	{
		free(com->sub[i].command);
		j = -1;
		while (com->sub[i].params && com->sub[i].params[++j])
		{
			free(com->sub[i].params[j]);
		}
		free(com->sub[i].params);
		free(com->sub[i].parstr);
		i++;
	}
	if (i > 0)
		free(com->pipesplit);
	free(com->sub);
}

int
	ft_parse(t_sh *sh)
{
	int ret;
	int	i;

	ret = 0;
	ret -= get_commands(sh);
	i = 0;
	while (sh->split && sh->split[i])
	{
		init_com(&sh->com[i]);
		run(&sh->com[i], sh);
		free_all(&sh->com[i]);
		free(sh->split[i]);
		i++;
	}
	free(sh->com);
	free(sh->split);
	return (ret);
}
