/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:07:55 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/24 15:01:41 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_dup_array(char **new, int i)
{
	int	k;

	k = i;
	while (k < i)
	{
		free(new[k]);
		k++;
	}
	free(new);
}

char	**dup_array(char **array)
{
	char	**new;
	int		i;

	i = 0;
	while (array[i])
		i++;
	new = ft_calloc(sizeof(char *), i + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (array[i])
	{
		new[i] = ft_strdup(array[i]);
		if (!new[i])
			return (free_dup_array(new, i), NULL);
		i++;
	}
	return (new);
}
