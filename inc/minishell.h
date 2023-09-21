/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:15:39 by nschutz           #+#    #+#             */
/*   Updated: 2023/09/21 10:22:14 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include "../readline/includes/readline.h"
# include "../readline/includes/history.h"
# include "../readline/includes/rlstdc.h"
// # include <readline/readline.h>
// # include <readline/history.h>
// # include "/Users/dnebatz/goinfre/.brew/opt/readline/include/readline/readline.h"
// # include  "../../../../../goinfre/.brew/opt/readline/include/readline/readline.h"
// # include  "../../../../../goinfre/.brew/opt/readline/include/readline/history.h"
// # include <readline.h>
// # include <history.h>
# include "../tools/ft_printf/ft_printf.h"

#define READLINE_LIBRARY

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
int		is_op(char s);
int		is_pipe(char s);
int		is_quote(char s);
int		is_red(char s);
int		is_file(char *s);
char	**mod_split(char const *s, char c);
void	free_array(char **array);

#endif