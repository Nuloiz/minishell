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

static int	mod_check_id(char string, int *alpha)
{
	if (ft_isalpha(string))
		*alpha = 1;
	if (!ft_isalpha(string) && string != '_' && *alpha != 1)
		return (0);
	if (!ft_isalnum(string) && string != '_')
		return (0);
	return (1);
}

static char	*checked_id(char *s, int *i, int *k, t_quote info)
{
	char	*str;
	char	*tmp;

	tmp = mod_get_env(info.envp, ft_substr(s, *i, *k - *i), info.l_r);
	if (s[*k] == '?' && k > 0 && s[*k - 1] == '$')
	{
		str = mod_get_env(info.envp, ft_substr(s, *k, 1), info.l_r);
		(*k)++;
		if (s[*k] != '\0')
			str = modified_strjoin(str, found_env(s, k, info));
	}
	else if (s[*k] == '$' && s[*k + 1] != '\0')
	{
		(*k)++;
		str = found_env(s, k, info);
	}
	else
		str = str_after_env(s, k, info.l_r, info.envp);
	tmp = modified_strjoin(tmp, str);
	return (tmp);
}

char	*found_env(char *s, int *i, t_quote info)
{
	char	*tmp;
	int		k;
	int		j;
	int		alpha;

	tmp = NULL;
	k = *i;
	j = 0;
	alpha = 0;
	while (s[k] != '\0')
	{
		if (mod_check_id(s[k], &alpha) == 0)
		{
			tmp = checked_id(s, i, &k, info);
			j = 1;
			break ;
		}
		k++;
	}
	if (j == 0)
		tmp = mod_get_env(info.envp, ft_strdup(&s[*i]), info.l_r);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*env_var(char *s, char **envp, int l_r)
{
	int			i;
	t_quote		info;
	char		*dup;
	char		*tmp;

	i = 0;
	info.l_r = l_r;
	info.envp = envp;
	if (s[0] != '$')
	{
		dup = string_before_env(s, &i);
		if (!dup)
			return (NULL);
	}
	else
		dup = NULL;
	i++;
	tmp = found_env(s, &i, info);
	if (!tmp)
	{
		if (dup)
			free(dup);
		return (NULL);
	}
	return (mod_nocheck_strjoin(dup, tmp));
}
