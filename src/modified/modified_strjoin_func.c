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

char	*mod_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		i;
	int		j;

	i = -1;
	j = -1;
	joined = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char) + 1);
	if (joined)
	{
		while (s1[++i])
			joined[i] = s1[i];
		i = (int)ft_strlen(s1);
		joined[i] = ' ';
		i++;
		while (s2[++j])
		{
			joined[i] = s2[j];
			i++;
		}
		joined[i] = 0;
		return (joined);
	}
	else
		return (0);
}
