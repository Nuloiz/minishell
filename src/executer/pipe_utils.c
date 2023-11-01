/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:53:07 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/01 11:55:21 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_input_pipe(t_execute *exec, int i)
{
	int	pipe;

	if (i == 0)
		pipe = exec->count_pipes - 1;
	else
		pipe = i - 1;
	return (pipe);
}

void	set_output_fd(t_execute *exec, int i, int pipe)
{
	if (exec->token[i]->append)
		exec->pipe_fd[pipe][1] = open(exec->token[i]->output, O_RDWR
				| O_CREAT | O_APPEND, 0644);
	else
		exec->pipe_fd[pipe][1] = open(exec->token[i]->output, O_RDWR
				| O_CREAT | O_TRUNC, 0644);
}
