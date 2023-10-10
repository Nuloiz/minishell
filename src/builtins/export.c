/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:33:33 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/10 19:33:18 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_export(char **envp)
{
	int		i;
	int		j;
	char	**splitted;
	int		once;

	i = 0;
	j = 0;
	once = 0;
	while (envp[i])
	{
		splitted = ft_split(envp[i], '=');
		ft_printf("declare -x ");
		while (splitted[j])
		{
			ft_printf("%s", splitted[j]);
			if (splitted[j + 1] && !once)
			{
				once = 1;
				ft_printf("=\"");
			}
			j++;
		}
		j = 0;
		once = 0;
		free_array(splitted);
		ft_printf("\"\n");
		i++;
	}
}

void	ft_sort_array(char ***arr, int len)
{
	int		i;
	int		j;
	char	*temp;
	int		char_len;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strlen((*arr)[i]) > ft_strlen((*arr)[j]))
				char_len = ft_strlen((*arr)[i]);
			else
				char_len = ft_strlen((*arr)[j]);
			if (ft_strncmp((*arr)[i], (*arr)[j], char_len) > 0)
			{
				temp = (*arr)[i];
				(*arr)[i] = (*arr)[j];
				(*arr)[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	ft_sorted_print_array(char **envp)
{
	int		len;
	char	**splitted;

	len = 0;
	while (envp[len])
		len++;
	ft_sort_array(&envp, len);
	ft_print_export(envp);
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
