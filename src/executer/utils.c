/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 20:50:22 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/17 11:58:22 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_struct(t_execute *new, int *types, char **parsed, char ***envp)
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
	while (types[++i])
	{
		if (types[i] == 1)
			new->input = parsed[i];
		if (types[i] == 3 || (types[i] == 4))
		{
			if (types[i] == 4)
				new->append = 1;
			new->output = parsed[i];
		}
		if (types[i] == 2)
			new->limiter = parsed[i];
		if (types[i] == 2)
			new->count_limiter ++;
		if (types[i] == 5)
			++new->count_commands;
		if (types[i] == 6)
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
	new->types = types;
	new->commands = ft_get_commands(new, parsed);
	new->types_commands = ft_get_types_commands(new);
	int j = 0;
	while (new->commands[j])
		dprintf(2, "new->commands[i]: %s\n", new->commands[j++]);
	dprintf(2, "new->commands[i]: %s\n", new->commands[j++]);
	// int j = -1;
	// while (new->commands[++j])
	// 	printf("commands: %s\n", new->commands[j]);
	// printf("count_children: %i count_commands: %i count_builtins: %i  count_pipes: %i\n", new->count_children, new->count_commands, new->count_builtins, new->count_pipes);
	return (1);
}

// int	ft_init_struct(t_execute *new, int argc, char **argv, char **envp)
// {
// 	new->count_children = argc - 3 - new->here_doc;
// 	new->id = malloc(sizeof(int) * (new->count_children));
// 	new->count_pipes = argc - 4;
// 	if (new->count_pipes < 1)
// 		new->count_pipes = 1;
// 	printf("count pipes: %i\n", new->count_pipes);
// 	new->pipe_fd = malloc(sizeof(int *) * (new->count_pipes));
// 	new->error = 0;
// 	new->commands = &argv[2 + new->here_doc];
// 	new->envp = envp;
// 	new->argc = argc;
// 	new->argv = argv;
// 	return (1);
// }

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
