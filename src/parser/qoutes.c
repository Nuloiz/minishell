/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:48:32 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/03 14:48:32 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*end_of_quote(char *ret, int *i, int *j, char c)
{
	char	*tmp;

	if (ret[*i] == c)
	{
		tmp = modified_strjoin(ft_substr(ret, 0, *i), \
			ft_substr(ret, (*i) + 1, ft_strlen(ret) - *i));
		free(ret);
		if (!tmp)
			return (NULL);
		ret = tmp;
		*i = *i - 2;
		*j = *j + 1;
	}
	*i = *i + 1;
	return (ret);
}

static char	*quotes(char *s, char c)
{
	char	*ret;
	int		i;
	int		j;

	ret = ft_substr(s, 1, ft_strlen(s) - 2);
	if (!ret)
		return (NULL);
	i = 0;
	j = 0;
	while (ret[i] != '\0')
	{
		ret = end_of_quote(ret, &i, &j, c);
		if (!ret)
			return (NULL);
	}
	if (j % 2 != 0)
	{
		ft_putstr_fd("Open Quotes", 0);
		free(ret);
		return (NULL);
	}
	return (ret);
}

t_input	*found_quote(t_input *new, char **s, char c)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*s)[i] && (*s)[i] != c)
		i++;
	tmp = ft_substr(*s, 0, i);
	if (!tmp && i > 0)
		return (NULL);
	new->word = quotes(&(*s)[i], (*s)[i]);
	if (!new->word)
		return (NULL);
	new->word = mod_nocheck_strjoin(tmp, new->word);
	if (!new->word)
		return (NULL);
	if (is_env_var(*s))
		new->type = 4;
	free(*s);
	*s = new->word;
	return (new);
}