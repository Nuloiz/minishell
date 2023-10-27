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

static char	*string_before_env(char *s, int *i, int *j)
{
	char	*dup;

	while (s[*i] != '$')
		*i = *i + 1;
	dup = ft_calloc(*i + 1, 1);
	if (!dup)
		return (NULL);
	while (*j < *i)
	{
		dup[*j] = s[*j];
		*j = *j + 1;
	}
	if (*j > 0 && dup[*j - 1] == 39)
		*j = 1;
	else
		*j = 0;
	return (dup);
}

char	*env_var(char *s, char **envp, int *l_r)
{
	int		i;
	int		j;
	int		k;
	char	*dup;
	char	*tmp;

	i = 0;
	j = 0;
	if (s[0] != '$')
	{
		dup = string_before_env(s, &i, &j);
		if (!dup)
			return (NULL);
	}
	else
		dup = NULL;
	if (!ft_strncmp(&s[i], "$?", 3))
	{
		tmp = ft_itoa(*l_r);
		if (!tmp)
		{
			if (dup)
				free(dup);
			return (NULL);
		}
		dup = mod_nocheck_strjoin(dup, tmp);
		if (!dup)
			return (NULL);
	}
	else
	{
		k = i;
		while (s[k] && s[k] != 39)
			k++;
		tmp = mod_get_env(envp, &s[i + 1], j, &s[k]);
		if (!tmp)
		{
			if (dup)
				free(dup);
			return (NULL);
		}
		dup = modified_strjoin(dup, tmp);
	}
	if (!dup)
		return (NULL);
	free(s);
	return (dup);
}
