/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 11:18:49 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/06 15:39:24 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_fork(t_execute *exec, int i)
{
	if (i == exec->count_children)
		i--;
	if ((exec->id[i] < 0) && (i < exec->count_children))
	{
		perror("fork error");
		return (-1);
	}
	return (i);
}

int	ft_forking(t_execute *exec)
{
	int	i;
	int	error;

	error = 0;
	i = -1;
	exec->id[0] = 1;
	while (++i < exec->count_children && !(
			exec->count_builtins == 1 && exec->count_children == 1))
	{
		exec->id[i] = fork();
		if (exec->id[i] == 0)
			break ;
	}
	i = ft_check_fork(exec, i);
	if (i < 0)
		return (1);
	if (exec->id[i] == 0)
		exec->error += ft_child(i, exec);
	else if (exec->id[i] > 0)
		exec->error += ft_parent(exec);
	return (error);
}
