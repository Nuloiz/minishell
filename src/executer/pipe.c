/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:20:52 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/08 11:28:57 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// setting redirections
// reading from the pipe before (if first then last)
// writing in the same pipe (if last then first)
int	ft_pipe_normal(t_execute *exec, int i)
{
	if (i == 0)
	{
		if (dup2(exec->pipe_fd[exec->count_pipes - 1][0], 0) < 0)
			perror("dup2 23");
	}
	else
	{
		if (dup2(exec->pipe_fd[i - 1][0], 0) < 0)
			perror("dup2 28");
	}
	if (i == exec->count_children - 1)
	{
		if (dup2(exec->pipe_fd[0][1], 1) < 0)
			perror("dup2 33");
	}
	else
	{
		if (dup2(exec->pipe_fd[i][1], 1) < 0)
		{
			perror("dup2 38");
			dprintf(2, "exec->pipe_fd[%i][1]: %i\n", i, exec->pipe_fd[i][1]);
		}
	}
	return (0);
}

// sets output to right pipe
int	ft_set_output(t_execute *exec, int i)
{
	int	pipe;
	int	next_pipe;

	if (i == exec->count_children - 1)
		pipe = 0;
	else
		pipe = i;
	if (i == exec->count_children - 1)
		next_pipe = 0;
	else
		next_pipe = pipe + 1;
	if (exec->token[i]->output)
	{
		close(exec->pipe_fd[pipe][1]);
		set_output_fd(exec, i, pipe);
		if (exec->pipe_fd[pipe][1] < 1)
		{
			perror("Error");
			return (1);
		}
	}
	else if (exec->token[next_pipe]->limiter && i != exec->count_children - 1)
	{
		dprintf(2, "next pipe: %i from child: %i is limiter setting to garb: %i\n", next_pipe, i, exec->garbage);
		close(exec->pipe_fd[pipe][1]);
		exec->pipe_fd[pipe][1] = exec->garbage;
	}
	else
	{
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

	pipe = get_input_pipe(exec, i);
	// if (exec->token[0]->limiter)
	// 	close(exec->pipe_fd[0][1]);
	if (exec->token[i]->limiter)
		return (0);
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
