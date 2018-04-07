/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 21:33:27 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/04/06 16:34:10 by nkouris          ###   ########.fr       */
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

int				ft_read_loop(void)
{
	char	byte;

	new_prompt(0);
	init_tokens();
	while (read(STDIN_FILENO, &byte, 1) == 1)
	{
/*	ft_printf("byte : <%d>\n", byte); */
		if (byte == 4 && !(*g_shell_env.buffer->buff))
		{
			reset_prompt();
			break ;
		}
/*		else if (byte == 10)
			ft_carriage_dispatch(byte); */
		else if (byte == 10 && T_BSLASH)
			backslash_char();
		else if (byte == 10 && (T_QUOTE | T_DQUOTE))
			quote_mode(byte);
		else if (byte == 10)
		{
			if (ft_linefeed() == EXIT_FAILURE
				|| checktty() == EXIT_FAILURE)
				reset_terminal();
		}
		else if (handle_keys(byte) == EXIT_FAILURE)
			reset_terminal();
	}
	return (EXIT_SUCCESS);
}
