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

int	is_built_in(char *s)
{
	if (!ft_strncmp(s, "cd", 3) || !ft_strncmp(s, "echo", 5) || \
		!ft_strncmp(s, "unset", 6) || !ft_strncmp(s, "export", 7) || \
		!ft_strncmp(s, "exit", 5) || !ft_strncmp(s, "pwd", 4) || \
		!ft_strncmp(s, "env", 4))
		return (1);
	return (0);
}

int	is_pipe(char *s)
{
	if (s[0] == '|' && !s[1])
		return (1);
	return (0);
}

int	is_env_var(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '$' && s[i + 1])
			return (1);
		i++;
	}
	return (0);
}

int	is_red(char s)
{
	if (s == '<' || s == '>')
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
