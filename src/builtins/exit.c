/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:41:17 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/09 09:00:10 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *string)
{
	int	i;
	int	ret_value;

	i = -1;
	ret_value = 0;
	while (string[++i])
	{
		if (string[i] >= '0' && string[i] <= '9')
			ret_value = 1;
	}
	return (ret_value);
}

static int	set_exit_return(char **splitted)
{
	if (is_numeric(splitted[1]) != 0)
		return (ft_atoi(splitted[1]));
	else
	{
		ft_putstr_fd
			("minishell: exit: a: numeric argument required\n", 2);
		return (255);
	}
}

static void	free_exit(t_execute *exec, char **splitted)
{
	free_array(splitted);
	free_token(exec->token);
	ft_free_array(*exec->envp);
	ft_close_all_fds(exec);
	ft_free_data(exec);
}

void	ft_exit(t_execute *exec, char *args)
{
	char	**splitted;
	int		ret_value;

	splitted = NULL;
	ret_value = 0;
	if (args)
	{
		splitted = ft_split(args, ' ');
		if (ft_array_size(splitted) > 2)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			ret_value = 1;
		}
		else if (splitted[1])
			ret_value = set_exit_return(splitted);
	}
	free_exit(exec, splitted);
	exit(ret_value);
}

void	free_token(t_command **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		free(token[i]->command);
		free(token[i]->input);
		free(token[i]->output);
		free(token[i]->limiter);
		free(token[i]);
		i++;
	}
	free(token[i]);
	free(token);
	token = NULL;
}
