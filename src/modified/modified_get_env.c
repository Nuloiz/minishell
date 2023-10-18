/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modified_get_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 09:56:14 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/16 09:56:14 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*mod_get_env(char **envp, char *string, int j, char *s)
{
	int		i;
	char	*string_equal;
	char	*env;

	i = 0;
	env = NULL;
	if (j == 1)
	{
		while (string[i] != 39)
			i++;
		string = ft_substr(string, 0, i);
	}
	i = 0;
	string_equal = ft_strjoin(string, "=");
	if (envp == NULL)
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], string_equal, ft_strlen(string_equal)))
		{
			env = ft_strdup(envp[i]);
			ft_memmove(env, &env[ft_strlen(string) + 1], (ft_strlen(env) - ft_strlen(string)));
			free(string_equal);
			if (j == 1)
				env = ft_strjoin(env, s);
			return (env);
		}
		i++;
	}
	if (j == 1)
		env = ft_strdup(s);
	free(string_equal);
	return (env);
}
