/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:57:58 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/30 17:36:20 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns a new array with string appended, frees old array
char	**ft_delete_from_array(char **array, char *string)
{
	int		size;
	char	**new_array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = ft_array_size(array);
	new_array = malloc(sizeof(char *) * (size));
	while (i < size)
	{
		if (!ft_strncmp(array[i], string, ft_strlen(string)))
			i++;
		else
		{
			new_array[j] = ft_strdup(array[i]);
			i++;
			j++;
		}
	}
	ft_free_array(array);
	new_array[j] = NULL;
	return (new_array);
}

//add or replace the value of the string in the 2D envp array
int	ft_unset(char ***envp, char *string)
{
	char	*string_equal;
	char	**splitted;

	splitted = ft_split(string, ' ');
	if (!splitted[1])
		return (0);
	if (!*envp)
		ft_putstr_fd("NO ENVP\n", 2);
	string_equal = ft_strjoin(splitted[1], "=");
	*envp = ft_delete_from_array(*envp, string_equal);
	free(string_equal);
	ft_free_array(splitted);
	return (0);
}

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**testenvp;
// 	int		i;

// 	i = 0;
// 	testenvp = malloc(sizeof(char *) * (4 + 1));
// 	testenvp[0] = ft_strdup("SHLVL=1");
// 	testenvp[1] = ft_strdup("PWD=/Users/dnebatz/Docu230-dnebatz/src/builtins");
// 	testenvp[2] = ft_strdup("LANG=lekcer");
// 	testenvp[3] = ft_strdup("TERM=xterm-256color");
// 	testenvp[4] = NULL;
// 	// ft_env(testenvp);
// 	ft_unset(&testenvp, "PWD");
// 	while (testenvp[i])
// 	{
// 		printf("%s i: %i\n", testenvp[i], i);
// 		free(testenvp[i]);
// 		i++;
// 	}
// 	free(testenvp[i]);
// 	free(testenvp);
// 	// ft_env(testenvp);
// }
