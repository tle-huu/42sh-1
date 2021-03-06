/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satkins <satkins@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/02 19:33:34 by asyed             #+#    #+#             */
/*   Updated: 2018/04/20 10:30:28 by satkins          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <stdlib.h>
#include <stdio.h>

extern char **environ;

int	builtin_export(char *argv[], __attribute__((unused)) t_environ *env)
{
	if (builtin_setenv(argv, g_environ) == EXIT_FAILURE 
		|| builtin_setenv(argv, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	builtin_getenv(char *argv[], t_environ *env)
{
	int	i;

	i = 0;
	if (!argv[1])
		return (EXIT_FAILURE);
	while ((env->environ)[i])
	{
		if (!ft_strncmp(argv[1], env->environ[i], 
			(ft_strchr(env->environ[i], '=') - env->environ[i])))
		{
			ft_printf_fd(STDOUT_FILENO, "%s\n", env->environ[i]);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}


int	builtin_env(__attribute__((unused)) char *argv[], t_environ *env)
{
	int	i;

	i = 0;
	while ((env->environ)[i])
	{
		ft_printf_fd(STDOUT_FILENO, "%s\n", env->environ[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	builtin_setenv(char *argv[], t_environ *env)
{
	int	i;
	int	equal_index;

	if (!argv[1])
		return (builtin_env(argv, env));
	if (!(equal_index = ft_strchr(argv[1], '=') - argv[1]))
		return (EXIT_FAILURE);
	i = 0;
	while (env->environ[i])
	{
		if (!strncmp(argv[1], env->environ[i], 
			equal_index) &&
			ft_strchr(env->environ[i], '=') - env->environ[i] == equal_index)
		{
			meta_free(env->environ[i]);
			if (!(env->environ[i] = ft_strdup(argv[1])))
				return (EXIT_FAILURE);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	env->size++;
	if (!(env->environ = meta_realloc(env->environ, (env->size + 1) * sizeof(char *))))
		return (EXIT_FAILURE);
	environ = env->environ;
	env->environ[env->size - 1] = ft_strdup(argv[1]);
	env->environ[env->size] = NULL;
	return (EXIT_SUCCESS);
}

int	builtin_unsetenv(char *argv[], t_environ *env)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(argv[1]);
	while (env->environ[i])
	{
		if (!strncmp(argv[1], env->environ[i], (ft_strchr(env->environ[i], '=') - env->environ[i])))
		{
			meta_free(env->environ[i]);
			ft_memmove(&(env->environ[i]), &(env->environ[i + 1]), ((env->size - i) - 1) * sizeof(char *));
			env->size--;
			env->environ = meta_realloc(env->environ, ((env->size + 1) * sizeof(char *)));
			environ = env->environ;
			env->environ[env->size] = NULL;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
