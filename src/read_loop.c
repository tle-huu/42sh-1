/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 21:33:27 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/04/03 17:11:33 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_term.h"

static int		checktty(void)
{
	return (EXIT_SUCCESS);
}

static int		reset_terminal(void)
{
	return (EXIT_SUCCESS);
}

int				read_loop(void)
{
	char	byte;

	g_shell_env.tokens.mpass = 0;
	g_shell_env.tokens.bslash = 0;
	new_prompt(0);
	while (read(STDIN_FILENO, &byte, 1) == 1)
	{
		if (byte == 10 && !g_shell_env.tokens.bslash)
		{
			if (ft_carriage_return() == EXIT_FAILURE)
				new_prompt(0);
		}
		else if (byte == 10 && g_shell_env.tokens.bslash)
			backslash_char();
		else if (byte == 4)
		{
			reset_prompt();
			break ;
		}
		else if (handle_keys(byte) == EXIT_FAILURE
				|| checktty() == EXIT_FAILURE)
			reset_terminal();
	}
	return (EXIT_SUCCESS);
}