/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:32:24 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/01 18:58:24 by dnebatz          ###   ########.fr       */
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
	status = 0;
	// dprintf(2, "exec->count_builtins == %i && exec->count_children == %i && exec->count_pipes == %i\n",exec->count_builtins, exec->count_children, exec->count_pipes);
	if (exec->count_builtins == 1 && exec->count_children == 1)
	{
		// dprintf(2, "one and only parent builtin\n");
		if (ft_set_redirects(exec, 0))
			return (1);
		// dprintf(2, "executing builtin: %s in parent\n", exec->token[0]->command);
		execute_builtin(0, exec);
	}
	ft_close_all_fds(exec);
	i = -1;
	// dprintf(2, "parent: exec->count_builtins: %i\n", exec->count_builtins);
	while (++i < exec->count_children && !(exec->count_builtins
			== 1 && exec->count_children == 1))
		waitpid(exec->id[i], &status, 0);
	dup2(stin_backup, 0);
	dup2(sout_backup, 1);
	close(stin_backup);
	close(sout_backup);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (g_signal)
		return (77);
	return (999);
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
		ft_exit(NULL, exec);
	// dprintf(2, "exec->token[i]->type: %i in child: %i and command: %s\n",exec->token[i]->type, i, exec->token[i]->command);
	if (!(exec->token[i]->command))
		ft_exit(NULL, exec);
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

int	ft_here_doc(t_execute *exec)
{
	int		i;
	int		pipe;

	i = -1;
	while (exec->token[++i])
	{
		if (exec->token[i]->limiter)
		{
			if (exec->token[i]->index == 0)
				pipe = exec->count_pipes - 1;
			else
				pipe = exec->token[i]->index - 1;
			write_newline(pipe, i, exec);
			close(exec->pipe_fd[pipe][1]);
		}
	}
	return (1);
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
