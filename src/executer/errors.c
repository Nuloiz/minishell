/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:56:52 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/09 10:34:30 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_print_execve_error(char **argv, int error_code)
// {
// 	return (error_code);
// }
int	ft_print_command_error(char *parsed, int error_code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(parsed, 2);
	ft_putstr_fd(": command not found\n", 2);
	return (error_code);
}
