/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:51:34 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/13 16:57:49 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_export_length(char *envp, char *string)
{
	int	len;
	int	len_string;
	int	len_envp;

	if (ft_strchr(envp, '='))
		return (ft_strchr(envp, '=') - envp);
	else
		len_envp = ft_strlen(envp);
	if (ft_strchr(string, '='))
		len_string = ft_strchr(string, '=') - string;
	else
		len_string = ft_strlen(string);
	if (len_envp > len_string)
		len = len_envp;
	else
		len = len_string;
	return (len);
}

void	find_and_set(char ***envp, char *string)
{
	char	**splitted;
	int		i;
	int		j;
	int		found;
	int		len;

	splitted = ft_split(string, ' ');
	j = -1;
	while (splitted[++j])
	{
		found = 0;
		i = -1;
		while ((*envp)[++i])
		{
			len = get_export_length((*envp)[i], splitted[j]);
			if (!ft_strncmp((*envp)[i], splitted[j], len))
			{
				free((*envp)[i]);
				(*envp)[i] = ft_strdup(splitted[j]);
				found = 1;
			}
		}
		if (!found)
			*envp = ft_append_string_to_array(*envp, splitted[j]);
	}
}
