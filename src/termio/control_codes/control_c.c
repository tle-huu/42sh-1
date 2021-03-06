/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 10:00:39 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/13 22:40:24 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_control.h"
#include "ft_proto.h"

int		control_c(void)
{
	cursor_to_end(&g_shell_env.cursor);
	if (reset_prompt() == EXIT_FAILURE || reset_buffer() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
