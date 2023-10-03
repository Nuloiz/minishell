/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:18:32 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/03 13:27:20 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns the count of char arrays in the array
int	ft_array_size(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

//returns a new array with string appended, frees old array
char	**ft_append_string_to_array(char **array, char *string)
{
	int		size;
	char	**new_array;
	int		i;

	i = 0;
	size = ft_array_size(array);
	new_array = malloc(sizeof(char *) * (size + 2));
	while (i < size)
	{
		new_array[i] = ft_strdup(array[i]);
		free(array[i]);
		i++;
	}
	free(array);
	new_array[i++] = ft_strdup(string);
	new_array[i] = NULL;
	return (new_array);
}
