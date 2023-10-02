/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dnebatz <dnebatz@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 10:18:35 by dnebatz           #+#    #+#             */
/*   Updated: 2023/10/02 08:56:12 by dnebatz          ###   ########.fr       */
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
	int		here_doc;
	int		count_children;
	int		*id;
	int		count_pipes;
	int		**pipe_fd;
	int		error;
	int		argc;
	char	**commands;
	char	**envp;
	char	**argv;
}	t_execute;

char	*ft_check_command_and_get_path(char *command, char **envp);
void	ft_free_array(char **array);
char	**ft_special_split(char const *s, char c);
char	**ft_get_command_arg_array(char *command);
void	ft_remove(char *start, char *end);
void	ft_close_fds(t_execute *exec, int current_child);
void	ft_close_all_fds(t_execute *exec);
int		ft_print_command_error(char **argv, int error_code);
int		ft_init_struct(t_execute *new, int argc, char **argv, char **envp);
void	ft_free_data(t_execute *exec);
int		ft_init(t_execute *exec, int argc, char **argv, char **envp);
int		ft_forking(t_execute *exec);
int		ft_child(int i, t_execute *exec);
int		ft_parent(t_execute *exec);
char	*ft_remove_slash(char *deleted);
int		ft_strchr_count(const char *string, char c);
int	execute(int argc, char **argv, char **envp);

#endif