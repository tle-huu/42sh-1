/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:39:45 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/04/14 11:55:19 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

#define END_PARSING -1

char	*g_operators[] = {
	"|",
	"&",
	"||",
	"&&",
	";",
	NULL
};

/*
** Remove the check for g_operators.
*/

static int			parse_tokens(char **tokens, t_token_type *type)
{
	int		i;

	i = 0;
	while (tokens[i])
	{
		if (type[i] == OPERATOR && str_search(g_operators, tokens[i]))
			return (i);
		ft_printf("not : |%s|[%d]\n", tokens[i], type[i]);
		i++;
	}
	return (!i ? END_PARSING : i - 1);
}

static t_ast		*build_ast(char **tokens, t_token_type *type, int *position)
{
	t_ast				*ast;
	char				**sub_string;
	t_token_type		*sub_types;
	int					i;

	ast = NULL;
	i = 0;
	if ((i = parse_tokens(tokens, type)) == END_PARSING)
		return (ast);
	*position += i + 1;
	sub_string = sub_token_char(tokens, 0, i + 1);
	sub_types = sub_token_type(type, 0, i + 1);
	if (ft_strequ(tokens[i], ";") || !tokens[i + 1])
	{
		ft_strequ(tokens[i], ";") ? sub_string[i] = NULL : 0;
		return (new_ast_leaf(sub_string, sub_types));
	}
	ast = new_ast_node(sub_token_char(sub_string, i, 1),
			sub_token_type(sub_types, i, 1),
			new_ast_leaf(sub_token_char(sub_string, 0, i),
							sub_token_type(sub_types, 0, i)),
			build_ast(tokens + i + 1, type + i + 1, position));
	free(sub_string);
	free(sub_types);
	return (ast);
}

t_queue				*build_forest(char **tokens, t_token_type *type)
{
	t_queue		*forest;
	// t_list		*new_list;
	t_ast		*ast;
	int			pos;

	if (!(forest = new_queue()))
		return (NULL);
	pos = 0;
	while (tokens && type && (ast = build_ast(tokens + pos, type + pos, &pos)))
	{
		if (ft_enqueue(forest, ast, sizeof(t_ast)) == EXIT_FAILURE)
		{
			free_forest(forest);
			return (NULL);
		}
		free(ast);
	}
	return (forest);
}
