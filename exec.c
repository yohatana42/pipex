/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:51:03 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/08 14:58:55 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static void	create_cmd_path(t_proc *proc, char **env_path);
static void	create_cmd_path(t_proc *proc, t_pipex_data *data);
static char	*option_trim(char *cmd);
static void	create_cmd_args(t_pipex_data *data, \
							int num, \
							int in_file_fd, \
							int out_file_fd);

void	exec(t_pipex_data *data, int num)
{

	(void)num;

	// 何番目のプロセスかわからないと

	// char	*cmd1;
	// char	*cmd2;
	int		in_file_fd = 0;
	int		out_file_fd = 0;

	// コマンドのフルパスを作る
	create_cmd_path(data->proc[num], data);
	printf("proc->cmd_path %s\n", data->proc[num]->cmd_path);

// あとここだけ！！！！！！！！
	// fdを変更する(pidによって出力先を変える)
	if (num == 0)
	{
		in_file_fd = open(data->infile, O_RDONLY);
		close(STD_IN);
		close(data->pipe_fd[IN]);
		dup2(in_file_fd, STD_IN);
		close(STD_OUT);
		dup2(data->pipe_fd[OUT], STD_OUT);
	}
	else if (num == data->cmd_count)
	{
		// read(pipe_fd[IN], , 100);
		close(STD_IN);
		close(data->pipe_fd[OUT]);
		dup2(data->pipe_fd[IN], STD_IN);
		out_file_fd = open(data->outfile, O_WRONLY);
		close(STD_OUT);
		dup2(out_file_fd, STD_OUT);
		// 最後のコマンドはstdoutに出力する
	}

	printf("in %d out %d\n", in_file_fd, out_file_fd);

	// コマンドの引数を作る
	create_cmd_args(data, num, in_file_fd, out_file_fd);

	execve(data->proc[num]->cmd_path, data->proc[num]->cmd_args, NULL);
}

static void	create_cmd_args(t_pipex_data *data, \
							int num, \
							int in_file_fd, \
							int out_file_fd)
{
	(void)in_file_fd;
	(void)out_file_fd;
	char	**cmd_args;

	// cmd
	printf("proc->cmd %s\n", data->proc[num]->cmd);
	cmd_args = ft_split(data->proc[num]->cmd, ' ');
	if (!cmd_args)
		error_pipex(data);
	data->proc[num]->cmd_args = cmd_args;
}

static void	create_cmd_path(t_proc *proc, t_pipex_data *data)
{
	int		i;
	char	*temp;
	char	*cmd_path;

	temp = option_trim(proc->cmd);
	if (!temp)
		error_pipex(data);
	i = 0;
	while (data->env_path[i])
	{
		cmd_path = ft_strjoin(data->env_path[i], temp);
		if (!cmd_path)
		{
			free(temp);
			error_pipex(data);
		}
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
		{
			proc->cmd_path = cmd_path;
			break ;
		}
		free(cmd_path);
		i++;
	}
	free(temp);
}

static char	*option_trim(char *cmd)
{
	char	*cmd_only;
	int		i;
	int		space_flg;

	i = 0;
	space_flg = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
		{
			space_flg = 1;
			break ;
		}
		i++;
	}
	printf("space_flg %d\n", space_flg);
	if (space_flg == 1)
		cmd_only = ft_substr(cmd, 0, i);
	else
		cmd_only = ft_strdup(cmd);
	return (cmd_only);
}
