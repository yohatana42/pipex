/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:50:23 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/18 14:09:14 by yohatana         ###   ########.fr       */
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

typedef struct s_fds
{
	int	in_file;
	int	out_file;
	int	pipe[2];
} t_fds;

// pipe_fdって構造体にすべきか？プロセス-1の数しか出来ないはずなのでこれ単体配列にすべきじゃね？
typedef struct s_proc
{
	int		pid;
	int		status;
	char	*cmd; // 引数でもらったコマンド
	// この辺は子プロセスで使うので親は不要
	// char	*cmd_path; // コマンドの実行パス（存在しない場合は引数でもらった状態のコマンドのみが入る）
	// char	**cmd_args; // コマンドの引数
} t_proc;

typedef struct s_pipex_data
{
	char	**env_path;
	t_proc	**proc;
	// int		pipe_fd[2];
	// char	*infile;
	// char	*outfile;
	// int		infile_fd;
	// int		outfile_fd;
	int		cmd_count;
}	t_pipex_data;

// main
// void	make_process(t_pipex_data *data);
void	make_process(t_pipex_data *data, t_fds fds);

// create_struct
// t_pipex_data	*create_pipex_data_struct(int argc, char **argv, char **env_path);
// t_pipex_data	*create_pipex_data_struct(int argc, char **argv);
t_pipex_data	*create_pipex_data_struct(int argc);
t_proc	**create_struct(int argc);
void	free_proc(t_proc **proc, int cmd_count);
void	free_pipex_data(t_pipex_data *data);

void	free_env_path(char **env_path);

// exec
// void	exec(char **env_path, t_proc *proc, int *pipe_fd, int num);
// void	exec(t_pipex_data *data, int num);
void	exec(t_pipex_data *data, int num, t_fds fds);

// int		end_exec(char **env_path, t_proc **proc, int *pipe_fd);
void	end_exec(t_pipex_data *data);
void	close_fds(t_fds fds);

// error
// void	error_pipex(char **env_path, t_proc **proc);
void	error_pipex(t_pipex_data *data);

// validate
int		validate_args(char **argv);


// get_env_path
char	**get_env_path(char **envp);

// void	cmd_set_to_struct(char **argv, t_proc **proc);
// void	data_set_to_struct(char **argv, t_pipex_data *data, char **env_path);
void	data_set_to_struct(int argc, \
						char **argv, \
						t_pipex_data *data, \
						char **env_path);
