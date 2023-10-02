/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:54:21 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/02 19:56:50 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 16:33:33 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/02 19:54:36 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tools/ft_printf/ft_printf.h"

//print 2D Array envp
int	ft_env(char **envp)
{
	int	i;
	char **new_envp;

	i = 0;
	if (!envp)
		ft_putstr_fd("NO ENVP\n", 2);
	// printf("sieof: %i\n", sizeof(string));
	// printf("strlen envp: %i\n", ft_strlen(envp));
	// printf("array size envp: %i\n", ft_array_size(envp));
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	char **testenvp;
	
	testenvp = malloc(sizeof(char *) * (4 + 1));
	testenvp[0] = ft_strdup("SHLVL=1");
	testenvp[1] = ft_strdup("PWD=/Users/dnebatz/Documents/minishell/intra-uuid-bf63c384-be65-493a-ac80-58b75b0f3b94-5190230-dnebatz/src/builtins");
	testenvp[2] = ft_strdup("LANG=lekcer");
	testenvp[3] = ft_strdup("TERM=xterm-256color");
	testenvp[4] = NULL;
	ft_env(testenvp);
	ft_env(testenvp);
	ft_env(testenvp);
}
