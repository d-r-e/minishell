/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:08:29 by darodrig          #+#    #+#             */
/*   Updated: 2020/06/30 13:24:41 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_char(char b, char *str)
{
	char	*aux;
	int		i;

	i = 0;
	if (!(aux = malloc(sizeof(char) * ft_strlen(str) + 2)))
		return (0);
	while (str[i] != '\0')
	{
		aux[i] = str[i];
		i++;
	}
	aux[ft_strlen(str)] = b;
	aux[ft_strlen(str) + 1] = '\0';
	return (aux);
}

int		init_struct(t_sh *sh, int argc, char **argv, char **envp)
{
	sh->exit = 0;
	sh->argc = argc;
	sh->argv = argv;
	envp_dup(sh, envp);
	sh->pathcount = 0;
	init_paths(sh);
	sh->commands[0] = ft_strdup("pwd");
	sh->commands[1] = ft_strdup("echo");
	sh->commands[2] = ft_strdup("cd");
	sh->commands[3] = ft_strdup("export");
	sh->commands[4] = ft_strdup("env");
	sh->commands[5] = ft_strdup("unset");
	sh->commands[6] = ft_strdup("exit");
	sh->dquotes = 0;
	sh->squotes = 0;
	sh->bar = 0;
	sh->stdi = dup(0);
	sh->stdo = dup(1);
	sh->exitvalue = 0;
	return (0);
}

void	exit_signal(int sig)
{
	(void)sig;
	ft_putstr("\n\033[0;35mMinishell% \033[0m");
	signal(sig, &exit_signal);
}

void	ctrl_d(int rd)
{
	if (rd == 0)
	{
		ft_putstr("exit\n");
		exit(0);
	}
}

int		main(int argc, char **argv, char **envp)
{
	char	*aux;
	char	b;
	t_sh	sh;
	int		rd;

	init_struct(&sh, argc, argv, envp);
	signal(SIGINT, &exit_signal);
	signal(SIGQUIT, &exit_signal);
	while (sh.exit == 0)
	{
		ft_putstr("\033[0;35mMinishell% \033[0m");
		sh.string = ft_strdup("");
		b = 0;
		while ((rd = read(0, &b, 1)) != -1)
		{
			if (b == '\n' || b == 0)
				break ;
			aux = add_char(b, sh.string);
			free(sh.string);
			sh.string = aux;
		}
		ctrl_d(rd);
		ft_parse(&sh);
		free(sh.string);
	}
}
