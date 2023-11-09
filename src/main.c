/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:02:33 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/09 12:10:50 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

static void	set_sh_path(char ***envp)
{
	char	*exports;

	exports = ft_strdup("export SHLVL=1");
	ft_export(envp, exports);
	free(exports);
	exports = ft_strdup("export PATH=/bin/ls");
	ft_export(envp, exports);
	ft_set_pwd(envp, NULL);
}

static void	set_env(char ***envp)
{
	char	*joined;
	char	*env_sh;
	int		sh_lvl;

	if (ft_array_size(*envp) < 1)
		set_sh_path(envp);
	else
	{
		env_sh = ft_get_env(*envp, "SHLVL");
		sh_lvl = ft_atoi(env_sh);
		sh_lvl++;
		free(env_sh);
		env_sh = ft_itoa(sh_lvl);
		joined = ft_strjoin("export SHLVL=", env_sh);
		ft_export(envp, joined);
		free(joined);
		free(env_sh);
	}
}

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
	set_env(&new_env);
	while (1 && new_env)
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
