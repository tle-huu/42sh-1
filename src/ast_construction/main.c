/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 15:24:14 by tle-huu-          #+#    #+#             */
/*   Updated: 2018/04/11 15:54:34 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int main(int argc, char **argv) {


	t_token_type *type = malloc(sizeof(t_token_type) * 13);
	type[0] = 0;
	type[1] = 0;
	type[2] = 1;
	type[3] = 0;
	type[4] = 1;
	type[5] = 0;
	type[6] = 1;
	type[7] = 0;
	type[8] = 0;
	type[9] = 0;
	type[10] = 0;
	type[11] = 0;
	type[12] = 0;

	int i = 0;
	t_queue *forest = build_forest(argv + 1, (t_token_type *)type);
	if (!forest)
	{
		printf("poop\n");
		return (EXIT_FAILURE);
	}
	// run_forest(forest);
	t_list *vasy = forest->head;
	while (vasy)
	{

		printf("\nnew tree\n\n");
		print_ast((t_ast *)(vasy->content), 0);
		vasy = vasy->next;
	}
	while(1);
	return 0;
}
