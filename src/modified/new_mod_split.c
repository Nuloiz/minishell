/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_mod_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:30:19 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/15 13:30:19 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_allocfails(char **array)
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

static int	mod_possplit(char *s, int *j, char c)
{
	char	q;

	while (s[*j] != '\0' && s[*j] != c)
	{
		if (s[*j] == 34 || s[*j] == 39)
		{
			q = s[*j];
			(*j)++;
			while (s[*j] != '\0' && s[*j] != q)
				(*j)++;
			if (s[*j] == '\0')
				return (0);
			(*j)++;
		}
		else
			(*j)++;
	}
	return (1);
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
		k = mod_possplit(s, &j, c);
		if (k == 0)
			return (-1);
		i++;
	}
	return (i);
}

static char	*mod_splitting(char *s, int *j, char c)
{
	char	*array;
	char	q;
	int		start;

	start = *j;
	while (s[*j] != '\0' && s[*j] != c)
	{
		if (s[*j] == 34 || s[*j] == 39)
		{
			q = s[*j];
			(*j)++;
			while (s[*j] != q)
				(*j)++;
			(*j)++;
		}
		else
			(*j)++;
	}
	array = ft_substr(s, start, *j - start);
	return (array);
}

char	**mod_split(char *s, char c)
{
	int		i;
	int		j;
	char	**array;

	i = 0;
	j = mod_countsplit(s, c);
	if (j == -1)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (j + 1));
	j = 0;
	if (!array)
		return (0);
	while ((s[j] != '\0'))
	{
		while (s[j] == c)
			j++;
		if (!s[j])
			break ;
		array[i] = mod_splitting(s, &j, c);
		if (array[i] == NULL)
			return (ft_allocfails(array));
		i++;
	}
	array[i] = NULL;
	return (array);
}
