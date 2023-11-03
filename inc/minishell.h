/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 14:15:39 by nschutz           #+#    #+#             */
/*   Updated: 2023/11/03 14:53:17 by dnebatz          ###   ########.fr       */
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

int	g_signal;

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

typedef struct s_boollr
{
	int		bool;
	int		l_r;
}	t_boollr;

typedef struct s_execute {
	int			count_only_files;
	int			count_limiter;
	int			count_commands;
	int			count_builtins;
	int			count_children;
	int			*id;
	int			count_pipes;
	int			**pipe_fd;
	int			error;
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
t_input		*found_quote(t_input *new, char **s, char c);
char		*env_var(char *s, char **envp, int l_r);
int			sort_array(t_input *input, t_array *array);
int			fill_tmp(t_input **input, t_array array, int *count, char **tmp);
int			nv_after_red(t_input **input, int i);
t_command	**get_commands(t_array **array);
char		*mod_get_env(char **envp, char *string, t_boollr *j, char *s);
char		**mod_split(char *s, char c);
void		mod_countsplitting(char *s, int *j, char c);
int			mod_possplit(const char *s, char c);
char		*mod_strjoin(char *s1, char *s2);
char		*mod_nofree_strjoin(char *s1, char *s2);
char		*mod_nocheck_strjoin(char *s1, char *s2);
char		*modified_strjoin(char *s1, char *s2);
char		*modified_strjoin_join(char *joined, char *s1, char *s2, int i);
char		*mod_substr(char const *s, unsigned int start, size_t len);
char		**dup_array(char **array);
void		free_array(char **array);
void		free_list(t_input **input);
void		free_command(t_command **token, int j);
void		free_in_command(t_command **token);
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
char		**ft_get_commands(t_execute *new, char **parsed);
char		*ft_check_command_and_get_path(char *command, char **envp);
void		ft_free_array(char **array);
char		**ft_special_split(char const *s, char c);
char		**ft_get_command_arg_array(char *command);
void		ft_remove(char *start, char *end);
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
// int			*ft_get_types_commands(t_execute *new);
int			ft_set_redirects(t_execute *exec, int i);
void		write_newline(int pipe, int i, t_execute *exec);
int			execute_command(int i, t_execute *exec);
void		execute_builtin(int i, t_execute *exec);
void		set_output_fd(t_execute *exec, int i, int pipe);
int			get_input_pipe(t_execute *exec, int i);
// void		set_sig_handle_prompt(struct sigaction *sa);
// void		set_sig_handle_executer(struct sigaction *sa);
void		set_sig_handle_prompt(void);
void		set_sig_handle_executer(void);
void		turn_off_ctl_echo(void);
void		free_token(t_command **token);
void		set_sig_handle_ignore(void);
int			ft_here_doc(t_execute *exec);
int			wait_return(t_execute *exec, int stin_backup, int sout_backup);
void		restore_stfds(int stin_backup, int sout_backup);

#endif