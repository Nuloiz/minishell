/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:15:39 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/16 10:44:40 by dnebatz          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>

# define COMMAND 1
# define FLAGS	2
# define FILE	3
# define ENV_VAR	4
# define PIPE	5
# define REDIRECT 6
# define BUILTIN	 7
# define PARAM	 8

extern int	g_signal;

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
	int		*pipe;
}				t_array;

typedef struct s_command
{
	int		index;
	char	*command;
	char	*input;
	char	*output;
	int		append;
	char	*limiter;
	int		type;
}				t_command;

typedef struct s_quote
{
	char	c;
	int		l_r;
	char	**envp;
}	t_quote;

typedef struct s_execute {
	int			count_only_files;
	int			count_limiter;
	int			count_commands;
	int			count_builtins;
	int			count_children;
	int			*id;
	int			count_pipes;
	int			**pipe_fd;
	int			garbage;
	char		***envp;
	t_command	**token;
}	t_execute;

int			main(int argc, char **argv, char **envp);
int			input_sort(char *line, char ***envp, int l_r);
void		mod_lstadd_back(t_input **lst, t_input *new);
t_input		*mod_lstlast(t_input *lst);
int			input_type(char *s, char **envp);
int			is_env_var(char *s);
int			is_built_in(char *s);
int			is_pipe(char *s);
int			is_red(char s);
int			is_file(char *s);
char		*new_quotes(char *s, t_quote info);
char		*string_vor_quote(char *s, int l_r, char **envp);
char		*get_env_in_quotes(char *s, int *i, t_quote info);
char		*env_var(char *s, char **envp, int l_r);
char		*found_env(char *s, int *i, t_quote info);
char		*string_before_env(char *s, int *i);
char		*str_after_env(char *s, int *i, int l_r, char **envp);
int			sort_array(t_input *input, t_array *array);
int			fill_tmp(t_input **input, t_array array, int *count, char **tmp);
int			nv_after_red(t_input **input, int i);
t_command	**get_commands(t_array **array);
char		*mod_get_env(char **envp, char *string, int l_r);
char		**mod_split(char *s, char c);
char		*string_before_quote(char *s, int *j, int *bool);
char		*mod_strjoin(char *s1, char *s2);
char		*mod_nofree_strjoin(char *s1, char *s2);
char		*mod_nocheck_strjoin(char *s1, char *s2);
char		*modified_strjoin(char *s1, char *s2);
char		*modified_strjoin_join(char *joined, char *s1, char *s2, int i);
char		**dup_array(char **array);
void		free_array(char **array);
void		free_list(t_input **input);
void		free_command(t_command **token, int j);
int			ft_array_size(char **array);
int			ft_echo(char *args);
int			ft_env(char **envp);
int			ft_export(char ***envp, char *string);
char		**ft_append_string_to_array(char **array, char *string);
int			ft_pwd(void);
int			ft_unset(char ***envp, char *string);
int			execute(char ***envp, t_command **token);
void		ft_exit(t_execute *exec, char *args);
char		*ft_get_env(char **envp, char *string);
int			ft_cd(char *command, char ***envp);
void		print_list(t_input **input);
void		print_cmds(char **s, int *type, int *pipe);
void		print_commands(t_command **token);
char		*ft_check_command_and_get_path(char *command, char **envp);
void		ft_free_array(char **array);
char		**ft_special_split(char const *s, char c);
char		**ft_get_command_arg_array(char *command);
void		ft_close_fds(t_execute *exec, int current_child);
void		ft_close_all_fds(t_execute *exec);
int			ft_print_command_error(char *parsed, int error_code);
int			ft_init_struct(t_execute *new, t_command **token, char ***envp);
void		ft_free_data(t_execute *exec);
int			ft_forking(t_execute *exec);
int			ft_child(int i, t_execute *exec);
int			ft_parent(t_execute *exec);
char		*ft_remove_slash(char *deleted);
int			ft_strchr_count(const char *string, char c);
int			ft_init(t_execute *exec, t_command **token, char ***envp);
void		ft_free_end(t_execute *exec);
int			ft_set_redirects(t_execute *exec, int i);
void		write_newline(int pipe, int i, t_execute *exec);
int			execute_command(int i, t_execute *exec);
int			execute_builtin(int i, t_execute *exec);
void		set_output_fd(t_execute *exec, int i, int pipe);
int			get_input_pipe(t_execute *exec, int i);
void		set_sig_handle_prompt(void);
void		set_sig_handle_executer(void);
void		turn_off_ctl_echo(void);
void		free_token(t_command **token);
void		set_sig_handle_ignore(void);
int			ft_here_doc(t_execute *exec);
int			wait_return(t_execute *exec);
void		restore_stfds(int stin_backup, int sout_backup);
void		close_limiter_pipes(t_execute *exec);
int			ft_set_pwd(char ***envp, char *path);
void		find_and_set(char ***envp, char **splitted);
int			get_export_length(char *envp, char *string);
int			check_identifier(char *string);
void		print_unset_id_error(char **splitted, int i);
void		print_cd_error(char **splitted);
void		free_exit(t_execute *exec, char **splitted);

#endif