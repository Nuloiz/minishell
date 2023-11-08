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

static char	*string_before_env(char *s, int *i, t_boollr *j)
{
	char	*dup;

	while (s[*i] != '$')
		*i = *i + 1;
	dup = ft_calloc(*i + 1, 1);
	if (!dup)
		return (NULL);
	while (j->bool < *i)
	{
		dup[j->bool] = s[j->bool];
		j->bool = j->bool + 1;
	}
	if (j->bool > 0 && dup[j->bool - 1] == 39)
		j->bool = 1;
	else
		j->bool = 0;
	return (dup);
}

static char	*found_env(char *s, int i, t_boollr *j, char **envp)
{
	char	*tmp;
	int		k;

	k = i;
	if (s[k] == '$' && j->bool == 0)
		k = 0;
	else
	{
		while (s[k] && s[k] != 39)
			k++;
	}
	tmp = mod_get_env(envp, &s[i + 1], j, &s[k]);
	free(s);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*env_var(char *s, char **envp, int l_r)
{
	int			i;
	t_boollr	j;
	char		*dup;
	char		*tmp;

	i = 0;
	j.l_r = l_r;
	j.bool = 0;
	if (s[0] != '$')
	{
		dup = string_before_env(s, &i, &j);
		if (!dup)
			return (NULL);
	}
	else
		dup = NULL;
	tmp = found_env(s, i, &j, envp);
	if (!tmp)
	{
		if (dup)
			free(dup);
		return (NULL);
	}
	dup = mod_nocheck_strjoin(dup, tmp);
	return (dup);
}
