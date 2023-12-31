/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:33:33 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/15 12:46:12 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_splitted(char **splitted)
{
	int	i;
	int	once;
	int	ret_value;

	i = 0;
	once = 0;
	ret_value = 1;
	while (splitted[i])
	{
		ft_printf("%s", splitted[i]);
		if (splitted[i + 1] && !once)
		{
			once = 1;
			ft_printf("=\"");
			ret_value = 0;
		}
		i++;
	}
	return (ret_value);
}

void	ft_print_export(char **envp)
{
	int		i;
	char	**splitted;

	i = 0;
	while (envp[i])
	{
		splitted = ft_split(envp[i], '=');
		ft_printf("declare -x ");
		if (!print_splitted(splitted))
			ft_printf("\"\n");
		else
			ft_printf("\n");
		free_array(splitted);
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
	char	**duped;

	len = 0;
	duped = dup_array(envp);
	while (duped[len])
		len++;
	ft_sort_array(&duped, len);
	ft_print_export(duped);
	free_array(duped);
}

//add or replace the value of the string in the 2D envp array
int	ft_export(char ***envp, char *string)
{
	char	**splitted;
	int		i;

	i = 0;
	splitted = ft_split(string, ' ');
	if (!*envp)
		ft_putstr_fd("NO ENVP\n", 2);
	if (!splitted[1])
		return (free_array(splitted), ft_sorted_print_array(*envp), 0);
	while (splitted[++i])
	{
		if (!check_identifier(splitted[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(splitted[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			return (free_array(splitted), 1);
		}
	}
	find_and_set(envp, splitted);
	return (free_array(splitted), 0);
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
