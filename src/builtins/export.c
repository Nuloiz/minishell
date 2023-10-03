/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:33:33 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/03 13:27:30 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//add or replace the value of the string in the 2D envp array
int	ft_export(char ***envp, char *string)
{
	int	i;
	int	found;

	found = 0;
	i = 0;
	if (!*envp)
		ft_putstr_fd("NO ENVP\n", 2);
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
