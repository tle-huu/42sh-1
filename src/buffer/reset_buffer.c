/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 10:45:25 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/06 17:23:37 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_term.h"

int			reset_buffer(void)
{
	int	ret;

	free(g_shell_env.buffer->buff);
	g_shell_env.buffer->buff = 0;
	free(g_shell_env.buffer);
	g_shell_env.buffer = 0;
	ret = init_buffer();
	return (ret);
}
