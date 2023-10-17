/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 13:16:52 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/17 15:22:37 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_init_types(int *types, char **parsed, t_execute *new)
{
	char	**limiter;
	int		i;
	int		j;

	i = 0;
	j = 0;
	types_commands = malloc(sizeof(int *) * (new->count_limiter + 1));
	while (i < new->count_limiter)
	{
		if (new->types[j] == 5 || new->types[j] == 6)
			types_commands[i++] = new->types[j];
		j++;
	}
	types_commands[i] = NULL;
	return (types_commands);
}

// returns array with just commands and builtins
char	**ft_get_limiter(t_execute *new, char **parsed)
{
	char	**limiter;
	int		i;
	int		j;

	i = 0;
	j = 0;
	limiter = malloc(sizeof(char *) * (new->count_limiter + 1));
	while (i < new->count_limiter)
	{
		if (new->types[j] == 2)
			limiter[i++] = ft_strdup(parsed[j]);
		j++;
	}
	limiter[i] = NULL;
	return (limiter);
}
