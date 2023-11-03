/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:43:22 by dnebatz           #+#    #+#             */
/*   Updated: 2023/11/03 14:32:49 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(void)
{
	char	pwd[PATH_MAX];
	char	*oldpwd;

	if (!(getcwd(pwd, PATH_MAX)))
		return (NULL);
	oldpwd = ft_strjoin("export OLDPWD=", pwd);
	if (!oldpwd)
		return (NULL);
	return (oldpwd);
}

int	ft_set_old_pwd(char ***envp, char *old_pwd)
{
	ft_export(envp, old_pwd);
	free(old_pwd);
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
	char	*old_pwd;

	home = ft_get_env(*envp, "HOME");
	if (!home)
		return (ft_putstr_fd
			("Minishell: Error: cd: PATH HOME not set\n", 2), 1);
	else
	{
		old_pwd = ft_get_pwd();
		if (chdir(home) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(home, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			free(old_pwd);
			return (1);
		}
		ft_set_old_pwd(envp, old_pwd);
		ft_set_pwd(envp, home);
	}
	return (0);
}

int	ft_cd(char *command, char ***envp)
{
	char	**splitted;
	char	*old_pwd;

	splitted = ft_split(command, ' ');
	if (!splitted)
		return (ft_putstr_fd("minishell: cd: error split\n", 2), 1);
	if (splitted[1])
	{
		old_pwd = ft_get_pwd();
		if (chdir(splitted[1]) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(splitted[1], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			free(old_pwd);
			return (1);
		}
		ft_set_old_pwd(envp, old_pwd);
		ft_set_pwd(envp, NULL);
	}
	else
		ft_set_pwd_home(envp);
	return (0);
}
