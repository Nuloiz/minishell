/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 19:32:24 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/16 10:45:25 by dnebatz          ###   ########.fr       */
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

	stin_backup = dup(0);
	sout_backup = dup(1);
	if (exec->count_builtins == 1 && exec->count_children == 1)
	{
		if (ft_set_redirects(exec, 0))
			return (ft_close_all_fds(exec), 1);
		if (!ft_strncmp(exec->token[0]->command, "exit", 4))
		{
			dup2(stin_backup, 0);
			dup2(sout_backup, 1);
			close(stin_backup);
			close(sout_backup);
		}
		ret_value = execute_builtin(0, exec);
		ft_close_all_fds(exec);
	}
	else
		ret_value = wait_return(exec);
	restore_stfds(stin_backup, sout_backup);
	return (ret_value);
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
	if (!(exec->token[i]->command))
		ft_exit(exec, NULL);
	if (exec->token[i]->type == 6)
	{
		return_val = execute_builtin(i, exec);
		ft_close_all_fds(exec);
		free_exit(exec, NULL);
		exit(return_val);
	}
	else
		return_val = execute_command(i, exec);
	ft_exit(exec, NULL);
	exit(return_val);
}

int	execute(char ***envp, t_command **token)
{
	t_execute	exec;
	int			error;

	if (!token || !*token)
		return (0);
	error = 0;
	if (ft_init(&exec, token, envp))
		return (1);
	exec.garbage = open("grb.tmp", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (exec.garbage < 0)
		return (ft_free_end(&exec), 1);
	if (exec.count_limiter && ft_here_doc(&exec) == -1)
		return (ft_free_end(&exec), 1);
	error = ft_forking(&exec);
	if (error)
		return (ft_free_end(&exec), error);
	ft_free_end(&exec);
	return (error);
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
	}
	return (0);
}
