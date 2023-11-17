/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:01:22 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/13 11:01:22 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *string_vor_quote(char *s, int l_r, char **envp)
{
	char	*tmp;

	if (is_env_var(s))
	{
		tmp = env_var(s, envp, l_r);
		return (free(s), tmp);
	}
	else
		return (s);
}

static char *get_env_in_quotes(char *s, int *i, t_quote info)
{
	char	*tmp;
	char	*str;
	int		j;

	j = *i;
	while (s[*i] && s[*i] != info.c)
		(*i)++;
	str = ft_substr(s, j, *i - j);
	if (!str)
		return (NULL);
	tmp = env_var(str, info.envp, info.l_r);
	return (free(str), tmp);
}

static char *more_env(char *s, int *i, int *j, t_quote info)
{
	char	*s1;
	char	*s2;

	if (*i == *j)
	{
		s1 = get_env_in_quotes(s, i, info);
		*j = *j + (int)ft_strlen(s1) - 2;
		return (s1);
	}
	s1 = ft_substr(s, *j, (*i) - (*j));
	if (!s1)
		return (NULL);
	s2 = get_env_in_quotes(s, i, info);
	if (!s2)
		return (NULL);
	s2 = modified_strjoin(s1, s2);
	*j = *j + (int)ft_strlen(s2) - 2;
	return (s2);
}

static char	*get_quote(char *s, t_quote info, int *i)
{
	char	*tmp;
	char	*str;
	int 	j;

	info.c = s[*i];
	(*i)++;
	j = *i;
	str = NULL;
	while (s[*i] && s[*i] != info.c)
	{
		if (s[*i] == '$' && s[(*i) + 1] != info.c && info.c == 34)
		{
			tmp = more_env(s, i, &j, info);
			if (!tmp)
				return (NULL);
			if (str)
			{
				str = ft_strjoin(str, tmp);
				if (!str)
					return (NULL);
				free(tmp);
			}
			else
				str = tmp;
		}
		else
			(*i)++;
	}
	tmp = ft_substr(s, j, *i - j);
	if (!tmp && *i != j)
		return (NULL);
	str = mod_nocheck_strjoin(str, tmp);
	if (s[(*i)] != info.c)
		return (NULL);
	(*i)++;
	return (str);
}

static char	*no_quotes(char *s, int l_r, char **envp)
{
	char	*tmp;

	if (is_env_var(s))
	{
		tmp = env_var(ft_strdup(s), envp, l_r);
	}
	else
		tmp = ft_strdup(s);
	return (tmp);
}

char	*new_quotes(char *s, int l_r, char **envp)
{
	t_quote info;
	char	*tmp;
	char	*quote;
	int		i;
	int		j;

	info.l_r = l_r;
	info.envp = envp;
	i = 0;
	j = 0;
	while (s[i] && s[i] != 34 && s[i] != 39)
		i++;
	if (!s[i])
		return (no_quotes(s, l_r, envp));
	if (i > 0)
	{
		tmp = string_vor_quote(ft_substr(s, 0, i), l_r, envp);
		j = 1;
	}
	if ((s)[i] == 34 || (s)[i] == 39)
		quote = get_quote((s), info, &i);
	if ((s)[i] && (s)[i] != '\0')
		quote = modified_strjoin(quote, new_quotes(&((s)[i]), l_r, envp));
	if (j == 1)
		quote = modified_strjoin(tmp, quote);
	return (quote);
}
