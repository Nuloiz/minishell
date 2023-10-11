/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:43:22 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/11 10:28:52 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_old_pwd(char ***envp)
{
	char	*oldpwd;
	char	pwd[PATH_MAX];

	if (!(getcwd(pwd, PATH_MAX)))
		return (1);
	oldpwd = ft_strjoin("export OLDPWD=", pwd);
	if (!oldpwd)
		return (1);
	ft_export(envp, oldpwd);
	free(oldpwd);
	return (0);
}

// setting pwd in env to given path, if not set to pwd
int	ft_set_pwd(char ***envp, char *path)
{
	char	*new_pwd;
	char	pwd[PATH_MAX];

	if (!path)
	{
		if (!(getcwd(pwd, PATH_MAX)))
			return (1);
		new_pwd = ft_strjoin("export PWD=", pwd);
		if (!new_pwd)
			return (1);
	}
	else
		new_pwd = ft_strjoin("export PWD=", path);
	ft_export(envp, new_pwd);
	free(new_pwd);
	return (0);
}

int	ft_set_pwd_home(char ***envp)
{
	char	*home;

	home = ft_get_env(*envp, "HOME");
	dprintf(2, "home: %s\n", home);
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	else
	{
		ft_set_old_pwd(envp);
		if (chdir(home) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(home, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
		ft_set_pwd(envp, home);
	}
	return (0);
}

int	ft_cd(char *command, char ***envp)
{
	char	**splitted;

	dprintf(2, "command to split: %s\n", command);
	splitted = ft_split(command, ' ');
	dprintf(2, "splitted: %s\n", splitted[0]);
	if (!splitted)
	{
		ft_putstr_fd("minishell: cd: error split\n", 2);
		return (1);
	}
	dprintf(2, "splitted: %s\n", splitted[0]);
	if (splitted[1])
	{
		dprintf(2, "set pwd: %s\n", splitted[1]);
		ft_set_old_pwd(envp);
		if (chdir(splitted[1]) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(splitted[1], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
		ft_set_pwd(envp, NULL);
	}
	else
	{
		dprintf(2, "set pwd home\n");
		ft_set_pwd_home(envp);
	}
	return (0);
}

