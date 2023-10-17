/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:50:22 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/17 18:08:06 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_struct(t_execute *new, t_command **token, char ***envp)
{
	int	i;

	i = -1;
	new->input = NULL;
	new->append = 0;
	new->output = NULL;
	new->limiter = NULL;
	new->count_commands = 0;
	new->count_builtins = 0;
	new->count_limiter = 0;
	while (token[++i]->index != -1)
	{
		dprintf(2, "token[%i]->type: %i\n", i, token[i]->type);
		if (token[i]->type == 2)
			new->count_limiter ++;
		if (token[i]->type == 5)
			++new->count_commands;
		if (token[i]->type == 6)
			++new->count_builtins;
	}
	new->count_children = new->count_commands + new->count_builtins;
	new->id = malloc(sizeof(int) * (new->count_children));
	new->count_pipes = new->count_children - 1;
	if (new->count_limiter)
		new->count_pipes++;
	if (new->count_pipes < 1)
		new->count_pipes = 1;
	new->pipe_fd = malloc(sizeof(int *) * (new->count_pipes));
	new->error = 0;
	new->envp = envp;
	new->token = token;
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
		// free(array[i]);
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
		dprintf(2, "closed pipe_fd[%i][0]: %i pipe_fd[%i][1]: %i\n", i, exec->pipe_fd[i][0], i, exec->pipe_fd[i][1]);
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
			dprintf(2, "closed pipe_fd[%i][1]: %i\n", i, exec->pipe_fd[i][1]);
		}
		if (i != current_child - 1 && !(current_child == 0
				&& i == exec->count_pipes - 1))
		{
			close(exec->pipe_fd[i][0]);
			dprintf(2, "closed pipe_fd[%i][0]: %i \n", i, exec->pipe_fd[i][0]);
		}
		i++;
	}
}
