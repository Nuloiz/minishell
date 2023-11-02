/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:02:33 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/01 18:53:38 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char				**new_env;
	char				*line;
	int					last_return;
	struct sigaction			sa;

	sa.sa_handler = &ft_sig_handle;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	turn_off_ctl_echo();
	g_signal = 0;
	if (argc && argv)
		argc = 1;
	new_env = dup_array(envp); //leak
	if (!new_env)
		return (-1);
	last_return = 0;
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
		{
			// rl_replace_line("minishell: exit", 0);
			printf("exit\n");
			free_array(new_env);
			free(line);
			break ;
		}

		add_history(line);
		last_return = input_sort(line, &new_env, last_return);
		if (last_return == -1)
		{
			free_array(new_env);
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}
