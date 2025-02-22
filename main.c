/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:11:24 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/22 20:29:58 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

// TODO
// exit status
// error message

int	main(int argc, char **argv, char **envp)
{
	char			**env_path;
	t_pipex_data	*data;
	t_fds			fds;
	int				exit_status;

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
		data = create_pipex_data_struct(argc);
		if (!data)
			error_pipex(data);
		data_set_to_struct(argc, argv, data, env_path);

		// fdの設定
		fds.in_file = open(argv[1], O_RDONLY);
		if (fds.in_file < 0)
			error_pipex(data);
		fds.out_file = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, PLIVILEGE);
		if (fds.out_file < 0)
			error_pipex(data);
		// パイプを作成
		if (pipe(fds.pipe) < 0)
			error_pipex(data);

		// 子プロセスを作る
		make_process(data, fds);

		exit_status = WEXITSTATUS(data->proc[1]->status);

		// 終了処理
		end_exec(data);
		close_fds(fds);
		// freeした後にdataを参照しているからinvalid readしていた！
		// return (WEXITSTATUS(data->proc[1]->status));
		return (exit_status);
	}
	else
		perror("the number of pipex arguments is 4");
	return (0);
}

void	close_fds(t_fds fds)
{
	close(fds.in_file);
	close(fds.out_file);
}

// unlink()はヒアドク>>の容量を超えたときに使う（ディフェンス次第だけど軽いのでやったほうがいいかも）
// ｔｍｐファイルを吐き出してそれを読み込んで、ファイルそのものを消す
// ヒアドクフラグみたいなので管理して最後にunlinkするとか……

// pipe()の容量を超える文字列（255*300↑）のときにwait()のタイミングに注意

// close()とかシスコールのエラーハンドリングをやるべき？

// シスコールの終了ステータスはそのまま出力するヒトもいる
// ただしstrerror()でエラー文はそのまま使ったほうがいい（command not found以外）

// close(0)のあとに再度stdinを開けるか


// 本当に悲しいことだけどこれが一番正しく動いている
void	make_process(t_pipex_data *data, t_fds fds)
{
	int	i;
	int	pid1;
	int	pid2;
	(void)fds;

	i = 0;
	pid1 = 0;
	pid2 = 0;
	pid1 = fork();
	if (pid1 < 0)
		error_pipex(data);
	else if (pid1 != 0)
	{
		pid2 = fork();
		if (pid2 < 0)
			error_pipex(data);
	}
	data->proc[0]->pid = pid1;
	data->proc[1]->pid = pid2;

	// 親のpipefdは閉じる
	if (pid1 != 0 && pid2 != 0)
	{
		close(fds.pipe[0]);
		close(fds.pipe[1]);
	}
	// execveしたら子プロセスは死ぬ
	if (pid1 == 0)
		exec(data, 0, &fds);
	else if (pid2 == 0)
		exec(data, 1, &fds);
	// waitの位置確認
	waitpid(pid2, &data->proc[1]->status, 0);
	waitpid(pid1, &data->proc[0]->status, 0);
}

// 一度に存在する子プロセスは常に一つになるようにする　ー＞うそ
// すべての子プロセスのexecve()が始まろうが終わろうがwait()する
	// 途中の子プロセスに膨大な処理時間が経過しても問題ないようにする
// 子プロセスが死ぬことでアクセスできないfdが存在しないように注意
// void	make_process(t_pipex_data *data, t_fds fds)
// {
// 	int	i;
// 	int	pid;
// 	int	last_pid;

// 	i = 0;
// 	while (i < data->cmd_count)
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 			error_pipex(data);
// 		if (pid == 0)
// 			exec(data, i);
// 		else
// 		{
// 			// 親はパイプのfdの入口を閉じる
// 			close(fds.pipe[i]);
// 		}
// 		if (i == data->cmd_count - 1)
// 			last_pid = pid;
// 		i++;
// 	}
// 	// pipe_fdをcloseで閉じる（子プロセスが入力待ち続けてしまうので）
// 	waitpid(last_pid, &data->proc[1]->status, 0);
// 	wait(0);
// }

// 終了処理
void	end_exec(t_pipex_data *data)
{
	free_pipex_data(data);
}

// error_exit()のほうがいいかも　最終的にどうなるかわかるから
void	error_pipex(t_pipex_data *data)
{
	int exit_status;

	// エラーメッセージを吐くだけのときもあるので分けたほうが楽かも
	// error_message()
	perror(strerror(errno));
	exit_status = WEXITSTATUS(data->proc[1]->status);
	free_pipex_data(data);
	exit (errno);
}
