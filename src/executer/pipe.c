/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:20:52 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/19 12:57:11 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// setting redirections
// reading from the pipe before (if first then last)
// writing in the same pipe (if last then first)
int	ft_pipe_normal(t_execute *exec, int i)
{
	if (i == 0)
		dup2(exec->pipe_fd[exec->count_pipes - 1][0], 0);
	else
		dup2(exec->pipe_fd[i - 1][0], 0);
	if (i == exec->count_children - 1)
		dup2(exec->pipe_fd[0][1], 1);
	else
		dup2(exec->pipe_fd[i][1], 1);
	return (0);
}

// sets output to right pipe
int	ft_set_output(t_execute *exec, int i)
{
	int	pipe;

	if (i == exec->count_children - 1)
		pipe = 0;
	else
		pipe = i;
	if (exec->token[i]->output)
	{
		close(exec->pipe_fd[pipe][1]);
		if (exec->token[i]->append)
			exec->pipe_fd[pipe][1] = open(exec->token[i]->output, O_RDWR
					| O_CREAT | O_APPEND, 0644);
		else
			exec->pipe_fd[pipe][1] = open(exec->token[i]->output, O_RDWR
					| O_CREAT | O_TRUNC, 0644);
		if (exec->pipe_fd[pipe][1] < 1)
		{
			perror("Error");
			return (1);
		}
	}
	else
	{
		// only last should have stdout ?!
		if (i == exec->count_children - 1)
		{
			close(exec->pipe_fd[pipe][1]);
			exec->pipe_fd[pipe][1] = 1;
		}
	}
	return (0);
}

// sets input to right pipe
int	ft_set_input(t_execute *exec, int i)
{
	int	pipe;

	if (exec->token[i]->limiter)
		return (0);
	if (i == 0)
		pipe = exec->count_pipes - 1;
	else
		pipe = i - 1;
	// if (exec->token[i]->input && !exec->token[i]->limiter) idk why i did this
	if (exec->token[i]->input)
	{
		close(exec->pipe_fd[pipe][0]);
		exec->pipe_fd[pipe][0] = open(exec->token[i]->input, O_RDONLY);
		if (exec->pipe_fd[pipe][0] < 1)
		{
			perror("Error");
			return (1);
		}
	}
	else
	{
		// only the first should have stdin !
		if (i == 0)
		{
			close(exec->pipe_fd[pipe][0]);
			exec->pipe_fd[pipe][0] = 0;
		}
	}
	return (0);
}

int	ft_set_redirects(t_execute *exec, int i)
{
	int	error;

	error = 0;
	error += ft_set_input(exec, i);
	error += ft_set_output(exec, i);
	ft_close_fds(exec, i);
	error += ft_pipe_normal(exec, i);
	return (error);
}