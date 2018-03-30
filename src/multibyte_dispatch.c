/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multibyte_dispatch.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 16:26:22 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/29 17:47:50 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_term.h"


int		multibyte_read(char byte)
{
	if (LSEEK(byte))
		return (MOVE);
	else if (DEL(byte))
		return (DEL);
	else if (SCRL(byte))
		return (SCRL);
	else if (HIST(byte))
		return (HIST);
	else if (byte == 1)
		return (SHIFT);
	return (EXIT_FAILURE);
}

int		cntrl_read(char byte)
{
	if (byte == 3)
		return (C_C);
	else if (byte == 4)
		return (C_D);
	else if (byte == 7)
		return (C_G);
	else if (byte == 8)
		return (C_H);
	else if (byte == 10)
		return (C_J);
	else if (byte == 13)
		return (C_M);
	else if (byte == 15)
		return (C_O);
	else if (byte == 22)
		return (C_V);
	else if (byte == 23)
		return (C_W);
	return (-1);
}
