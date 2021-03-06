/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:16:12 by asyed             #+#    #+#             */
/*   Updated: 2018/04/20 12:52:29 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include "ft_proto.h"

struct s_ophandlers	op_handlers[] = {
	{&op_pipe_check, &op_pipe_exec},
	{&op_or_check, &op_or_exec},
	{&op_and_check, &op_and_exec},
	{NULL, NULL},
};

struct s_ophijackhandlers	ophijack_handlers[] = {
	{&op_or_check, &op_or_exec_hijacked},
	{&op_and_check, &op_and_exec_hijacked},
	{NULL, NULL},
};

static void	child_offload(t_ast *curr, t_environ *env)
{
	exec_init(curr);
	execvP(*(curr->token), ft_getenv("PATH", env), curr->token);
	ft_printf("Error: %s: %s\n", ft_strerror(errno), *(curr->token));
	exit(EXIT_FAILURE);
}

int			run_pipecmds(t_stack *cmd, t_pqueue *pids, t_environ *env)
{
	int		pid;
	int		res;
	t_ast	*process;

	if (!cmd || isempty_stack(cmd) || !(process = ft_stackpop(cmd)))
		return (EXIT_SUCCESS);
	relative_hook(process, env);
	if ((res = builtin_handler(process, env)) != -1)
	{
		parent_pipes(process);
		return (res);
	}
	if ((pid = fork()) == -1)
		return (EXIT_FAILURE);
	if (!pid)
		child_offload(process, env);
	parent_pipes(process);
	ft_enpqueue(pids, &pid, sizeof(int), (int (*)(void *, void *))&compare);
	run_pipecmds(cmd, pids, env);
	return (EXIT_SUCCESS);
}

int			handle_suspend(pid_t *pid, t_ast *curr)
{
	t_jobspec	job;

	if (!(job.pids = new_stack()))
		return (EXIT_FAILURE);
	if (ft_stackpush(job.pids, pid, sizeof(pid_t)) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	job.name = ft_strdup(*(curr->token));
	add_suspended(&job);
	return (EXIT_SUCCESS);
}

int			run_operation(t_ast *curr, uint8_t wait, t_environ *env)
{
	pid_t		pid;
	int			res;

	if (!curr || *(curr->type) == OPERATOR)
		return (EXIT_FAILURE);
	relative_hook(curr, env);
	if ((res = builtin_handler(curr, env)) != -1)
		return (res);
	if ((pid = fork()) == -1)
		return (EXIT_FAILURE);
	if (!pid)
		child_offload(curr, env);
	if (wait)
	{
		waitpid(pid, &res, WUNTRACED);
		if (WIFSTOPPED(res))
		{
			if (handle_suspend(&pid, curr) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else
			kill(pid, SIGKILL);
	}
	return (res);
}

/*
** Introduce error handling.
*/

void		pipe_carry(t_ast *prev, t_ast *curr)
{
	int fds[2];

	if (!curr || (!curr->p_info && !(curr->p_info = init_process())))
		return ;
	*(curr->p_info->stdin) = (prev ? *(curr->p_info->stdin) : STDIN_FILENO);
	curr->p_info->stdin[1] = (prev ? curr->p_info->stdin[1] : -1);
	if (pipe_ops(fds))
		return ;
	memcpy(curr->p_info->comm, fds, sizeof(int) * 2);
	if (pipe_ops(fds))
		return ;
	if (!(curr->right_child->right_child) ||
			(*(curr->right_child->type) == OPERATOR &&
			ft_strcmp(*(curr->right_child->token), "|")))
	{
		fds[0] = STDOUT_FILENO;
		fds[1] = STDOUT_FILENO;
	}
	memcpy(curr->p_info->stdout, fds, sizeof(int) * 2);
	*(curr->p_info->stderr) = STDERR_FILENO;
	if (curr->left_child && curr->right_child)
	{
		build_leafs(curr);
		build_info(curr, curr->right_child);
	}
}
