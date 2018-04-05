/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 16:27:28 by asyed             #+#    #+#             */
/*   Updated: 2018/04/03 20:48:30 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		op_pipe_exec(t_ast *curr)
{
	run_operation(curr->left_child, 0);
	if (curr->right_child)
	{
		run_operation(curr->right_child, 1);
		run_tree(curr->right_child);
	}
	return (EXIT_SUCCESS);
}
