/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Updated: 2018/03/29 15:43:13 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_term.h"

static int		multibyte(t_terminf *shell_env, char byte, int *mpass)
{
	if (*mpass == 0
		|| (*mpass == 1 && byte == '['))
	{
		(*mpass)++;
		return (EXIT_SUCCESS);
	}
	else if (*mpass == 1 && byte != '[')
	{
		one_byte(shell_env, byte);
		return (EXIT_SUCCESS);
	}
	// jump table
}

static int		regular_text(char byte)
{
	t_cursor	*cursor;
	char		*buffer;
	int			ret;

	ret = EXIT_SUCCESS;
	cursor = &(g_shell_env.cursor);
	buffer = g_shell_env->buffer->buff;
	if (g_shell_env->buffer->length == g_shell_env->buffer->max_size)
		ret = resize_buffer(void);
	ft_memove(buffer[cursor->position + 1], buffer[cursor->position],
			g_shell_env->buffer->length - cursor->position);
	tputs(tgetstr("im", 0), 1, &my_putchar);
	ft_putchar_fd(byte, 0);
	tputs(tgetstr("ei", 0), 1, &my_putchar);
	return (ret);
}

static int		control_char(t_terminf *shell_env, char byte)
{
	// jump table
}


static int		one_byte(t_terminf *shell_env, char byte)
{
	int		ret;

	ret = EXIT_SUCCESS;
	if (byte >= 32 && byte <= 126)
		ret = one_byte(shell_env, byte);
	if (byte < 32 || byte == 127)
		ret = control_char(shell_env, byte);
	return (ret);
}

int				handle_keys(t_terminf *shell_env, char byte, int *mpass)
{
	int		ret;
	int		token;

	ret = EXIT_SUCCESS;
	token = 0;
	if (byte == 27)
		ret = multibyte(shell_env, byte, mpass);
	else
		ret = one_byte(shell_env, byte);
	return (ret);
}
