/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:32:24 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/30 16:46:41 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parent(t_execute *exec)
{
	int	i;
	int	status;
	int	stin_backup;
	int	sout_backup;

	stin_backup = dup(0);
	sout_backup = dup(1);
	// i = 0;
	// dprintf(2, "exec->count_builtins == %i && exec->count_children == %i && exec->count_pipes == %i\n",exec->count_builtins, exec->count_children, exec->count_pipes);
	if (exec->count_builtins == 1 && exec->count_children == 1)
	{
		// dprintf(2, "one and only parent builtin\n");
		if (ft_set_redirects(exec, 0))
			return (1);
		// close(exec->pipe_fd[0][0]);
		// close(exec->pipe_fd[0][1]);
		// if (exec->token[i]->input)
		// {
		// 	// dprintf(2, "with input file\n");
		// 	exec->pipe_fd[0][0]
		// 		= open(exec->token[i]->input, O_RDONLY);
		// 	if (exec->pipe_fd[0][0] < 1)
		// 	{
		// 		perror("Error Inputfile Parent");
		// 		return (1);
		// 	}
		// }
		// else
		// 	exec->pipe_fd[0][0] = 0;
		// if (exec->token[i]->output)
		// {
		// 	// dprintf(2, "with output file\n");
		// 	if (exec->token[i]->append)
		// 		exec->pipe_fd[0][1] = open(exec->token[i]->output, O_RDWR
		// 				| O_CREAT | O_APPEND, 0644);
		// 	else
		// 		exec->pipe_fd[0][1] = open(exec->token[i]->output, O_RDWR
		// 				| O_CREAT | O_TRUNC, 0644);
		// 	if (exec->pipe_fd[0][1] < 1)
		// 	{
		// 		perror("Error Outputfile Parent");
		// 		return (1);
		// 	}
		// }
		// else
		// 	exec->pipe_fd[0][1] = 1;
		// dup2(exec->pipe_fd[0][0], 0);
		// dup2(exec->pipe_fd[0][1], 1);
		// dprintf(2, "executing builtin: %s in parent\n", exec->token[0]->command);
		if (!ft_strncmp(exec->token[0]->command, "echo", 4))
			ft_echo(exec->token[0]->command);
		else if (!ft_strncmp(exec->token[0]->command, "cd", 2))
			ft_cd(exec->token[i]->command, exec->envp);
		else if (!ft_strncmp(exec->token[0]->command, "pwd", 3))
			ft_pwd();
		else if (!ft_strncmp(exec->token[0]->command, "export", 6))
			ft_export(exec->envp, exec->token[0]->command);
		else if (!ft_strncmp(exec->token[0]->command, "unset", 5))
			ft_unset(exec->envp, exec->token[0]->command);
		else if (!ft_strncmp(exec->token[0]->command, "env", 3))
			ft_env(*exec->envp);
		else if (!ft_strncmp(exec->token[0]->command, "exit", 4))
			ft_exit(NULL, exec);
	}
	ft_close_all_fds(exec);
	i = -1;
	// dprintf(2, "parent: exec->count_builtins: %i\n", exec->count_builtins);
	while (++i < exec->count_children && !(exec->count_builtins == 1 && exec->count_children == 1))
	{
		waitpid(exec->id[i], &status, 0);
	}
	dup2(stin_backup, 0);
	dup2(sout_backup, 1);
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

	if (ft_set_redirects(exec, i))
		ft_exit(NULL, exec);
	// dprintf(2, "exec->token[i]->type: %i in child: %i and command: %s\n",exec->token[i]->type, i, exec->token[i]->command);
	if (!(exec->token[i]->command))
		ft_exit(NULL, exec);
	if (exec->token[i]->type == 6)
	{
		// dprintf(2, "executing builtin: %s in child: %i\n", exec->token[i]->command, i);
		if (!ft_strncmp(exec->token[i]->command, "echo", 4))
			ft_echo(exec->token[i]->command);
		else if (!ft_strncmp(exec->token[i]->command, "cd", 2))
			ft_cd(exec->token[i]->command, exec->envp);
		else if (!ft_strncmp(exec->token[i]->command, "pwd", 3))
			ft_pwd();
		else if (!ft_strncmp(exec->token[i]->command, "export", 6))
			ft_export(exec->envp, exec->token[i]->command);
		else if (!ft_strncmp(exec->token[i]->command, "unset", 5))
			ft_unset(exec->envp, exec->token[i]->command);
		else if (!ft_strncmp(exec->token[i]->command, "env", 3))
			ft_env(*exec->envp);
		else if (!ft_strncmp(exec->token[i]->command, "exit", 4))
			ft_exit(exec->token[i]->command, exec);
		ft_close_all_fds(exec);
		exit(0);
	}
	else
	{
		command_array = ft_get_command_arg_array
			(exec->token[i]->command);
		command = ft_check_command_and_get_path(command_array[0], *exec->envp);
		if (command == NULL)
		{
			ft_free_array(command_array);
			return (ft_print_command_error(&exec->token[i]->command, 127, i));
		}
		execve(command, command_array, *exec->envp);
		perror("Execve error");
		if (command != command_array[0])
			free(command);
		ft_free_array(command_array);
	}
	ft_close_all_fds(exec);
	exit (127);
}

