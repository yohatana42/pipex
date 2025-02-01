/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:11:24 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/01 22:50:45 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

int		validate_args(char **argv);
int		end_exec(void);
char	**get_env_path(char **envp);

int	main(int argc, char **argv, char **envp)
{
	char	**env_path;
	(void)env_path;

	if (argc == 5)
	{
		// 環境変数を分解する done!
		env_path = get_env_path(envp);

		// 引数のチェック
		validate_args(argv);

		// 構造体の作成

		// データの格納（ファイルのread）

		// パイプを作成

		// 子プロセスを作る

		// 子プロセスの実行or親プロセスの待機（pipe()の容量を超えたときに注意）

		// 子プロセスの終了
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

// 終了処理
int	end_exec(void)
{
	// free(buffer)
	// close(fd)
	return (0);
}
