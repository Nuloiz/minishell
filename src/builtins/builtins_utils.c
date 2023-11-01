/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 13:18:32 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/01 11:47:40 by dnebatz          ###   ########.fr       */
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

char	*ft_get_env(char **envp, char *string)
{
	int		i;
	char	*string_equal;
	char	*env;

	i = 0;
	env = NULL;
	string_equal = ft_strjoin(string, "=");
	if (envp == NULL)
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], string_equal, ft_strlen(string_equal)))
		{
			env = ft_strdup(envp[i]);
			ft_memmove(env, &env[ft_strlen(string) + 1],
				(ft_strlen(env) - ft_strlen(string)));
			free(string_equal);
			return (env);
		}
		i++;
	}
	free(string_equal);
	return (env);
}
