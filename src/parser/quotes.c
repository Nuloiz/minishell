/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:48:32 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/03 14:48:32 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*string_vor_quote(char *s, int l_r, char **envp)
{
	char	*tmp;

	if (is_env_var(s))
	{
		tmp = env_var(s, envp, l_r);
		return (free(s), tmp);
	}
	else
		return (s);
}

char	*get_env_in_quotes(char *s, int *i, t_quote info)
{
	char	*tmp;
	char	*str;
	int		j;

	j = *i;
	while (s[*i] && s[*i] != info.c)
		(*i)++;
	str = ft_substr(s, j, *i - j);
	if (!str)
		return (NULL);
	tmp = env_var(str, info.envp, info.l_r);
	return (free(str), tmp);
}
