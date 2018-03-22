/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-huu- <tle-huu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 21:04:38 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/03/21 22:06:21 by tle-huu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef enum			e_token_type
{
						token,
						operator

}						t_token_type;

typedef struct				s_ast
{
	char					**token;
	t_token_type			*type;
	struct s_ast			*left_child;
	struct s_ast			*right_child;
}							t_ast;

/*
***		ast utils
*/

t_token_type	*sub_token_type(t_token_type *array, int index, int length);

#endif
