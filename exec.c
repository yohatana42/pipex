/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:51:03 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/06 23:12:45 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*create_cmd_path(char *cmd, char **env_path);
static char	*option_trim(char *cmd);

void	exec(char **argv, char **env_path, int new_pid_1, int new_pid_2, int *pipe_fd)
{
	char	*cmd1;
	char	*cmd2;
	int		in_file_fd;
	int		out_file_fd;

	// コマンドの存在チェック
	cmd1 = create_cmd_path(argv[2], env_path);
	printf("cmd1: %s\n", cmd1);
	if (cmd1 == NULL)
	{
		free_env_path(env_path);
		perror("this is not command");
	}

	cmd2 = create_cmd_path(argv[3], env_path);
	printf("cmd2: %s\n", cmd2);
	if (cmd2 == NULL)
	{
		free_env_path(env_path);
		perror("this is not command");
	}
	// 存在して実行可能じゃなくてもexecveに投げる気がする

/* コマンド情報の配列を作って頭から実行していくのがいいかも
	typedef struct s_command
	{
		char *cmd; // 引数でもらったコマンド（例："wc -l"）
		char *cmd_path; // コマンドの実行パス（存在しない場合は引数でもらった状態のコマンドのみが入る）
		char **cmd_args; // execveの第二引数（例：0 = wc, 1 = -l）
		int	*pipefd[2]; // このプロセスが使うパイプFD
	}	t_command;
*/
	// コマンドの引数を作る
	char	**cmd1_args;
	cmd1_args = NULL;
	char	**cmd2_args;
	cmd2_args = NULL;
	// fdを変更する(pidによって出力先を変える)
	if (new_pid_1 == 0)
	{
		in_file_fd = open(argv[1], O_RDONLY);
		close(STD_IN);
		dup2(in_file_fd, STD_IN);
		close(pipe_fd[IN]);
		dup2(pipe_fd[OUT], STD_OUT);
		execve(cmd1, cmd1_args, NULL);
	}
	if (new_pid_2 == 0)
	{
		close(pipe_fd[OUT]);
		// パイプの読み込みってreadでいいのか？
		// read(pipe_fd[IN], , 100);
		dup2(pipe_fd[IN], STD_IN);
		out_file_fd = open(argv[4], O_WRONLY);
		dup2(out_file_fd, STD_OUT);
		execve(cmd2, cmd2_args, NULL);
	}
}

static char **create_cmd_args(char *cmd_path, char *argv, int in_fd)
{
	char **cmd_args;

	cmd_args = NULL;

	return (cmd_args);
}

static char	*create_cmd_path(char *cmd, char **env_path)
{
	int		i;
	char	*temp;
	char	*cmd_path;

	temp = option_trim(cmd);
	printf("option_trim %s\n", temp);
	if (!temp)
		return (NULL);
	i = 0;
	while (env_path[i])
	{
		cmd_path = ft_strjoin(env_path[i], temp);
		if (!cmd_path)
		{
			free(temp);
			return (NULL);
		}
		printf("cmd_path %s\n", cmd_path);
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
		{
			free(temp);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free(temp);
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
	printf("space_flg %d\n", space_flg);
	if (space_flg == 1)
		cmd_only = ft_substr(cmd, 0, i);
	else
		cmd_only = ft_strdup(cmd);
	return (cmd_only);
}
