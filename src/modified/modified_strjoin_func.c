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

char	*string_one(char *s1, char *joined)
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
