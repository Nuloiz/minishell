/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:41:17 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/02 15:58:15 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_execute *exec)
{
	int		i;

	i = 0;
	while (exec->token[i])
	{
		free(exec->token[i]->command);
		free(exec->token[i]->input);
		free(exec->token[i]->output);
		free(exec->token[i]->limiter);
		free(exec->token[i]);
		i++;
	}
	free(exec->token[i]);
	free(exec->token);
	ft_free_array(*exec->envp);
	ft_close_all_fds(exec);
	ft_free_data(exec);
	exit(0);
}
