/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkouris <nkouris@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 15:18:45 by nkouris           #+#    #+#             */
/*   Updated: 2018/04/13 20:44:49 by nkouris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_autocomplete.h"
#include "ft_proto.h"

char	*concatpath(char *fin, char *add)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(fin) + ft_strlen(add);
	if (!(temp = (char *)ft_memalloc(len + 1)))
		return (NULL);
	ft_strcpy(temp, add);
	ft_strcat(temp, fin);
	return (temp);
}
