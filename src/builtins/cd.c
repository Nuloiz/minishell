/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:43:22 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/09 11:46:36 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_old_pwd(char ***envp)
{
	char	*oldpwd;
	char	pwd[PATH_MAX];

	if (!(getcwd(pwd, PATH_MAX)))
		return (1);
	oldpwd = ft_strjoin("OLDPWD=", pwd);
	if (!oldpwd)
		return (1);
	ft_export(envp, oldpwd);
	free(oldpwd);
	return (0);
}

int	ft_set_pwd(char ***envp)
{
	char	*new_pwd;
	char	pwd[PATH_MAX];


	if (!(getcwd(pwd, PATH_MAX)))
		return (1);
	new_pwd = ft_strjoin("PWD=", pwd);
	if (!new_pwd)
		return (1);
	ft_export(envp, new_pwd);
	free(new_pwd);
	return (0);
}

int	ft_set_pwd_home(char ***envp)
{
	char	*home;

	home = ft_get_env(*envp, "HOME");
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
		ft_set_pwd(envp);
	}
	return (0);
}

int	ft_cd(char *command, char ***envp)
{
	char	*home;
	char	**splitted;

	splitted = ft_split(command, ' ');
	if (splitted)
		return (1);
	if (splitted[0])
	{
		ft_set_old_pwd(envp);
		if (chdir(splitted[0]) == -1)
		{
			ft_putstr_fd("cd: ", 2);
			ft_putstr_fd(splitted[1], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
		ft_set_pwd(envp);
	}
	else
	{
		ft_set_pwd_home(envp);
	}
	return (0);
}

