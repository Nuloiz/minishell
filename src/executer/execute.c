/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:32:24 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/03 14:52:48 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_stfds(int stin_backup, int sout_backup)
{
	dup2(stin_backup, 0);
	dup2(sout_backup, 1);
	close(stin_backup);
	close(sout_backup);
}

int	ft_parent(t_execute *exec)
{
	int	ret_value;
	int	stin_backup;
	int	sout_backup;

	stin_backup = 0;
	sout_backup = 1;
	// dprintf(2, "exec->count_builtins == %i && exec->count_children == %i && exec->count_pipes == %i\n",exec->count_builtins, exec->count_children, exec->count_pipes);
	if (exec->count_builtins == 1 && exec->count_children == 1)
	{
		// dprintf(2, "one and only parent builtin\n");
		if (ft_strncmp(exec->token[0]->command, "exit", 4))
		{
			stin_backup = dup(0);
			sout_backup = dup(1);
		}
		if (ft_set_redirects(exec, 0))
			return (ft_close_all_fds(exec), 1);
		// dprintf(2, "executing builtin: %s in parent\n", exec->token[0]->command);
		execute_builtin(0, exec);
	}
	ret_value = wait_return(exec, stin_backup, sout_backup);
	ft_close_all_fds(exec);
	return (0);
}

// standard input now last pipe read end
// standard input now before pipe read end
// standard output now first pipe write end
// standard output now pipe write end
int	ft_child(int i, t_execute *exec)
{
	int		return_val;

	return_val = 0;
	if (ft_set_redirects(exec, i))
		ft_exit(exec, NULL);
	// dprintf(2, "exec->token[i]->type: %i in child: %i and command: %s\n",exec->token[i]->type, i, exec->token[i]->command);
	if (!(exec->token[i]->command))
		ft_exit(exec, NULL);
	if (exec->token[i]->type == 6)
	{
		// dprintf(2, "executing builtin: %s in child: %i\n", exec->token[i]->command, i);
		execute_builtin(i, exec);
		ft_close_all_fds(exec);
		exit(0);
	}
	else
		return_val = execute_command(i, exec);
	ft_close_all_fds(exec);
	exit (return_val);
}

int	execute(char ***envp, t_command **token)
{
	t_execute	exec;
	int			error;

	// dprintf(3, "hello im the execute function\n");
	if (!token || !*token)
		return (0);
	error = 0;
	if (ft_init(&exec, token, envp))
		return (1);
	// if (!token[0])
	// 	return (ft_free_end(0, NULL, &exec));
	if (exec.count_limiter && ft_here_doc(&exec) == -1)
		return (ft_free_end(&exec), 1);
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
