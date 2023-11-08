/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:50:22 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/08 12:06:14 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_data(t_execute *exec)
{
	int	i;

	i = -1;
	while (++i < exec->count_pipes)
		free(exec->pipe_fd[i]);
	free(exec->pipe_fd);
	exec->pipe_fd = NULL;
	free(exec->id);
	exec->id = NULL;
	unlink("grb.tmp");
}

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
	}
	free(array);
}

void	ft_close_all_fds(t_execute *exec)
{
	int	i;

	i = 0;
	while (i < exec->count_pipes)
	{
		close(exec->pipe_fd[i][0]);
		close(exec->pipe_fd[i][1]);
		i++;
	}
	close(exec->garbage);
}

void	ft_close_fds(t_execute *exec, int current_child)
{
	int	i;

	i = 0;
	while (i < exec->count_pipes)
	{
		if (i != current_child && !(current_child == exec->count_children - 1
				&& i == 0))
		{
			close(exec->pipe_fd[i][1]);
		}
		if (i != current_child - 1 && !(current_child == 0
				&& i == exec->count_pipes - 1))
		{
			close(exec->pipe_fd[i][0]);
		}
		i++;
	}
}

void	close_limiter_pipes(t_execute *exec)
{
	int	i;
	int	pipe;

	i = -1;
	while (exec->token[++i])
	{
		if (exec->token[i]->limiter)
		{
			if (i == 0)
				pipe = exec->count_pipes - 1;
			else
				pipe = i - 1;
			close(exec->pipe_fd[pipe][1]);
		}
	}
}
