/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:18:35 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/03 19:18:03 by dnebatz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>		//open
# include <sys/wait.h>	//wait
# include <stdio.h>
# include <string.h>	//strerror
# include "../inc/minishell.h"

typedef struct s_execute {
	char	*input;
	int		append;
	char	*output;
	char	*limiter;
	int		count_commands;
	int		count_builtins;
	int		count_children;
	int		*id;
	int		count_pipes;
	int		**pipe_fd;
	int		error;
	char	**commands;
	char	**envp;
}	t_execute;

char	*ft_check_command_and_get_path(char *command, char **envp);
void	ft_free_array(char **array);
char	**ft_special_split(char const *s, char c);
char	**ft_get_command_arg_array(char *command);
void	ft_remove(char *start, char *end);
void	ft_close_fds(t_execute *exec, int current_child);
void	ft_close_all_fds(t_execute *exec);
int		ft_print_command_error(char **parsed, int error_code, int i);
int		ft_init_struct(t_execute *new, int *types, char **parsed, char **envp);
void	ft_free_data(t_execute *exec);
int		ft_forking(t_execute *exec);
int		ft_child(int i, t_execute *exec);
int		ft_parent(t_execute *exec);
char	*ft_remove_slash(char *deleted);
int		ft_strchr_count(const char *string, char c);
int		ft_init(t_execute *exec, int *types, char **parsed, char **envp);

#endif