/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:50:23 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/23 17:09:17 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>
# include "./libft/libft.h"
# include "./printf/libftprintf.h"

# define IN 0
# define OUT 1
# define STD_IN 0
# define STD_OUT 1
# define ERR_OUT 1
# define PLIVILEGE 00644

typedef struct s_fds
{
	int	in_file;
	int	out_file;
	int	pipe[2];
}	t_fds;

typedef struct s_proc
{
	int		pid;
	int		status;
	char	*cmd;
}	t_proc;

typedef struct s_pipex_data
{
	char	**env_path;
	t_proc	**proc;
	int		cmd_count;
}	t_pipex_data;

// main
void			make_process(t_pipex_data *data, t_fds fds);

// create_struct
t_pipex_data	*create_pipex_data_struct(int argc);
void			free_proc(t_proc **proc, int cmd_count);
void			free_pipex_data(t_pipex_data *data);

void			free_env_path(char **env_path);

// exec
void			exec(t_pipex_data *data, int num, t_fds *fds);
void			end_exec(t_pipex_data *data, t_fds fds);

// error
void			error_pipex(t_pipex_data *data);
void			exit_error(char *str);

// validate
int				validate_args(char **argv, char **env_path);

// get_env_path
char			**get_env_path(char **envp);

// data_set_struct
void			data_set_to_struct(int argc, \
						char **argv, \
						t_pipex_data *data, \
						char **env_path);

#endif
