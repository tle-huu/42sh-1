/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/29 14:25:41 by nkouris           #+#    #+#             */
/*   Updated: 2018/03/29 17:32:13 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_term.h"

static void ft_idonothing(int lol)
{}


int		shsignal_handlers(void)
{
	signal(SIGINT, ft_idonothing);
	signal(SIGTSTP, ft_idonothing);
	signal(SIGCONT, ft_idonothing);
	signal(SIGWINCH, ft_idonothing);
	return (EXIT_SUCCESS);
}