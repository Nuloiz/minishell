/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modified_libft_func.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:08:15 by nschutz           #+#    #+#             */
/*   Updated: 2023/09/19 11:08:15 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

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

static int	mod_possplit(const char *s, char c)
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

static int	mod_countsplit(char const *s, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[j] != '\0')
	{
		while (s[j] == c)
			j++;
		if (!s[j])
			break ;
		if (s[j] == 34 || s[j] == 39)
			j = j + mod_possplit(&s[j] + 1, s[j]) + 2;
		else
			j = j + mod_possplit(&s[j], c);
		i++;
	}
	return (i);
}

char	**mod_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**array;

	i = 0;
	j = 0;
	array = (char **)malloc(sizeof(char *) * (mod_countsplit(s, c) + 1));
	if (!array)
		return (0);
	while ((s[j] != '\0'))
	{
		while (s[j] == c)
			j++;
		if (!s[j])
			break ;
		if (s[j] == 34 || s[j] == 39)
		{
			array[i] = ft_substr(s, j, mod_possplit(&s[j] + 1, s[j]) + 2);
			if (array[i] == NULL)
				return (mod_allocfails(array));
			j = j + mod_possplit(&s[j] + 1, s[j]) + 2;
		}
		else
		{
			array[i] = ft_substr(s, j, mod_possplit(&s[j], c));
			if (array[i] == NULL)
				return (mod_allocfails(array));
			j = j + mod_possplit(&s[j], c);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}
