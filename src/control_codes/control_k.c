/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_k.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:02:09 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/05 14:02:37 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_term.h"

int		control_k(void)
{
	cut_line_after_cursor();
	return (EXIT_SUCCESS);
}
