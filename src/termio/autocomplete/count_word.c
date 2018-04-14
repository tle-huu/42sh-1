/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 20:59:40 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/13 23:16:58 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_autocomplete.h"

void		wcount_forword(char byte)
{
	if (IS_WHITESPACE(byte))
	{
		T_WORD *= !T_WORD;
		if (*(g_shell_env.cursor.buffer + g_shell_env.cursor.position))
			wcount_forword(*(g_shell_env.cursor.buffer +
						g_shell_env.cursor.position));
	}
	else if (!IS_WHITESPACE(byte))
	{
		if (IS_OPERATOR(byte))
			g_shell_env.cursor.wordloc = 0;
		else
		{
			!T_WORD ? g_shell_env.cursor.wordloc++ : 0;
			T_WORD = 1;
		}
	}
	printf("\non: %d\n", g_shell_env.cursor.wordloc);
}

void		wcount_backword(char byte)
{
	if (IS_WHITESPACE(byte))
	{
		if (g_shell_env.cursor.wordloc == -1)
			find_backwords();
		else
			T_WORD ? T_WORD = 0 : 0;
	}
	else if (!IS_WHITESPACE(byte))
	{
		if (IS_OPERATOR(byte))
			g_shell_env.cursor.wordloc = -1;
		else
		{
			!T_WORD ? g_shell_env.cursor.wordloc-- : 0;
			T_WORD = 1;
		}
	}
	printf("\non: %d %d\n", g_shell_env.cursor.wordloc, byte);
}

void		find_backwords(void)
{
	char	*temp;

	T_WORD = 0;
	g_shell_env.cursor.wordloc = 0;
	temp = g_shell_env.cursor.buffer + g_shell_env.cursor.position; 
	while (temp != g_shell_env.buffer->buff && g_shell_env.cursor.wordloc < 2)
		wcount_backword(*temp--);
}
