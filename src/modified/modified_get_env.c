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

static char	*mod_valid_env(char *envp, char *string, t_boollr *j, char *s)
{
	char	*env;

	env = ft_strdup(envp);
	ft_memmove(env, &env[ft_strlen(string) + 1], \
					(ft_strlen(env) - ft_strlen(string)));
	if (j->bool == 1)
		env = mod_nofree_strjoin(env, s);
	free(string);
	return (env);
}

static char	*mod_get_env_two(char **envp, char *string, t_boollr *j, char *s)
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
			return (free(string_equal), mod_valid_env(envp[i], string, j, s));
	}
	if (!ft_strncmp(string, "?", 2))
	{
		env = ft_itoa(j->l_r);
		if (j->bool == 1)
			env = mod_nofree_strjoin(env, s);
		free(string_equal);
		return (env);
	}
	if (j->bool == 1)
		env = ft_strdup(s);
	return (free(string_equal), free(string), env);
}

static char	*mod_multiple_wo_quotes(char **envp, char *string, \
									t_boollr *j, char **s)
{
	int		i;

	i = 0;
	while (string[i] != '\0')
	{
		if (string[i] == '$' || (string[i] == 39 && string[i + 1] == '$'))
		{
			if (string[i] == '$')
				*s = mod_strjoin(mod_get_env(envp, ft_substr(string, \
				i + 1, ft_strlen(string) - i), j, NULL), NULL);
			else
				*s = mod_strjoin(mod_get_env(envp, ft_substr(string, \
				i + 2, ft_strlen(string) - i - 3), j, NULL), NULL);
			if (!*s)
				return (free(string), NULL);
			j->bool = 1;
			break ;
		}
		i++;
	}
	return (ft_substr(string, 0, i));
}

char	*mod_get_env(char **envp, char *string, t_boollr *j, char *s)
{
	string = mod_multiple_wo_quotes(envp, string, j, &s);
	if (!string)
		return (NULL);
	return (mod_get_env_two(envp, string, j, s));
}
