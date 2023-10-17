/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:28:42 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/16 20:47:26 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_remove_slash(char *deleted)
{
	int		i;
	int		len;
	int		j;
	char	*new_deleted;

	len = ft_strlen(deleted);
	i = 0;
	j = 0;
	if (!deleted)
		return (NULL);
	if (!*deleted)
		return (NULL);
	new_deleted = malloc
		(sizeof(char) * len - ft_strchr_count(deleted, '\\') + 1);
	while (i < len - 1)
	{
		if (deleted[i] == '\\'
			&& (deleted[i + 1] == '"' || deleted[i + 1] == '\'' ))
			j++;
		new_deleted[j++] = deleted[i++];
	}
	new_deleted[j++] = deleted[i];
	new_deleted[j] = 0;
	free(deleted);
	return (new_deleted);
}

// returns array with just commands and builtins
char	**ft_get_commands(t_execute *new, char **parsed)
{
	char	**commands;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = new->count_builtins + new->count_commands;
	commands = malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		if (new->types[j] == 5 || new->types[j] == 6)
			commands[i++] = ft_strdup(parsed[j]);
		j++;
	}
	commands[i] = NULL;
	return (commands);
}

int	ft_free_end(int ret, char **array, t_execute *exec)
{
	ft_free_array(array);
	ft_free_array(exec->commands);
	ft_free_array(exec->types_commands);
	ft_close_all_fds(exec);
	return (ret);
}

// returns array with just commands and builtins
int	*ft_get_types_commands(t_execute *new)
{
	int	*types_commands;
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	size = new->count_builtins + new->count_commands;
	types_commands = malloc(sizeof(int *) * (size + 1));
	while (i < size)
	{
		if (new->types[j] == 5 || new->types[j] == 6)
			types_commands[i++] = new->types[j];
		j++;
	}
	types_commands[i] = NULL;
	return (types_commands);
}
