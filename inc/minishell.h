/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:15:39 by nschutz           #+#    #+#             */
/*   Updated: 2023/10/16 20:42:13 by dnebatz          ###   ########.fr       */
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
// # include "../src/executer/pipex.h"
# include <errno.h>

#define COMMAND 1
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

typedef struct s_array
{
	char	**cmds;
	char	***envp;
	int		*type;
}				t_array;

typedef struct s_execute {
	char	*input;
	int		append;
	char	*output;
	char	*limiter;
	int		count_commands;
	int		count_builtins;
	int		count_children;
	int		count_limiter;
	int		*id;
	int		count_pipes;
	int		**pipe_fd;
	int		error;
	char	**commands;
	char	***envp;
	int		*types_commands;
	int		*types;
}	t_execute;

int		main(int argc, char **argv, char **envp);
int		input_sort(char *line, char ***envp, int *l_r);
void	mod_lstadd_back(t_input **lst, t_input *new);
t_input	*mod_lstlast(t_input *lst);
int		input_type(char *s, char *s_one, char **envp);
int		is_env_var(char *s);
int		is_built_in(char *s);
int		is_pipe(char *s);
int		is_red(char s);
int		is_file(char *s);
int		sort_array(t_input **input, t_array *array);
int		nv_after_red(t_input **input, int i);
char	*mod_get_env(char **envp, char *string, int j, char *s);
char	**mod_split(char *s, char c);
char	*mod_strjoin(char *s1, char *s2);
char	*modified_strjoin(char *s1, char *s2);
char	**dup_array(char **array);
void	free_array(char **array);
void	free_list(t_input **input);
int		ft_array_size(char **array);
int		ft_echo(char *args);
int		ft_env(char **envp);
int		ft_export(char ***envp, char *string);
char	**ft_append_string_to_array(char **array, char *string);
int		ft_pwd(void);
int		ft_unset(char ***envp, char *string);
int		execute(int *types, char **parsed, char ***envp);
void	ft_exit(char **array, t_execute *exec);
char	*ft_get_env(char **envp, char *string);
int		ft_cd(char *command, char ***envp);
void	print_list(t_input **input);
void	print_cmds(char **s, int *type);
char	**ft_get_commands(t_execute *new, char **parsed);
char	*ft_check_command_and_get_path(char *command, char **envp);
void	ft_free_array(char **array);
char	**ft_special_split(char const *s, char c);
char	**ft_get_command_arg_array(char *command);
void	ft_remove(char *start, char *end);
void	ft_close_fds(t_execute *exec, int current_child);
void	ft_close_all_fds(t_execute *exec);
int		ft_print_command_error(char **parsed, int error_code, int i);
int		ft_init_struct(t_execute *new, int *types, char **parsed, char ***envp);
void	ft_free_data(t_execute *exec);
int		ft_forking(t_execute *exec);
int		ft_child(int i, t_execute *exec);
int		ft_parent(t_execute *exec);
char	*ft_remove_slash(char *deleted);
int		ft_strchr_count(const char *string, char c);
int		ft_init(t_execute *exec, int *types, char **parsed, char ***envp);
int		ft_free_end(int ret, char **array, t_execute *exec);
int		*ft_get_types_commands(t_execute *new);

#endif