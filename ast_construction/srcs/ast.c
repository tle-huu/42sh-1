/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:39:45 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/03/22 16:33:37 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

#define END_PARSING -1

static int			is_operator(char *token_char)
{
	return (str_search({"|", "&", "||", "&&", ";", NULL}, token_char));
}

static int			parse_tokens(char **tokens, t_token_type *type,
	t_list **forest)
{
	int		i;

	i = 0;
	while (tokens[i])
	{
		if (type[i] == operator && is_operator(tokens[i]))
			return (i);
		i++;
	}
	return (END_PARSING);
}

static t_ast		*build_ast(char **tokens, t_token_type *type, int *position)
{
	int					i;
	t_ast				*ast;
	char				**sub_token_char;
	t_token_type		*sub_token_type;

	ast = NULL;
	if ((i = parse_tokens(tokens, type)) == END_PARSING)
		return (ast);
	*position += i;
	sub_token_char = sub_token_char(tokens, 0, i + 1);
	sub_token_type = sub_token_type(type, 0, i + 1);
	if (ft_strequ(tokens[i], ";") || !tokens[i])
		return (new_ast_leaf(sub_token_char, sub_token_type));
	ast = new_ast_node(sub_token_char(sub_token_char, i, 1),
							sub_token_type(sub_token_type, i, 1),
								new_ast_leaf(sub_token_char, sub_token_type),
									build_ast(tokens + i + 1, type + i + 1));
	return (ast);
}

t_list				*build_forest(char **tokens, t_token_type *type)
{
	t_list		*forest;
	t_list		*new_list;
	t_ast		*ast;
	int			position;

	if (!(forest = (t_list *)ft_memalloc(sizeof(t_list))))
		return (NULL);
	position = 0;
	while ((ast = build_ast(tokens + position, type, &position)))
	{
		new_list = ft_lstnew(ast, sizeof(*ast));
		ft_lstadd(&forest, ast);
		free(ast);
	}
	return (forest);
}