int	ft_here_doc(t_execute *exec)
{
	char	*red_line;
	int		len;
	int		i;
	int		pipe;
	char	*red_line_newline;

	i = -1;
	while (exec->token[++i])
	{
		if (exec->token[i]->limiter)
		{
			if (exec->token[i]->index == 0)
				pipe = exec->count_pipes - 1;
			else
				pipe = exec->token[i]->index - 1;
			// dprintf(2, "exec->count_pipes: %i pipe: %i i: %i\n", exec->count_pipes, pipe, i);
			// ft_printf("-> ");
			// red_line = get_next_line(0);
			red_line = readline("-> ");
			red_line_newline = ft_strjoin(red_line, "\n");
			while (red_line != NULL)
			{
				if (ft_strlen(red_line) - 1 < ft_strlen(exec->token[i]->limiter))
					len = ft_strlen(exec->token[i]->limiter);
				else
					len = ft_strlen(red_line);
				// // dprintf(2, "ft_strncmp(red_line :%s exec->token[%i]->limiter: %s, len: %i): %i == 0\n",red_line, i, exec->token[i]->limiter, len, ft_strncmp(red_line, exec->token[i]->limiter, len));
				if (ft_strncmp(red_line, exec->token[i]->limiter, len) == 0)
					break ;
				write(exec->pipe_fd[pipe][1],
					red_line_newline, ft_strlen(red_line_newline));
				free(red_line);
				free(red_line_newline);
				// ft_printf("-> ");
				// red_line = get_next_line(0);
				red_line = readline("-> ");
				red_line_newline = ft_strjoin(red_line, "\n");
			}
			close(exec->pipe_fd[pipe][1]);
			free(red_line);
		}
	}
	return (1);
}

int	execute(char ***envp, t_command **token)
{
	t_execute	exec;
	int			error;

	dprintf(3, "hello im the execute function\n");
	if (!token || !*token)
		return (0);
	error = 0;
	if (ft_init(&exec, token, envp))
		return (1);
	// if (!token[0])
	// 	return (ft_free_end(0, NULL, &exec));
	if (exec.count_limiter)
		ft_here_doc(&exec);
	error = ft_forking(&exec);
	if (error)
		return (error);
	ft_free_data(&exec);
	return (exec.error);
}

//call initialisation for struct, set here_doc and open pipes
int	ft_init(t_execute *exec, t_command **token, char ***envp)
{
	int	i;

	i = -1;
	ft_init_struct(exec, token, envp);
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
		// // dprintf(2, "exec->pipe_fd[%i][0]:%i exec->pipe_fd[%i][1]: %i\n",i, exec->pipe_fd[i][0], i, exec->pipe_fd[i][1]);
	}
	return (0);
}
