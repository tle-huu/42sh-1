/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reprint_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 10:47:14 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/05 19:24:10 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_term.h"

int			reprint_buffer(void)
{
	ft_putstr_fd(g_shell_env.buffer->buff, STDIN_FILENO);
	move_cursor(&g_shell_env.cursor);
	return (EXIT_SUCCESS);
}
