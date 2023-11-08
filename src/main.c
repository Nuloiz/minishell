/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:02:33 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/08 12:51:31 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

static char	**init_main(int *last_return, char **envp, int *argc, char **argv)
{
	char				**new_env;

	set_sig_handle_prompt();
	turn_off_ctl_echo();
	last_return = 0;
	g_signal = 0;
	(void) argc;
	(void) argv;
	new_env = dup_array(envp);
	if (!new_env)
		return (NULL);
	else
		return (new_env);
}

static void	free_main(char **new_env, char *line)
{
	free_array(new_env);
	free(line);
}

int	main(int argc, char **argv, char **envp)
{
	char				**new_env;
	char				*line;
	int					last_return;

	new_env = init_main(&last_return, envp, &argc, argv);
	while (1)
	{
		line = readline("minishell: ");
		if (!line)
		{
			printf("exit\n");
			free_main(new_env, line);
			break ;
		}
		add_history(line);
		set_sig_handle_executer();
		last_return = input_sort(line, &new_env, last_return);
		if (last_return == -1)
			return (free_main(new_env, line), -1);
		g_signal = 0;
		set_sig_handle_prompt();
		free(line);
	}
	return (0);
}
