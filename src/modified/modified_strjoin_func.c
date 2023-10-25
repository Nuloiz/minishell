/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modified_strjoin_func.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:06:02 by nschutz           #+#    #+#             */
/*   Updated: 2023/09/27 14:54:03 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*string_one(char *s1, char *joined)
{
	int	i;

	i = 0;
	while (s1 && s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	if (i > 0)
		joined[i] = ' ';
	return (joined);
}

char	*mod_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	j = 0;
	joined = ft_calloc((ft_strlen(s1) + ft_strlen(s2)) + 2, 1);
	if (joined)
	{
		joined = string_one(s1, joined);
		i = (int)ft_strlen(joined);
		while (s2 && s2[j])
		{
			joined[i] = s2[j];
			i++;
			j++;
		}
		if (s1)
			free((char *)s1);
		if (s2)
			free((char *)s2);
		return (joined);
	}
	else
		return (0);
}

static char	*modified_strjoin_join(char *joined, char *s1, char *s2, int i)
{
	int	j;

	j = 0;
	if (s1)
	{
		while (s1[++i])
			joined[i] = s1[i];
		i = ft_strlen(s1);
	}
	else
		i = 0;
	if (s2)
	{
		while (s2[++j])
		{
			joined[i] = s2[j];
			i++;
		}
	}
	joined[i] = 0;
	return (joined);
}

char	*modified_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;

	i = -1;
	joined = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (joined)
	{
		joined = modified_strjoin_join(joined, s1, s2, i);
		if (s1)
			free(s1);
		if (s2)
			free(s2);
		return (joined);
	}
	else
	{
		if (s1)
			free(s1);
		if (s2)
			free(s2);
	}
	return (0);
}

char	*mod_nofree_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;

	i = -1;
	joined = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (joined)
		return (modified_strjoin_join(joined, s1, s2, i));
	else
		return (0);
}
