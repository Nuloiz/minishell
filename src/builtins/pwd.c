/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 18:20:46 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/02 18:25:45 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../tools/ft_printf/ft_printf.h"
#include <unistd.h>
// #include <linux/limits.h>
#include <limits.h>

int	ft_cwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX))
		{
			ft_printf("%s\n", path);
			return (0);
		}
	else
		return (1);
}

int	main(void)
{
	ft_cwd();
}