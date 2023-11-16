/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:52:30 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/23 15:52:30 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*string_before_env(char *s, int *i)
{
	int 	j;
	char	*dup;

	j = 0;
	while (s[*i] != '$')
		*i = *i + 1;
	dup = ft_calloc(*i + 1, 1);
	if (!dup)
		return (NULL);
	while (j < *i)
	{
		dup[j] = s[j];
		j++;
	}
	return (dup);
}

static char	*str_after_env(char *s, int *i, int l_r, char **envp)
{
	char	*tmp;

	tmp = ft_substr(s, *i, ft_strlen(s) - *i);
	if (!tmp)
		return (NULL);
	if (is_env_var(tmp))
		tmp = env_var(tmp, envp, l_r);
	return (tmp);
}

static char	*found_env(char *s, int *i, int l_r, char **envp)
{
	char	*tmp;
	char 	*str;
	int		k;
	int		j;

	tmp = NULL;
	k = *i;
	j = 0;
	while (s[k] != '\0')
	{
		if (s[k] == '$' || s[k] == 39)
		{
			tmp = mod_get_env(envp, ft_substr(s, *i, k - *i), l_r);
			if (s[k] == '$')
			{
				k++;
				str = found_env(s, &k, l_r, envp);
			}
			else
				str = str_after_env(s, &k, l_r, envp);
			tmp = modified_strjoin(tmp, str);
			j = 1;
			break;
		}
		k++;
	}
	if (j == 0)
		tmp = mod_get_env(envp, &s[*i], l_r);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*env_var(char *s, char **envp, int l_r)
{
	int			i;
	char		*dup;
	char		*tmp;

	i = 0;
	if (s[0] != '$')
	{
		dup = string_before_env(s, &i);
		if (!dup)
			return (NULL);
	}
	else
		dup = NULL;
	i++;
	tmp = found_env(s, &i, l_r, envp);
	if (!tmp)
	{
		if (dup)
			free(dup);
		return (NULL);
	}
	dup = mod_nocheck_strjoin(dup, tmp);
	return (dup);
}
