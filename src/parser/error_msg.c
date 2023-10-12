/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:21:13 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/11 13:21:13 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nv_after_red(t_input **input, int i)
{
	if (i == 2 && (!(*input) || (*input)->type == PIPE || \
			(*input)->type == REDIRECT))
	{
		if (!(*input))
			printf("syntax error near unexpected token `newline'\n");
		else
			printf("syntax error near unexpected token `%s'\n", (*input)->word);
		return (258);
	}
	return (0);
}
