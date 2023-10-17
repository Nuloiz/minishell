/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:20:52 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/17 18:59:11 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipe_output_onlyone(t_execute *exec)
{
	if (exec->token[0]->append)
		exec->pipe_fd[0][1] = open(exec->output, O_RDWR
				| O_CREAT | O_APPEND, 0644);
	else
		exec->pipe_fd[0][1] = open(exec->output, O_RDWR
				| O_CREAT | O_TRUNC, 0644);
	if (exec->pipe_fd[0][1] < 1)
	{
		perror("Error Outputfile Only Child");
		return (1);
	}
	return (0);
}

int	ft_pipe_onlyone(t_execute *exec)
{
	close(exec->pipe_fd[0][0]);
	close(exec->pipe_fd[0][1]);
	if (exec->token[0]->input)
	{
		exec->pipe_fd[0][0]
			= open(exec->input, O_RDONLY);
		if (exec->pipe_fd[0][0] < 1)
		{
			perror("Error");
			return (1);
		}
	}
	else
		exec->pipe_fd[0][0] = 0;
	if (exec->token[0]->output)
	{
		dprintf(2, "with output file: %s\n", exec->output);
		if (ft_pipe_output_onlyone(exec))
			return (1);
	}
	else
		exec->pipe_fd[0][1] = 1;
	return (0);
}

int	ft_set_redirects(t_execute *exec, int i)
{
	int	error;

	error = 0;
	if (exec->id[i] == 0 && i == 0 && exec->count_children == 1)
		if (ft_pipe_onlyone(exec))
			return (1);
	else if (exec->id[i] == 0 && i == 0)
		if (ft_pipe_first(exec))
	error += ft_pipe_normal(exec, i);
}
