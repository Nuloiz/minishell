/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:41:17 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/03 09:57:32 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_execute *exec)
{
	free_token(exec->token);
	ft_free_array(*exec->envp);
	ft_close_all_fds(exec);
	ft_free_data(exec);
	exit(0);
}

void	free_token(t_command **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		free(token[i]->command);
		free(token[i]->input);
		free(token[i]->output);
		free(token[i]->limiter);
		free(token[i]);
		i++;
	}
	free(token[i]);
	free(token);
}
