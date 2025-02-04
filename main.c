/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:11:24 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/04 20:21:28 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

// int		validate_args(char **argv, char **env_path);
int		validate_args(char **argv);
int		end_exec(void);
char	**get_env_path(char **envp);

// 実行可能なコマンドのパス
// 環境変数パス（二重配列）

int	main(int argc, char **argv, char **envp)
{
	char	**env_path;
	int		pipe_fd[2];
	int		new_pid_1;
	int		new_pid_2;
	int		status_1;
	int		status_2;
	(void)argv;
	(void)env_path;
	// t_cmd	*cmd;

	status_1 = 0;
	status_2 = 0;

	if (argc == 5)
	{
		// 環境変数を分解する done!
		env_path = get_env_path(envp);
		if (!env_path)
			perror("env path can not get");

		// /* デバッグ用 */
		// int i = 0;
		// while (env_path[i])
		// {
		// 	printf("env_path[i] %s\n", env_path[i]);
		// 	i++;
		// }

		// 構造体の作成
		// cmd = create_struct();

		// 引数のチェック ファイル名だけならdone
		validate_args(argv);
		// データの格納（ファイルのread）

		// パイプを作成
		if (pipe(pipe_fd) != 0)
			perror("pipe failed");
		printf("pipe_fd[0] %d\n", pipe_fd[0]);
		printf("pipe_fd[1] %d\n", pipe_fd[1]);

		// 子プロセスを作る
		new_pid_1 = fork();
		if (new_pid_1 != 0)
			new_pid_2 = fork();
		if (new_pid_1 == 0 || new_pid_2 == 0)
		{
			printf("im child pid:%d\n", getpid());
			exec(argv, env_path);
		}
		else
		{
			printf("im parent\n");
			waitpid(new_pid_1, &status_1, 0);
			waitpid(new_pid_2, &status_2, 0);
			printf("status_1 %d status_2 %d\n", status_1, status_2);
		}

		// 子プロセスの実行or親プロセスの待機（pipe()の容量を超えたときに注意）
		// ここで環境パスとかやる

		// 子プロセスの終了

		// 終了処理
		free_env_path(env_path);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		end_exec();
	}
	else
		perror("the number of pipex arguments is 4");
	return (0);
}

// unlink()はヒアドク>>の容量を超えたときに使う（ディフェンス次第だけど軽いのでやったほうがいいかも）
// ｔｍｐファイルを吐き出してそれを読み込んで、ファイルそのものを消す
// ヒアドクフラグみたいなので管理して最後にunlinkするとか……

// pipe()の容量を超える文字列（255*300↑）のときにwait()のタイミングに注意

// close()とかシスコールのエラーハンドリングをやるべき？

// シスコールの終了ステータスはそのまま出力するヒトもいる
// ただしstrerror()でエラー文はそのまま使ったほうがいい（command not found以外）

// close(0)のあとに再度stdinを開けるか

// 終了処理
int	end_exec(void)
{
	// free(buffer)
	// close(fd)
	return (0);
}

// t_cmd	*create_struct(void)
// {
// 	t_cmd	*cmd;

// 	cmd = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
// 	if (!cmd)
// 		return (NULL);
// 	cmd->cmd1 = NULL;
// 	cmd->cmd2 = NULL;
// 	return (cmd);
// }
