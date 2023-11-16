/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:28:42 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/16 10:46:19 by dnebatz          ###   ########.fr       */
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

void	ft_free_end(t_execute *exec)
{
	free_token(exec->token);
	ft_free_data(exec);
}

//executes builtin
int	execute_builtin(int i, t_execute *exec)
{
	int	return_val;

	return_val = 0;
	if (!ft_strncmp(exec->token[i]->command, "echo", 4))
		return_val = ft_echo(exec->token[i]->command);
	else if (!ft_strncmp(exec->token[i]->command, "cd", 2))
		return_val = ft_cd(exec->token[i]->command, exec->envp);
	else if (!ft_strncmp(exec->token[i]->command, "pwd", 3))
		return_val = ft_pwd();
	else if (!ft_strncmp(exec->token[i]->command, "export", 6))
		return_val = ft_export(exec->envp, exec->token[i]->command);
	else if (!ft_strncmp(exec->token[i]->command, "unset", 5))
		return_val = ft_unset(exec->envp, exec->token[i]->command);
	else if (!ft_strncmp(exec->token[i]->command, "env", 3))
		return_val = ft_env(*exec->envp);
	else if (!ft_strncmp(exec->token[i]->command, "exit", 4))
		ft_exit(exec, exec->token[i]->command);
	return (return_val);
}

static void	ft_free_end_execve(t_execute *exec)
{
	free_token(exec->token);
	exec->token = NULL;
	ft_free_data(exec);
	exec = NULL;
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
	ft_free_end_execve(exec);
	execve(command, command_array, *exec->envp);
	perror("Execve error");
	if (command != command_array[0])
		free(command);
	ft_free_array(command_array);
	return (127);
}
