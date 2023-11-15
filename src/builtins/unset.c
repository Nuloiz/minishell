/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:57:58 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/15 11:26:00 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns position of the enviroment variable in the 2D array
int	get_env_pos(char **envp, char *string)
{
	int	i;
	int	len;

	i = 0;
	while (envp[i])
	{
		len = get_export_length(envp[i], string);
		if (!ft_strncmp(envp[i], string, len))
			return (i);
		i++;
	}
	return (-1);
}

//returns a new array with string appended, frees old array
char	**ft_delete_from_array(char **array, int env_pos)
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
		if (i == env_pos)
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
	char	**splitted;
	int		env_pos;
	int		i;

	splitted = ft_split(string, ' ');
	if (!splitted[1])
		return (free_array(splitted), 0);
	if (!*envp)
		ft_putstr_fd("NO ENVP\n", 2);
	i = 0;
	while (splitted[++i])
	{
		if (!check_identifier(splitted[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(splitted[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (free_array(splitted), 1);
		}
		env_pos = get_env_pos(*envp, splitted[i]);
		if (env_pos < 0)
			break ;
		*envp = ft_delete_from_array(*envp, env_pos);
	}
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
