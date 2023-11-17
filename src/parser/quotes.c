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
