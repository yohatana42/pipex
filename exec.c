/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:51:03 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/18 14:17:27 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static void	create_cmd_path(t_proc *proc, t_pipex_data *data);
static char	*create_cmd_path(t_proc *proc, t_pipex_data *data);
static char	*option_trim(char *cmd);
static char	**create_cmd_args(t_pipex_data *data, int num);

// void	exec(t_pipex_data *data, int num)
void	exec(t_pipex_data *data, int num, t_fds fds)
{
	char	*cmd_path;
	char	**cmd_args;

	// コマンドのフルパスを作る
	cmd_path = create_cmd_path(data->proc[num], data);

	/*
	fdを変更する(pidによって出力先を変える)
	*/
	int	fd;
	if (num == 0)
	{
		close(fds.pipe[0]);
		fd = dup2(fds.in_file, STDIN_FILENO);
		fd = dup2(fds.pipe[1], STDOUT_FILENO);
		close(fds.pipe[1]);
	}
	else if (num == data->cmd_count - 1)
	{
		close(fds.pipe[1]);
		fd = dup2(fds.pipe[0], STDIN_FILENO);
		fd = dup2(fds.out_file, STDOUT_FILENO);
		close(fds.pipe[0]);
	}

	// コマンドの引数を作る
	cmd_args = create_cmd_args(data, num);

	dprintf(STDERR_FILENO, "EXECVE rdy\n");
	// 実行
	execve(cmd_path, cmd_args, NULL);
}

static char	**create_cmd_args(t_pipex_data *data, int num)
{
	char	**cmd_args;

	cmd_args = ft_split(data->proc[num]->cmd, ' ');
	if (!cmd_args)
		error_pipex(data);
	return (cmd_args);
}


static char	*create_cmd_path(t_proc *proc, t_pipex_data *data)
{
	int		i;
	char	*cmd_only;
	char	*cmd_path;

	cmd_only = option_trim(proc->cmd);
	if (!cmd_only)
		error_pipex(data);
	i = 0;
	while (data->env_path[i])
	{
		cmd_path = ft_strjoin(data->env_path[i], cmd_only);
		if (!cmd_path)
		{
			free(cmd_only);
			error_pipex(data);
		}
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	free(cmd_only);
	return (NULL);
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
	if (space_flg == 1)
		cmd_only = ft_substr(cmd, 0, i);
	else
		cmd_only = ft_strdup(cmd);
	return (cmd_only);
}
