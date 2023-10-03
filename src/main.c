/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:19:04 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/03 21:34:12 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "executer/pipex.h"

void	ft_sig_handle(int sig)
{
	if (sig == 2)
	{
		// rl_replace_line("", 0);
		// printf("signal: %i caught! i will be a new promt on new line\n", sig);
		// printf("minishell after signal2-0.1$ ");
		// 
		rl_replace_line("hello\n", 0);
		// write(0, "\n", 2);
		rl_on_new_line();
		rl_redisplay();
		// readline, rl_clear_history, rl_on_new_line,
		// rl_replace_line, rl_redisplay
	}
	else
		printf("signal: %i caught!\n", sig);
}

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sa;
	char				*line;

	sa.sa_handler = &ft_sig_handle;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	// rl_replace_line("hello", 1);
	// rl_redisplay();
	line = readline(0);
	// ft_putstr_fd("hello\n", 1);

	// char *testargv[] = {"input.txt", "cat -e", "cat -e", "grep a", "cat -e", NULL};
	// int	testintargv[] = {1, 5, 6, 5, 5, NULL};
	// char *testargv[] = {"cat -e", "cat -e", "grep a", "cat -e", "output.txt", NULL};
	// int	testintargv[] = {5, 6, 5, 5, 3, NULL};
	// char *testargv[] = {"cat -e", "cat -e", "grep a", "cat -e", "output.txt", NULL};
	// int	testintargv[] = {5, 6, 5, 5, 4, NULL};
	// char *testargv[] = {"ls -a", "cat -e", "grep a", "cat -e", NULL};
	// int	testintargv[] = {5, 6, 5, 5, NULL};
	char *testargv[] = {"ls -a", "cat -e", "grep a", "cat -e", "output.txt", NULL};
	int	testintargv[] = {5, 6, 5, 5, 3, NULL};
	// char *testargv[] = {"input.txt", "cat -e", "cat -e", "grep a", "cat -e", "output.txt", NULL};
	// int	testintargv[] = {1, 5, 6, 5, 5, 4, NULL};
	// char *testargv[] = {"cat -e", "echo hallo", "wc -l", NULL};
	// int	*testintargv[] = {5, 6, 5, NULL};
	// char *testargv[] = {"end", "cat -e", "echo hallo", "wc -l", "output.txt", NULL};
	// int	*testintargv[] = {2, 5, 6, 5, 4, NULL};
	// input 1
	// limiter 2
	// output 3
	// append 4
	// command 5
	// builtin 6
	execute(testintargv, testargv, envp);
	// rl_replace_line("hello", 1);
	// rl_redisplay();
	// line = readline(0);
	return (0);
}
