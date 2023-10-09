/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 19:54:21 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/09 12:02:34 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tools/ft_printf/ft_printf.h"

//print 2D Array envp
int	ft_env(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		ft_putstr_fd("NO ENVP\n", 2);
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	char **testenvp;
// 	testenvp = malloc(sizeof(char *) * (4 + 1));
// 	testenvp[0] = ft_strdup("SHLVL=1");
// 	testenvp[1] = ft_strdup("PWD=/Users/src/builtins");
// 	testenvp[2] = ft_strdup("LANG=lekcer");
// 	testenvp[3] = ft_strdup("TERM=xterm-256color");
// 	testenvp[4] = NULL;
// 	ft_env(testenvp);
// 	ft_env(testenvp);
// 	ft_env(testenvp);
// }
