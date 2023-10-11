/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:18:49 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/11 10:36:50 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_last_child(t_execute *exec, int i)
{
	if (exec->output)
	{
		close(exec->pipe_fd[0][1]);
		if (exec->append)
			exec->pipe_fd[0][1] = open(exec->output, O_RDWR
					| O_CREAT | O_APPEND, 0644);
		else
			exec->pipe_fd[0][1] = open(exec->output, O_RDWR
					| O_CREAT | O_TRUNC, 0644);
		if (exec->pipe_fd[0][1] < 1)
		{
			perror("Error Outputfile Child");
			return (1);
		}
		dprintf(2, "last child with output: %s and append is: %i\n", exec->output, exec->append);
	}
	else
	{
		dprintf(2, "last child without output\n");
		close(exec->pipe_fd[0][1]);
		exec->pipe_fd[0][1] = 1;
	}
	exec->error += ft_child(i, exec);
	return (0);
}

int	ft_first_child(t_execute *exec, int i)
{
	dprintf(2, "first child\n");
	if (exec->input)
	{
		close(exec->pipe_fd[exec->count_pipes - 1][0]);
		exec->pipe_fd[exec->count_pipes - 1][0]
			= open(exec->input, O_RDONLY);
		if (exec->pipe_fd[exec->count_pipes - 1][0] < 1)
		{
			perror("Error");
			return (1);
		}
	}
	else
	{
		close(exec->pipe_fd[exec->count_pipes - 1][0]);
		exec->pipe_fd[exec->count_pipes - 1][0] = 0;
	}
	exec->error += ft_child(i, exec);
	return (0);
}

int	ft_child_first_last(t_execute *exec, int i)
{
	dprintf(2, "one and only child\n");
	close(exec->pipe_fd[0][0]);
	close(exec->pipe_fd[0][1]);
	if (exec->input)
	{
		dprintf(2, "with input file\n");
		exec->pipe_fd[exec->count_pipes - 1][0]
			= open(exec->input, O_RDONLY);
		if (exec->pipe_fd[exec->count_pipes - 1][0] < 1)
		{
			perror("Error");
			return (1);
		}
		else
			exec->pipe_fd[0][0] = 0;
	}
	if (exec->output)
	{
		if (exec->append)
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
	}
	else
		exec->pipe_fd[0][1] = 1;
	exec->error += ft_child(i, exec);
	return (0);
}

int	ft_check_fork(t_execute *exec, int i)
{
	if (i == exec->count_children)
		i--;
	if ((exec->id[i] < 0) && (i < exec->count_children))
	{
		dprintf(2, "fork error at id[%i]: %i\n", i, exec->id[i]);
		perror("fork error");
		return (-1);
	}
	return (i);
}

int	ft_forking(t_execute *exec)
{
	int	i;
	int	error;

	error = 0;
	i = -1;
	while (++i < exec->count_children && !exec->count_builtins == 1)
	{
		exec->id[i] = fork();
		if (exec->id[i] == 0)
			break ;
	}
	i = ft_check_fork(exec, i);
	if (i < 0)
		return (1);
	if (exec->id[i] == 0 && i == 0 && exec->limiter && !(exec->count_builtins == 1 && exec->count_children == 1))
		exec->error += ft_child(i, exec);
	else if (exec->id[i] == 0 && i == 0 && exec->count_children == 1 && !(exec->count_builtins == 1 && exec->count_children == 1))
		exec->error += ft_child_first_last(exec, i);
	else if (exec->id[i] == 0 && i == 0 && !(exec->count_builtins == 1 && exec->count_children == 1))
		error = ft_first_child(exec, i);
	else if (exec->id[i] == 0 && i == exec->count_children - 1 && !(exec->count_builtins == 1 && exec->count_children == 1))
		error = ft_last_child(exec, i);
	else if (exec->id[i] == 0 && !(exec->count_builtins == 1 && exec->count_children == 1))
		exec->error += ft_child(i, exec);
	else if (exec->id[i] > 0)
		exec->error += ft_parent(exec);
	return (error);
}
