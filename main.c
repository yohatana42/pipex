/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:11:24 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/06 23:15:16 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"


/*
	2/7やること
	・構造体の作成
	・構造体のフリー
	・fork()のラッパー関数
	・エラー用の関数の作成
	・↑bashとの挙動の差を確認
*/

int	main(int argc, char **argv, char **envp)
{
	char	**env_path;
	int		pipe_fd[2];
	int		new_pid_1;
	int		new_pid_2;
	int		status_1;
	int		status_2;

	status_1 = 0;
	status_2 = 0;

	if (argc == 5)
	{
		// 構造体の作成
		// cmd = create_struct();

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


		// 引数のチェック ファイル名だけならdone
		validate_args(argv);

		// パイプを作成
		if (pipe(pipe_fd) != 0)
			perror("pipe failed");
		printf("pipe_fd[0] %d\n", pipe_fd[0]);
		printf("pipe_fd[1] %d\n", pipe_fd[1]);

		// 子プロセスを作る
		new_pid_1 = fork();
		if (new_pid_1 < 0)
			error_pipex();
		else if (new_pid_1 != 0)
		{
			new_pid_2 = fork();
			if (new_pid_2 < 0)
				error_pipex();
		}

		// 子プロセスのpidを構造体にセット

		// 子プロセスの実行or親プロセスの待機（pipe()の容量を超えたときに注意）
		if (new_pid_1 == 0 || new_pid_2 == 0)
		{
			printf("im child pid:%d\n", getpid());
		// ここで環境パスとかやる
			exec(argv, env_path, new_pid_1, new_pid_2, pipe_fd);
		}
		else
		{
			printf("im parent\n");
			waitpid(new_pid_1, &status_1, 0);
			waitpid(new_pid_2, &status_2, 0);
			printf("status_1 %d status_2 %d\n", status_1, status_2);
		}
		// 終了処理
		end_exec(env_path, pipe_fd);
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
int	end_exec(char **env_path, int *pipe_fd)
{
	// 構造体のfree
	free_env_path(env_path);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
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

void	error_pipex(void)
{
	// strerror(errno);
	// perror(strerror(errno));
	exit (errno);
}
