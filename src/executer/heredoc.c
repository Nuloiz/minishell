/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:25:50 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/06 19:57:23 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if ((len != 0 && ft_strncmp(read_line,
					exec->token[i]->limiter, len) == 0) || read_line == NULL)
		{
			break ;
		}
		write(exec->pipe_fd[pipe][1],
			read_line, ft_strlen(read_line));
		write(exec->pipe_fd[pipe][1], "\n", 1);
		free(read_line);
	}
	free(read_line);
}

void	loop_limiter(t_execute *exec)
{
	int		i;
	int		pipe;

	dprintf(2, "count pipes: %i\n", exec->count_pipes);
	i = -1;
	while (exec->token[++i])
	{
		if (exec->token[i]->limiter)
		{
			if (i == 0)
				pipe = exec->count_pipes - 1;
			else
				pipe = i - 1;
			dprintf(2, "pipe: %i\n", pipe);
			write_newline(pipe, i, exec);
		}
	}
	ft_close_all_fds(exec);
	ft_free_end(exec);
}

int	ft_here_doc(t_execute *exec)
{
	int		id;
	int		status;

	set_sig_handle_ignore();
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		loop_limiter(exec);
		exit(0);
	}
	waitpid(id, &status, 0);
	if (WTERMSIG(status) == SIGINT)
	{
		write(1, "\n", 1);
		return (-1);
	}
	set_sig_handle_executer();
	return (1);
}

int	wait_return(t_execute *exec, int stin_backup, int sout_backup)
{
	int	i;
	int	status;

	status = 0;
	i = -1;
	while (++i < exec->count_children && !(exec->count_builtins
			== 1 && exec->count_children == 1))
		waitpid(exec->id[i], &status, 0);
	restore_stfds(stin_backup, sout_backup);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (g_signal)
		return (g_signal + 128);
	else
		return (0);
}
