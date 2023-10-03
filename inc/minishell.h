/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:15:39 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/03 13:29:21 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define READLINE_LIBRARY

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include "readline.h"
# include "history.h"
# include "rlstdc.h"
# include <limits.h>
//# include "ft_printf.h"
# include "../tools/ft_printf/ft_printf.h"
# include "../src/executer/pipex.h"

#define COMMAND	1
#define FLAGS	2
#define FILE	3
#define ENV_VAR	4
#define PIPE	5
#define REDIRECT 6
#define BUILTIN	 7
#define PARAM	 8

typedef struct s_input
{
	struct s_input	*next;
	char			*word;
	int				type;
}				t_input;

typedef struct binary_tree
{
	struct binary_tree	*left;
	struct binary_tree	*right;
	char				*word;
	int					type;
}				t_binary_tree;

int		main(int argc, char **argv, char **envp);
int		input_sort(char *line, char **envp);
void	mod_lstadd_back(t_input **lst, t_input *new);
t_input	*mod_lstlast(t_input *lst);
int		input_type(char *s, char *s_one, char **envp);
char	*find_path(char *cmd, char **envp);
int		is_env_var(char *s);
int		is_built_in(char *s);
int		is_pipe(char *s);
int		is_red(char s);
int		is_file(char *s);
int		sort_tree(t_input *input, char **envp);
void	sort_array(t_input *input, char **envp);
char	**mod_split(char const *s, char c);
char	*mod_strjoin(char const *s1, char const *s2);
void	free_array(char **array);
int		ft_array_size(char **array);
int		ft_echo(char **args);
int		ft_env(char **envp);
int		ft_export(char ***envp, char *string);
char	**ft_append_string_to_array(char **array, char *string);
int		ft_cwd(void);
int		ft_unset(char ***envp, char *string);

#endif