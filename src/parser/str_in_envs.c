/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_in_envs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 12:06:33 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/17 12:06:33 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*string_before_env(char *s, int *i)
{
	int		j;
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

char	*str_after_env(char *s, int *i, int l_r, char **envp)
{
	char	*tmp;
	char	*str;

	tmp = ft_substr(s, *i, ft_strlen(s) - *i);
	if (!tmp)
		return (NULL);
	if (is_env_var(tmp))
	{
		str = env_var(tmp, envp, l_r);
		free(tmp);
	}
	else
		str = tmp;
	return (str);
}
