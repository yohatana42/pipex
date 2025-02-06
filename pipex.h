/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:50:23 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/06 22:58:14 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include "./libft/libft.h"
#include "./printf/libftprintf.h"

#define IN 0
#define OUT 1
#define STD_IN 0
#define STD_OUT 1
#define ERR_OUT 1
#define PLIVILEGE 00644

typedef struct s_cmd
{
	char	*cmd1;
	char	*cmd2;
} t_cmd;

typedef struct s_data
{
	char	**env_path;
	int		pipe_fd[2];
	int		new_pid_1;
	int		new_pid_2;
	int		status_1;
	int		status_2;
} t_data;

void	free_env_path(char **env_path);
// void	exec(char **argv, char **env_path);
// void	exec(char **argv, char **env_path, int new_pid_1, int new_pid_2);
void	exec(char **argv, char **env_path, int new_pid_1, int new_pid_2, int *pipe_fd);
void	error_pipex(void);
int		validate_args(char **argv);
int		end_exec(char **env_path, int *pipe_fd);
char	**get_env_path(char **envp);
void	error_pipex(void);
