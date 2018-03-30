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

static int		(*multibyte_jump[])(char byte) = {

	ft_linemove
	/*
	ft_delete,
	ft_scroll,
	ft_history,
	ft_shiftmod
	*/
};

static int		(*control_jump[])(char byte) = {
	control_c
/*
	cntrl_d,
	cntrl_g,
	cntrl_h,
	cntrl_j,
	cntrl_m,
	cntrl_o,
	cntrl_v,
	cntrl_w
*/
};

static int		control_char(char byte)
{
	int	ret;
	if ((ret = cntrl_read(byte)) < 0)
		return (EXIT_FAILURE);
	else
		ret = control_jump[ret](byte);
  return (ret == EXIT_SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE);

}

static int		regular_text(char byte)
{
	t_cursor	*cursor;
	char		*buffer;
	int			ret;

	ret = EXIT_SUCCESS;
	buffer = g_shell_env.buffer->buff;
	cursor = &(g_shell_env.cursor);
	if (g_shell_env.buffer->length == g_shell_env.buffer->max_size)
		ret = resize_buffer();
	ft_memmove(buffer + cursor->position + 1, buffer + cursor->position,
			g_shell_env.buffer->max_size - cursor->position - 1);
	buffer[cursor->position] = byte;
	cursor->position++;
	g_shell_env.buffer->length++;
	tputs(tgetstr("im", 0), 1, &my_putchar);
	ft_putchar_fd(byte, 0);
	tputs(tgetstr("ei", 0), 1, &my_putchar);
	return (ret);
}

static int		one_byte(char byte)
{
	int		ret;

	ret = EXIT_SUCCESS;
	if (byte >= 32 && byte <= 126)
		ret = regular_text(byte);
	if (byte < 32 || byte == 127)
		ret = control_char(byte);
	return (ret);
}

static int		multibyte(char byte, int *mpass)
{
	int	ret;

	if (*mpass == 0
		|| (*mpass == 1 && byte == '['))
	{
		(*mpass)++;
		return (EXIT_SUCCESS);
	}
	else if (*mpass == 1 && byte != '[')
	{
		one_byte(byte);
		*mpass = 0;
		return (EXIT_SUCCESS);
	}
	if ((ret = multibyte_read(byte)) != EXIT_FAILURE)
	{
		if (ret == CURSOR_MOVE)
			multibyte_jump[ret](byte);
	}
	else
		return (EXIT_FAILURE);
	*mpass = 0;
	return (EXIT_SUCCESS);
	// jump table
}

int				handle_keys(char byte, int *mpass)
{
	int		ret;
	int		token;

	ret = EXIT_SUCCESS;
	token = 0;
	if (byte == 27 || *mpass)
		ret = multibyte(byte, mpass);
	else
		ret = one_byte(byte);
	return (ret);
}
