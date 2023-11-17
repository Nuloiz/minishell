/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mod_get_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:07:32 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/16 10:07:32 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*mod_valid_env(char *envp, char *string)
{
	char	*env;

	env = ft_strdup(envp);
	if (!env)
		return (NULL);
	ft_memmove(env, &env[ft_strlen(string) + 1], \
					(ft_strlen(env) - ft_strlen(string)));
	return (free(string), env);
}

char	*mod_get_env(char **envp, char *string, int l_r)
{
	int		i;
	char	*string_equal;
	char	*env;

	i = -1;
	string_equal = ft_strjoin(string, "=");
	env = NULL;
	if (envp == NULL)
		return (NULL);
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], string_equal, ft_strlen(string_equal)))
			return (free(string_equal), mod_valid_env(envp[i], string));
	}
	if (!ft_strncmp(string, "?", 2))
	{
		env = ft_itoa(l_r);
		return (free(string_equal), free(string), env);
	}
	env = ft_strdup("");
	return (free(string_equal), free(string),  env);
}
