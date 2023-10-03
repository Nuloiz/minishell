/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:33:33 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/03 12:28:55 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tools/ft_printf/ft_printf.h"

int	ft_env(char **envp);

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
	int	size;
	char	**new_array;
	int	i;

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


//add or replace the value of the string in the 2D envp array
int	ft_export(char ***envp, char *string)
{
	int	i;
	int	found;

	found = 0;
	i = 0;
	if (!*envp)
		ft_putstr_fd("NO ENVP\n", 2);
	// printf("sieof: %i\n", sizeof(string));
	// printf("strlen envp: %i\n", ft_strlen(envp));
	// printf("array size envp: %i\n", ft_array_size(envp));
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], string, (ft_strchr(string, '=') - string + 1)))
		{
			free((*envp)[i]);
			(*envp)[i] = ft_strdup(string);
			found = 1;
		}
		i++;
	}
	if (!found)
	{
		*envp = ft_append_string_to_array(*envp, string);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	**testenvp;

	testenvp = malloc(sizeof(char *) * (4 + 1));
	testenvp[0] = ft_strdup("SHLVL=1");
	testenvp[1] = ft_strdup("PWD=/Users/dnebatz/Documents/minishell/intra-uuid-bf63c384-be65-493a-ac80-58b75b0f3b94-5190230-dnebatz/src/builtins");
	testenvp[2] = ft_strdup("LANG=lekcer");
	testenvp[3] = ft_strdup("TERM=xterm-256color");
	testenvp[4] = NULL;
	printf("FIRST: \n");
	ft_env(testenvp);
	ft_export(&testenvp, "LANG=POMMESBURGER2000POMMESBURGER2000POMMEOMMESBURGER2001");
	printf("After first: \n");
	ft_export(&testenvp, "LANG=POBU2001");
	printf("After second: \n");
	ft_env(testenvp);
	ft_export(&testenvp, "AUTO=VW");
	printf("After third: \n");
	ft_env(testenvp);
	int i = 0;
	while (testenvp[i])
	{
		printf("%s i: %i\n", testenvp[i], i);
		free(testenvp[i]);
		i++;
	}
	free(testenvp[i]);
	free(testenvp);
}
