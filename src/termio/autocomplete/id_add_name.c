/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_add_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 16:07:32 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/16 02:37:31 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_autocomplete.h"
#include "ft_proto.h"

int		id_add_name(struct stat *sbuf, struct dirent *entry)
{
	size_t	len;
	char	*send;
	t_trie	*trie;

	len = ft_strlen(entry->d_name);
	(g_shell_env.cursor.wordloc == 1) ? (trie = g_shell_env.trie_binaries.trie)
			: (trie = g_shell_env.trie_wdir.trie);
	if (!(send = ft_memalloc(len + 2)))
		return (EXIT_FAILURE);
	ft_strcpy(send, entry->d_name);
	if (S_ISDIR(sbuf->st_mode))
		send[len] = '/';
	add_word_to_trie(trie, send);
	meta_free(send);
	return (EXIT_SUCCESS);
}
