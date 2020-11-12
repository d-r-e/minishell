/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 10:22:35 by darodrig          #+#    #+#             */
/*   Updated: 2020/06/30 13:46:27 by darodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_paths(t_sh *sh)
{
	char	*path;

	sh->pathcount = array_counter(sh->pos_paths);
	path = get_var("PATH", sh->envp);
	sh->pos_paths = ft_split(path, ':');
	append_toall(sh->pos_paths, "/");
	sh->pathcount = array_counter(sh->pos_paths);
}
