/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:56:52 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/15 12:57:24 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_command_error(char *parsed, int error_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(parsed, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (error_code);
}

void	print_cd_error(char **splitted)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(splitted[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

void	print_unset_id_error(char **splitted, int i)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(splitted[i], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
