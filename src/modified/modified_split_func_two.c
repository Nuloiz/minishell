/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modified_split_func_two.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:10:55 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/23 12:12:22 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	qoute_or_space(char *s, char c, int j)
{
	while (s[j] && s[j] != c)
	{
		if (s[j] == 39 || s[j] == 34)
			return (1);
		j++;
	}
	return (0);
}

char	*string_before_quote(char *s, int *j, int *bool)
{
	int		i;
	int		k;
	char	*tmp;

	i = 0;
	k = *j;
	while (s[*j] != 34 && s[*j] != 39)
	{
		i++;
		(*j)++;
	}
	tmp = ft_substr(s, k, i);
	*bool = 0;
	return (tmp);
}

void	mod_countsplitting(char *s, int *j, char c, int *bool)
{
	int	k;

	if ((*bool) == 1)
	{
		while (s[*j] != 34 && s[*j] != 39)
			(*j)++;
		if (!s[(*j) + 1])
		{
			*bool = -1;
			return ;
		}
		*j = *j + mod_possplit(&s[*j] + 1, s[*j]) + 2;
		if (!s[(*j) - 1])
		{
			*bool = -1;
			return ;
		}
		if (s[*j] != ' ')
		{
			k = qoute_or_space(s, c, *j);
			mod_countsplitting(s, j, c, &k);
		}
	}
	else
		*j = *j + mod_possplit(&s[*j], c);
}
