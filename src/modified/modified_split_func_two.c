/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modified_split_func_two.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:10:55 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/23 12:12:22 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mod_countsplitting(char *s, int *j, char c)
{
	if (s[*j] == 34 || s[*j] == 39)
	{
		*j = *j + mod_possplit(&s[*j] + 1, s[*j]) + 2;
		if (s[*j] != ' ')
			mod_countsplitting(s, j, c);
	}
	else
		*j = *j + mod_possplit(&s[*j], c);
}
