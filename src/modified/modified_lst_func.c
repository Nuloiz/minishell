/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modified_lst_func.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 10:52:48 by nschutz           #+#    #+#             */
/*   Updated: 2023/09/20 10:52:48 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_input	*mod_lstlast(t_input *lst)
{
	if (!lst)
		return (0);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	mod_lstadd_back(t_input **lst, t_input *new)
{
	if (lst)
	{
		if ((*lst) != NULL)
		{
			mod_lstlast((*lst))->next = new;
		}
		else
		{
			(*lst) = new;
		}
	}
}
