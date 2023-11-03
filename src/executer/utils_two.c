/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:28:42 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/03 11:47:49 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_slash(char *deleted)
{
	int		i;
	int		len;
	int		j;
	char	*new_deleted;

	len = ft_strlen(deleted);
	i = 0;
	j = 0;
	if (!deleted)
		return (NULL);
	if (!*deleted)
		return (NULL);
	new_deleted = malloc
		(sizeof(char) * len - ft_strchr_count(deleted, '\\') + 1);
	while (i < len - 1)
	{
		if (deleted[i] == '\\'
			&& (deleted[i + 1] == '"' || deleted[i + 1] == '\'' ))
			j++;
		new_deleted[j++] = deleted[i++];
	}
	new_deleted[j++] = deleted[i];
	new_deleted[j] = 0;
	free(deleted);
	return (new_deleted);
}

// returns array with just commands and builtins
// char	**ft_get_commands(t_execute *new, char **parsed)
// {
// 	char	**commands;
// 	int		i;
// 	int		j;
// 	int		size;

// 	i = 0;
// 	j = 0;
// 	size = new->count_builtins + new->count_commands;
// 	commands = malloc(sizeof(char *) * (size + 1));
// 	while (i < size)
// 	{
// 		if (new->types[j] == 5 || new->types[j] == 6)
// 			commands[i++] = ft_strdup(parsed[j]);
// 		j++;
// 	}
// 	commands[i] = NULL;
// 	return (commands);
// }

void	ft_free_end(t_execute *exec)
{
	int		i;

	i = 0;
	while (exec->token[i])
	{
		free(exec->token[i]->command);
		free(exec->token[i]->input);
		free(exec->token[i]->output);
		free(exec->token[i]->limiter);
		free(exec->token[i]);
		i++;
	}
	free(exec->token[i]);
	free(exec->token);
	// ft_close_all_fds(exec);
}

//calling readline and writing it in pipe
void	write_newline(int pipe, int i, t_execute *exec)
{
	int		len;
	char	*read_line;

	while (1)
	{
		read_line = readline("-> ");
		if (ft_strlen(read_line) - 1 < ft_strlen(exec->token[i]->limiter))
			len = ft_strlen(exec->token[i]->limiter);
		else
			len = ft_strlen(read_line);
		dprintf(2, "len: %i\n", len);
		if (len != 0 && ft_strncmp(read_line, exec->token[i]->limiter, len) == 0)
		{
			dprintf(2, "im out!\n");
			break ;
		}
		write(exec->pipe_fd[pipe][1],
			read_line, ft_strlen(read_line));
		write(exec->pipe_fd[pipe][1], "\n", 1);
		// free(read_line_newline);
		free(read_line);
	}
	free(read_line);
}

//executes builtin
void	execute_builtin(int i, t_execute *exec)
{
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
		ft_exit(exec, exec->token[i]->command);
}

int	execute_command(int i, t_execute *exec)
{
	char	**command_array;
	char	*command;

	command_array = ft_get_command_arg_array
		(exec->token[i]->command);
	command = ft_check_command_and_get_path(command_array[0], *exec->envp);
	if (command == NULL)
	{
		ft_close_all_fds(exec);
		ft_free_array(command_array);
		return (ft_print_command_error(exec->token[i]->command, 127));
	}
	execve(command, command_array, *exec->envp);
	perror("Execve error");
	if (command != command_array[0])
		free(command);
	ft_free_array(command_array);
	return (127);
}
