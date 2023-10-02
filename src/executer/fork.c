/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:18:49 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/02 09:47:18 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_last_child(t_execute *exec, int i)
{
	close(exec->pipe_fd[0][1]);
	exec->pipe_fd[0][1] = open(exec->argv[exec->argc - 1], O_RDWR
			| O_CREAT | O_TRUNC, 0644);
	if (exec->pipe_fd[0][1] < 1)
	{
		perror("Error");
		return (1);
	}
	exec->error += ft_child(i, exec);
	return (0);
}

int	ft_first_child(t_execute *exec, int i)
{
	close(exec->pipe_fd[exec->count_pipes - 1 - exec->here_doc][0]);
	exec->pipe_fd[exec->count_pipes - 1 - exec->here_doc][0]
		= open(exec->argv[1], O_RDONLY);
	if (exec->pipe_fd[exec->count_pipes - 1 - exec->here_doc][0] < 1)
	{
		perror("Error");
		return (1);
	}
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
	while (++i < exec->count_children)
	{
		exec->id[i] = fork();
		if (exec->id[i] == 0)
			break ;
	}
	i = ft_check_fork(exec, i);
	if (i < 0)
		return (1);
	if (exec->id[i] == 0 && i == 0 && exec->here_doc)
		exec->error += ft_child(i, exec);
	else if (exec->id[i] == 0 && i == 0)
		error = ft_first_child(exec, i);
	else if (exec->id[i] == 0 && i == exec->count_children - 1)
		error = ft_last_child(exec, i);
	else if (exec->id[i] == 0)
		exec->error += ft_child(i, exec);
	else if (exec->id[i] > 0)
		exec->error += ft_parent(exec);
	return (error);
}
