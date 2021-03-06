/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 20:35:32 by asyed             #+#    #+#             */
/*   Updated: 2018/04/20 10:20:36 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
** Are unset and export really just aliases?
*/

struct s_builtins	builtins[] = {
	{"cd", &builtin_cd},
	{"echo", &builtin_echo},
	{"fg", &builtin_fg},
	{"bg", &builtin_bg},
	{"jobs", &builtin_jobs},
	{"env", &builtin_env},
	{"history", &builtin_history},
	{"getenv", &builtin_getenv},
	{"setenv", &builtin_setenv},
	{"unsetenv", &builtin_unsetenv},
	{"unset", &builtin_unsetenv},
	{"export", &builtin_setenv},
	{NULL, NULL},
};

void	restore_fds(int *backup)
{
	dup2(backup[0], STDIN_FILENO);
	dup2(backup[1], STDOUT_FILENO);
	dup2(backup[2], STDERR_FILENO);
	meta_free(backup);
}

void	backup_fds(int **backup)
{
	if (!(*backup = ft_memalloc(sizeof(int) * 3)))
		return ;
	(*backup)[0] = dup(STDIN_FILENO);
	(*backup)[1] = dup(STDOUT_FILENO);
	(*backup)[2] = dup(STDERR_FILENO);
}

void	set_fds(t_process *info)
{
	dup2(*(info->stdin), STDIN_FILENO);
	dup2(*(info->stdout), STDOUT_FILENO);
	dup2(*(info->stderr), STDERR_FILENO);
}

int		builtin_handler(t_ast *curr, t_environ *env)
{
	int i;
	int	*backup;

	i = 0;
	backup_fds(&backup);
	if (handle_redirection(curr))
		return (EXIT_FAILURE);
	while (builtins[i].name)
	{
		if (!ft_strcmp(builtins[i].name, *(curr->token)))
		{
			set_fds(curr->p_info);
			i = builtins[i].exec(curr->token, env);
			restore_fds(backup);
			return (i);
		}
		i++;
	}
	restore_fds(backup);
	return (-1);
}
