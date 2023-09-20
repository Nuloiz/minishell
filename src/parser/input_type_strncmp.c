/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_type_strncmp.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:53:09 by nschutz           #+#    #+#             */
/*   Updated: 2023/09/18 16:53:09 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op(char *s)
{
	if ((s[0] == '-'  && !s[1]) || s[0] == '+')
		return (1);
	return (0);
}

int	is_pipe(char *s)
{
	if (s[0] == '|' && !s[1])
		return (1);
	return (0);
}

int	is_quote(char s)
{
	if (s == 39 || s == 34)
		return (1);
	return (0);
}

int	is_red(char *s)
{
	if (ft_strchr(s, '<') || ft_strchr(s, '>'))
		return (1);
	return (0);
}

int	is_file(char *s)
{
	int	fd1;

	fd1 = open(s, O_RDONLY);
	if (fd1 < 0)
		return (0);
	close (fd1);
	return (1);
}
