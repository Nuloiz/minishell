/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:50:22 by dnebatz           #+#    #+#             */
/*   Updated: 2023/09/21 18:03:46 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_init_struct(t_execute *new, int argc, char **argv, char **envp)
{
	new->count_children = argc - 3 - new->here_doc;
	new->id = malloc(sizeof(int) * (new->count_children));
	new->count_pipes = argc - 4;
	new->pipe_fd = malloc(sizeof(int *) * (new->count_pipes));
	new->error = 0;
	new->commands = &argv[2 + new->here_doc];
	new->envp = envp;
	new->argc = argc;
	new->argv = argv;
	return (1);
}

void	ft_free_data(t_execute *exec)
{
	int	i;

	i = -1;
	while (++i < exec->count_pipes)
		free(exec->pipe_fd[i]);
	free(exec->pipe_fd);
	free(exec->id);
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
		free(array[i]);
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
