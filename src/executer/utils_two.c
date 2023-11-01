/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:28:42 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/01 10:12:36 by dnebatz          ###   ########.fr       */
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
// char	**ft_get_commands(t_execute *new, char **parsed)
// {
// 	char	**commands;
// 	int		i;
// 	int		j;
// 	int		size;

// 	i = 0;
// 	j = 0;
// 	size = new->count_builtins + new->count_commands;
// 	commands = malloc(sizeof(char *) * (size + 1));
// 	while (i < size)
// 	{
// 		if (new->types[j] == 5 || new->types[j] == 6)
// 			commands[i++] = ft_strdup(parsed[j]);
// 		j++;
// 	}
// 	commands[i] = NULL;
// 	return (commands);
// }

int	ft_free_end(int ret, char **array, t_execute *exec)
{
	ft_free_array(array);
	// ft_free_array(exec->commands);
	// free(exec->types_commands);
	ft_close_all_fds(exec);
	return (ret);
}

void	write_newline(int pipe, int i, t_execute *exec)
{
	int		len;
	char	*red_line_newline;
	char	*red_line;

	red_line = readline("-> ");
	while (red_line != NULL)
	{
		red_line_newline = ft_strjoin(red_line, "\n");
		if (ft_strlen(red_line) - 1 < ft_strlen(exec->token[i]->limiter))
			len = ft_strlen(exec->token[i]->limiter);
		else
			len = ft_strlen(red_line);
		if (ft_strncmp(red_line, exec->token[i]->limiter, len) == 0)
			break ;
		write(exec->pipe_fd[pipe][1],
			red_line_newline, ft_strlen(red_line_newline));
		free(red_line_newline);
		free(red_line);
		red_line = readline("-> ");
	}
	free(red_line);
}
