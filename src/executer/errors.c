/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:56:52 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/11 19:22:38 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	ft_print_execve_error(char **argv, int error_code)
// {
// 	return (error_code);
// }
int	ft_print_command_error(char **parsed, int error_code, int i)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(parsed[i], 2);
	ft_putstr_fd(": command not found\n", 2);
	exit (error_code);
}
