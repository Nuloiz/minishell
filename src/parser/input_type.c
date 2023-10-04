/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 16:40:45 by nschutz           #+#    #+#             */
/*   Updated: 2023/09/18 16:40:45 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char **envp)
{
	int		i;

	i = 0;
	if (*envp == NULL)
		return ("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:");
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
			return (envp[i] + 4);
		i++;
	}
	return (NULL);
}

int	find_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	*path_i;
	char	*path_c;
	char	**new_path;

	path = get_path(envp);
	if (!path | !cmd)
		return (0);
	new_path = ft_split(path, ':');
	i = 0;
	while (new_path[i])
	{
		path_i = ft_strjoin(new_path[i], "/");
		path_c = ft_strjoin(path_i, cmd);
		free(path_i);
		if (access(path_c, R_OK) == 0)
		{
			free_array(new_path);
			free(path_c);
			return (1);
		}
		free(path_c);
		i++;
	}
	return (free_array(new_path), 0);
}

static int	is_flag(char *s)
{
	if (!s)
		return (0);
	else if (s[0] == '-' && s[1] != '\n')
		return (1);
	return (0);
}

static int	is_cmd(char *s, char *s_one, char **envp)
{
	if (find_path(s, envp))
		return (1);
	else if (find_path(s_one, envp) || is_flag(s_one))
	{
		if (is_flag(s) == 1)
			return (2);
	}
	return (0);
}

int	input_type(char *s, char *s_one, char **envp)
{
	int	i;

	if (is_built_in(s))
		return (7);
	i = is_cmd(s, s_one, envp);
	if (i > 0)
		return (i);
	else if (is_file(s))
		return (3);
	else if (is_env_var(s))
		return (4);
	else if (is_pipe(s))
		return (5);
	else if (is_red(s[0]))
		return (6);
	else
		return (8);
}
