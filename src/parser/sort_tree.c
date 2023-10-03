/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nschutz <nschutz@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 13:35:06 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/02 16:23:23 by nschutz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tree(t_binary_tree *tree, int i)
{
	if (tree == NULL)
		return;
	i++;
	ft_printf("Word: %s	/	Type: %i	/Num: %i\n", tree->word, tree->type, i);
	if (tree->left)
	{
		ft_printf("left\n");
		print_tree(tree->left, i);
	}
	if (tree->right)
	{
		ft_printf("right\n");
		print_tree(tree->right, i);
	}
}

void	noder(t_binary_tree *root, t_input *input)
{
	t_binary_tree	*new;

	new = ft_calloc(1, sizeof(t_binary_tree));
	new->word = input->word;
	new->type = input->type;
	new->left = root->right;
	root->right = new;
}


t_binary_tree	*new_rootr(t_binary_tree *root, t_input *input)
{
	t_binary_tree	*new;

	new = ft_calloc(1, sizeof(t_binary_tree));
	new->word = input->word;
	new->type = input->type;
	new->right = root;
	return (new);
}

t_binary_tree	*new_rootl(t_binary_tree *root, t_input *input)
{
	t_binary_tree	*new;

	new = ft_calloc(1, sizeof(t_binary_tree));
	new->word = input->word;
	new->type = input->type;
	new->left = root;
	return (new);
}

void	new_left(t_binary_tree *root, t_input *input)
{
	t_binary_tree	*left;
	t_binary_tree	*tree;

	left = ft_calloc(1, sizeof(t_binary_tree));
	tree = root;
	left->word = input->word;
	left->type = input->type;
	while (tree->left)
		tree = tree->left;
	tree->left = left;
}

void	new_right(t_binary_tree *root, t_input *input)
{
	t_binary_tree	*right;
	t_binary_tree	*tree;

	right = ft_calloc(1, sizeof(t_binary_tree));
	tree = root;
	right->word = input->word;
	right->type	= input->type;
	while (tree->right)
		tree = tree->right;
	tree->right = right;
}

t_binary_tree	*fill_tree(t_binary_tree *root, t_input *input)
{
	int	pipe;

	pipe = 0;
	if (!input)
		return (NULL);
	root->word = input->word;
	root->type = input->type;
	input = input->next;
	while (input)
	{
		if (!root->left && (input->type == COMMAND || input->type == BUILTIN))
			new_left(root, input);
		else if (input->type == FLAGS)
			new_right(root, input);
		else if (root->left && (input->type == PARAM || input->type == ENV_VAR))
			new_right(root, input);
		else if (input->type == PIPE)
		{
			root = new_rootl(root, input);
			pipe = 1;
		}
		else if (input->type == REDIRECT && pipe == 1)
		{
			noder(root, input);
			pipe = 0;
			input = input->next;
			new_right(root, input);
			if (input->next)
			{
				input = input->next;
				root = new_rootl(root, input);
			}
		}
		else if (pipe == 0 && root->left && root->right && (input->type == COMMAND \
				 || input->type == BUILTIN || input->type == PARAM))
				 root = new_rootl(root, input);
		else
			new_right(root, input);
		input = input->next;
	}
	return (root);
}

int	sort_tree(t_input *input, char **envp)
{
	t_binary_tree	*root;

	root = ft_calloc(1, sizeof(t_binary_tree));
	//root = fill_tree(root, input);
	//filler(input, envp);
	sort_array(input, envp);
	//print_tree(root, 0);
	return (1);
}
