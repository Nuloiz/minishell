/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modified_split_func.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:08:15 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/30 16:50:00 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**mod_allocfails(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free (array[i]);
		i++;
	}
	free (array);
	return (NULL);
}

int	mod_possplit(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		else
			i++;
	}
	return (i);
}

static int	mod_countsplit(char *s, char c)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s[j] != '\0')
	{
		while (s[j] == c)
			j++;
		if (!s[j])
			break ;
		k = qoute_or_space(s, c, j);
		mod_countsplitting((char *)s, &j, c, &k);
		if (k == -1)
			return (-2);
		i++;
	}
	return (i);
}

char	*mod_splitting(char *s, int *j, char c, int bool)
{
	char	*array;
	char	*tmp;
	int		i;

	if (bool == 1)
	{
		if (s[*j] != 34 && s[*j] != 39)
			tmp = string_before_quote(s, j, &bool);
		i = mod_possplit(&s[*j] + 1, s[*j]) + 2;
		array = ft_substr(s, *j, i);
		*j = *j + i;
		if (s[*j] && s[*j] != ' ')
			array = modified_strjoin(array, \
				mod_splitting(s, j, c, qoute_or_space(s, c, *j)));
		if (bool == 0)
			array = modified_strjoin(tmp, array);
	}
	else
	{
		array = ft_substr(s, *j, mod_possplit(&s[*j], c));
		*j = *j + mod_possplit(&s[*j], c);
	}
	return (array);
}

char	**mod_split(char *s, char c)
{
	int		i;
	int		j;
	char	**array;

	i = 0;
	j = mod_countsplit(s, c) + 1;
	if (j == -1)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * j);
	j = 0;
	if (!array)
		return (NULL);
	while ((s[j] && s[j] != '\0'))
	{
		while (s[j] == c)
			j++;
		if (!s[j])
			break ;
		array[i] = mod_splitting(s, &j, c, qoute_or_space(s, c, j));
		if (array[i] == NULL)
			return (mod_allocfails(array));
		i++;
	}
	array[i] = NULL;
	return (array);
}
