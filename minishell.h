/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:52:22 by darodrig          #+#    #+#             */
/*   Updated: 2020/07/01 09:08:39 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/param.h>
# include <sys/mount.h>
# include "srcs/libft/libft.h"
# include <signal.h>
# include <fcntl.h>
# include <sys/errno.h>
# define POS_PATHS 3
# define STDIN 0
# define STDOUT 1
# define SIDEOUT 0
# define SIDEIN 1

typedef struct	s_comm
{
	char			*command;
	char			*parstr;
	char			**params;
	char			*file_in;
	int				flag_file_in;
	char			*file_out;
	int				flag_file_out;
	char			**pipesplit;
	char			**redir;
	struct s_comm	*sub;
	int				pipes[2];
}				t_comm;

typedef struct	s_shell
{
	int		exit;
	char	*commands[7];
	char	*string;
	char	**split;
	int		argc;
	char	**argv;
	char	**envp;
	char	*path;
	char	*possible_paths[POS_PATHS];
	char	**pos_paths;
	t_comm	*com;
	int		dquotes;
	int		squotes;
	int		bar;
	int		pipe;
	int		stdi;
	int		stdo;
	int		exitvalue;
	int		fdin;
	int		fdout;
	int		bckin;
	int		bckout;
	int		status;
	int		ok;
	int		pid;
	int		pathcount;
}				t_sh;

char			*add_char(char b, char *str);
int				ft_echo(char **args, t_sh *sh);
int				ft_cd(t_sh *sh, char **args);
int				ft_exit(t_sh *sh, char **args);
int				ft_env(t_sh *sh, t_comm *sub);
int				ft_export(t_sh *sh, t_comm *sub);
int				ft_unset(t_sh *sh, t_comm *com);
int				commands(const char *s, t_sh *sh);
int				get_commands(t_sh *sh);
void			init_function(t_sh *sh);
int				ft_pwd(t_sh *sh);
int				ft_parse(t_sh *sh);
char			*get_var(char *var, char **env);
int				parse_com(t_comm *com, int n);
int				array_counter(char **arr);
void			envp_dup(t_sh *sh, char **envp);
void			swap_var(t_comm *com, t_sh *sh);
int				set_special_chars(t_sh *sh, char c);
void			free_vars(t_sh *sh);
char			**add_var(t_sh *sh, char *var);
int				search_str_in_arr(char *str, char **arr);
int				substitute_var_in_env(t_sh *sh, char *var);
void			print_array(char **arr);
void			set_var(char **s, t_sh *sh);
int				run_built_in(t_comm *com, t_sh *sh, int i);
void			array_trim(char **arr, char *set);
void			find_redirections(t_comm *com);
void			redir_open(t_sh *sh, t_comm *com);
void			redir_close(t_sh *sh, t_comm *com);
int				init_com(t_comm *com);
char			**new_params(t_comm *com, int i, int n);
int				print_not_found(t_sh *sh, const char *s);
int				run_comms(t_comm *com, t_sh *sh, int i);
void			ft_son(t_sh *sh, t_comm *com, int len, int i);
void			ft_father(t_sh *sh, t_comm *com, int len, int i);
void			init_paths(t_sh *sh);
void			append_toall(char **arr, char *str);
void			add_str_to_arr(char **arr, char *str);
void			ft_debug(const char *str, int n);
int				run_ours(t_sh *sh, t_comm *com, int i);
#endif
