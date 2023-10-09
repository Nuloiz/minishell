/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:43:22 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/09 11:36:53 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_old_pwd(char ***envp)
{
	char	*oldpwd;
	char	pwd[PATH_MAX];

	if (!(getcdw(pwd, PATH_MAX)))
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


	if (!(getcdw(pwd, PATH_MAX)))
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
			ft_putstr_fd(splitted[0], 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
		ft_set_pwd(envp);
	}
	else
	{
		
	}
	return (0);
}
