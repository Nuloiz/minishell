/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:32:24 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/03 21:08:09 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_parent(t_execute *exec)
{
	int	i;
	int	status;

	// if (exec.builtin == 1)
	// 	ft_
	ft_close_all_fds(exec);
	i = -1;
	while (++i < exec->count_children)
	{
		waitpid(exec->id[i], &status, 0);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

// standard input now last pipe read end
// standard input now before pipe read end
// standard output now first pipe write end
// standard output now pipe write end
int	ft_child(int i, t_execute *exec)
{
	char	**command_array;
	char	*command;

	ft_close_fds(exec, i);
	if (i == 0)
		dup2(exec->pipe_fd[exec->count_pipes - 1][0], 0);
	else
		dup2(exec->pipe_fd[i - 1][0], 0);
	if (i == exec->count_children - 1)
		dup2(exec->pipe_fd[0][1], 1);
	else
		dup2(exec->pipe_fd[i][1], 1);
	printf("exec->commands[%i] to split: %s", i, exec->commands[i]);
	command_array = ft_get_command_arg_array
		(exec->commands[i]);
	command = ft_check_command_and_get_path(command_array[0], exec->envp);
	if (command == NULL)
	{
		ft_free_array(command_array);
		return (ft_print_command_error(exec->commands, 127, i));
	}
	execve(command, command_array, exec->envp);
	perror("Execve error:");
	ft_free_array(command_array);
	free(command);
	return (127);
}

int	ft_here_doc(t_execute *exec)
{
	char	*red_line;
	int		len;

	ft_printf("-> ");
	red_line = get_next_line(0);
	while (red_line != NULL)
	{
		if (ft_strlen(red_line) - 1 < ft_strlen(exec->limiter))
			len = ft_strlen(exec->limiter);
		else
			len = ft_strlen(red_line) - 1;
		if (ft_strncmp(red_line, exec->limiter, len) == 0)
			break ;
		write(exec->pipe_fd[exec->count_pipes - 1][1],
			red_line, ft_strlen(red_line));
		free(red_line);
		ft_printf("-> ");
		red_line = get_next_line(0);
	}
	close(exec->pipe_fd[exec->count_pipes - 1][1]);
	free(red_line);
	return (1);
}

int	execute(int *types, char **parsed, char **envp)
{
	t_execute	exec;
	int			error;

	error = 0;
	if (ft_init(&exec, types, parsed, envp))
		return (1);
	if (exec.limiter)
		ft_here_doc(&exec);
	error = ft_forking(&exec);
	if (error)
		return (error);
	ft_free_data(&exec);
	return (exec.error);
}

//call initialisation for struct, set here_doc and open pipes
int	ft_init(t_execute *exec, int *types, char **parsed, char **envp)
{
	int	i;

	i = -1;
	// 
	ft_init_struct(exec, types, parsed, envp);
	if (exec->id == NULL || exec->pipe_fd == NULL)
		return (1);
	while (++i < exec->count_pipes)
	{
		exec->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (exec->pipe_fd[i] == NULL)
			return (1);
	}
	i = -1;
	while (++i < exec->count_pipes)
	{
		if (pipe(exec->pipe_fd[i]) == -1)
		{
			ft_putstr_fd("Pipe Error!\n", 2);
			return (1);
		}
	}
	return (0);
}
