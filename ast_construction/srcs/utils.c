/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:39:53 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/04/04 21:49:09 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_token_type	*sub_token_type(t_token_type *array, int index, int length)
{
	t_token_type	*copy;
	int				i;
	int				j;

	if (!(copy = (t_token_type *)ft_memalloc(sizeof(t_token_type) *
		(length + 1))))
		return (NULL);
	j = 0;
	i = index;
	copy[length] = 0;
	while (j < length)
	{
		copy[j] = array[i];
		i++;
		j++;
	}
	return (copy);
}

char			**sub_token_char(char **array, int index, int length)
{
	char			**copy;
	int				i;
	int				j;

	if (!(copy = (char **)ft_memalloc(sizeof(char *) *
		(length + 1))))
		return (NULL);
	j = 0;
	i = index;
	copy[length] = 0;
	while (j < length)
	{
		copy[j] = array[i];
		i++;
		j++;
	}
	return (copy);
}

int				str_search(char **argv, char *str)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (ft_strequ(argv[i], str))
			return (1);
		i++;
	}
	return (0);
}
