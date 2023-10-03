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

typedef struct s_input
{
	struct s_input	*next;
	char			*word;
	int				type;
	//COMMAND	= 1;
	//FLAGS		= 2;
	//FILE		= 3;
	//OPERATOR	= 4;
	//PIPE		= 5;
	//QUOTES	= 6;
	//REDIRECT	= 7;
	//PARAM		= 8;
}				t_input;

int		main(int argc, char **argv, char **envp);
int		input_sort(char *line, char **envp);
void	mod_lstadd_back(t_input **lst, t_input *new);
t_input	*mod_lstlast(t_input *lst);
int		input_type(char *s, char *s_one, char **envp);
int		is_op(char *s);
int		is_pipe(char *s);
int		is_quote(char s);
int		is_red(char *s);
int		is_file(char *s);	
char	**mod_split(char const *s, char c);
void	free_array(char **array);
int		ft_array_size(char **array);
int		ft_echo(char **args);
int		ft_env(char **envp);
int		ft_export(char ***envp, char *string);
char	**ft_append_string_to_array(char **array, char *string);
int		ft_cwd(void);
int		ft_unset(char ***envp, char *string);

#endif