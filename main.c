/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:11:24 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/08 14:44:40 by yohatana         ###   ########.fr       */
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
	・errnoと終了ステータスは別
		errnoはシステムコールのエラーを検知する
*/

int	main(int argc, char **argv, char **envp)
{
	char			**env_path;
	// t_proc			**proc;
	// int				pipe_fd[2];
	t_pipex_data	*data;

	if (argc == 5)
	{

		// 環境変数を分解する done!
		env_path = get_env_path(envp);
		if (!env_path)
			perror("env path can not get");

		// 引数のチェック ファイル名だけならdone
		if (validate_args(argv))
		{
			free_env_path(env_path);
			exit(1);
		}

		// 構造体の作成
		data = create_pipex_data_struct(argc, argv);
		if (!data)
			error_pipex(data);
		data_set_to_struct(argc, argv, data, env_path);

		// パイプを作成
		/*
			失敗時
			yohatana@c6r2s5:~$ ulimit -n 1; ls | cat
			bash: pipe error: Too many open files
			bash: start_pipeline: pgrp pipe: Too many open files
		*/
		if (pipe(data->pipe_fd) < 0)
			error_pipex(data);

		// // 子プロセスを作る
		make_process(data);
		// //=============　ここまでOK　===================

		/*
			プロセスが指定した数つくれてるか
			デバッグ用
		*/
		printf("get_pid %d\n", getpid());

		// 子プロセスの実行or親プロセスの待機（pipe()の容量を超えたときに注意）
		int	i;
		i = 0;
		while (data->proc[i])
		{
			printf("====exec start====\n");
			if (data->proc[i]->pid == 0)
			{
				printf("get_pid %d\n", getpid());
				exec(data, i);
				i++;
			}
			else
			{
				waitpid(data->proc[i]->pid, &data->proc[i]->status, 0);
				break ;
			}
		}

		// 終了処理
		end_exec(data);
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

void	make_process(t_pipex_data *data)
{
	// 子プロセスを作る
	// マンダトリーだけなら決め打ちしてもいいけども
	int	i;

	i = 0;
	while (data->proc[i])
	{
		data->proc[i]->pid = fork();
		if (data->proc[i]->pid < 0)
			error_pipex(data);
		else if (data->proc[i]->pid != 0)
			i++;
		else
			break ;
	}
}

// 終了処理
int	end_exec(t_pipex_data *data)
{
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	free_pipex_data(data);
	return (0);
}

// error_exit()のほうがいいかも　最終的にどうなるかわかるから
void	error_pipex(t_pipex_data *data)
{
	// エラーメッセージを吐くだけのときもあるので分けたほうが楽かも
	// error_message()
	perror(strerror(errno));
	free_pipex_data(data);
	exit (errno);
}

void	data_set_to_struct(int argc, \
						char **argv, \
						t_pipex_data *data, \
						char **env_path)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	while (data->proc[i])
	{
		data->proc[i]->cmd = ft_strdup(argv[j]);
		if (!data->proc[i]->cmd)
		{
			error_pipex(data);
		}
		i++;
		j++;
	}
	data->infile = argv[0];
	data->outfile = argv[argc - 1];
	data->cmd_count = argc - 3;
	data->env_path = env_path;
}
