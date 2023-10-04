/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:33:33 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/04 22:15:05 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sort_chars(char ***array)
{
	int		i;
	int		len_string;
	int		j;
	char	*temp;
	int		len;

	i = 0;
	len_string = ft_array_size(*array);
	while (i < len_string - 1)
	{
		j = i + 1;
		while (j < len_string)
		{
			if (ft_strlen(*array[i]) > ft_strlen(*array[j]))
				len = ft_strlen(*array[i]);
			else
				len = ft_strlen(*array[j]);
			if (ft_strncmp(*array[i], *array[j], len) > 0)
			{
				temp = *array[i];
				*array[i] = *array[j];
				*array[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	ft_sorted_print_array(char **envp)
{
	int	i;

	i = 0;
	// ft_sort_chars(&envp);
	while (envp[i])
	{
		dprintf(2, "declare -x %s\n", envp[i]);
		i++;
	}
}

//add or replace the value of the string in the 2D envp array
int	ft_export(char ***envp, char *string)
{
	int		i;
	int		found;
	char	**splitted;

	splitted = ft_split(string, ' ');
	found = 0;
	printf("export started\n");
	if (!*envp)
		ft_putstr_fd("NO ENVP\n", 2);
	if (!splitted[1])
	{
		printf("export without arguements\n");
		ft_sorted_print_array(*envp);
		return (0);
	}
	i = 0;
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

// int	main(int argc, char **argv, char **envp)
// {
// 	char	**testenvp;

// 	testenvp = malloc(sizeof(char *) * (4 + 1));
// 	testenvp[0] = ft_strdup("SHLVL=1");
// 	testenvp[1] = ft_strdup("PWD=/Users/dnebatz/Docu3b94-src/builtins");
// 	testenvp[2] = ft_strdup("LANG=lekcer");
// 	testenvp[3] = ft_strdup("TERM=xterm-256color");
// 	testenvp[4] = NULL;
// 	printf("FIRST: \n");
// 	ft_env(testenvp);
// 	ft_export(&testenvp, "LANG=POMMESBURGER2000PMESBURGER2001");
// 	printf("After first: \n");
// 	ft_export(&testenvp, "LANG=POBU2001");
// 	printf("After second: \n");
// 	ft_env(testenvp);
// 	ft_export(&testenvp, "AUTO=VW");
// 	printf("After third: \n");
// 	ft_env(testenvp);
// 	int i = 0;
// 	while (testenvp[i])
// 	{
// 		printf("%s i: %i\n", testenvp[i], i);
// 		free(testenvp[i]);
// 		i++;
// 	}
// 	free(testenvp[i]);
// 	free(testenvp);
// }
