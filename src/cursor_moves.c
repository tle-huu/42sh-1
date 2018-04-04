/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 15:57:48 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/01 20:04:44 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ft_term.h"

void	move_cursor(t_cursor *cursor)
{
	int		og_col;
	int		og_line;
	int		new_col;
	int		new_line;

	og_line = cursor->og_position.y;
	og_col = cursor->og_position.x;
	new_col = og_col + cursor->position;
	new_line = og_line + new_col / (g_shell_env.window.ws_col);
	new_col %= g_shell_env.window.ws_col;
	tputs(tgoto(tgetstr("cm", NULL),
		new_col, new_line), 0, &my_putchar);
}

void		cursor_to_right(t_cursor *cursor)
{
	if (g_shell_env.buffer->length != cursor->position)
	{
		cursor->position++;
		move_cursor(cursor);
	}
}

void		cursor_to_left(t_cursor *cursor)
{
	if (cursor->position > 0)
	{
		cursor->position--;
		move_cursor(cursor);
	}
}

void		cursor_to_home(t_cursor *cursor)
{
	cursor->position = 0;
	move_cursor(cursor);
}

void		cursor_to_end(t_cursor *cursor)
{
	cursor->position = g_shell_env.buffer->length;
	move_cursor(cursor);
}

/*
{

int		ft_backspace(t_terminf *anti)
{
	char	*temp;

	ft_curleft(anti);
	if (!(temp = tgetstr("dc", 0)))
		return (EXIT_FAILURE);
	tputs(temp, 1, my_stupidput);
	return (EXIT_SUCCESS);
}

// int		ft_delete(t_terminf *anti)
// {
// 	char	*temp;
//
// 	temp = tgetstr("dl", 0);
// 	tputs(temp, 1, my_stupidput);
// 	return (EXIT_SUCCESS);
// }
 */