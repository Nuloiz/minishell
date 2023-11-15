/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:51:34 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/15 11:32:09 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_identifier(char *string)
{
	int	i;
	int	alpha;

	i = -1;
	alpha = 0;
	while (string[++i])
	{
		if (string[i] == '=' && i != 0)
			return (1);
		if (ft_isalpha(string[i]))
			alpha = 1;
		if (!ft_isalpha(string[i]) && string[i] != '_' && alpha != 1)
			return (0);
		if (!ft_isalnum(string[i]) && string[i] != '_')
			return (0);
	}
	return (1);
}

int	get_export_length(char *envp, char *string)
{
	int	len;
	int	len_string;
	int	len_envp;

	if (ft_strchr(envp, '='))
		len_envp = ft_strchr(envp, '=') - envp;
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

//finding the string in the 2D array and replacing
// it with the new value or adding if not found
void	find_and_set(char ***envp, char **splitted)
{
	int		i;
	int		j;
	int		found;
	int		len;

	j = 0;
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
