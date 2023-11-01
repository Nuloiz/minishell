/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modified_strjoin_nocheck.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:40:26 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/01 13:44:13 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*mod_nocheck_strjoin(char *s1, char *s2)
{
	char	*joined;
	int		i;

	i = -1;
	joined = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (joined)
		joined = modified_strjoin_join(joined, s1, s2, i);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (joined);
}
