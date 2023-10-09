/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:19:04 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/09 13:50:03 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <unistd.h>
// #include <signal.h>
// #include <stdio.h>
// #include "executer/pipex.h"

// void	ft_sig_handle(int sig)
// {
// 	if (sig == 2)
// 	{
// 		// rl_replace_line("", 0);
// 		// printf("signal: %i caught! i will be a new promt on new line\n", sig);
// 		// printf("minishell after signal2-0.1$ ");
// 		// 
// 		rl_replace_line("hello\n", 0);
// 		// write(0, "\n", 2);
// 		rl_on_new_line();
// 		rl_redisplay();
// 		// readline, rl_clear_history, rl_on_new_line,
// 		// rl_replace_line, rl_redisplay
// 	}
// 	else
// 		printf("signal: %i caught!\n", sig);
// }

int	main(int argc, char **argv, char **envp)
{
	// struct sigaction	sa;
	char				*line;

	// sa.sa_handler = &ft_sig_handle;
	// sa.sa_flags = SA_RESTART;
	// sigaction(SIGINT, &sa, NULL);
	// signal(SIGQUIT, SIG_IGN);
	// rl_replace_line("hello", 1);
	// rl_redisplay();
	line = readline(0);
	add_history(line);
	while (line)
		{
			input_sort(line, envp);
			// printf("line: %s\n", line);
			free(line);
			line = readline(0);
			add_history(line);
		}
		// input_sort(line, envp);
	return (0);
}
