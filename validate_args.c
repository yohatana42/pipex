/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:41:45 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/03 22:51:54 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

// static char	*exist_cmd(char *cmd, char **env_path);
// static char	*option_trim(char *cmd);
static int	validate_infile(char *infile);
static int	validate_outfile(char *outfile);

// int	validate_args(char **argv, char **env_path)
int	validate_args(char **argv)
{
	// char	*cmd1;
	// char	*cmd2;

	// コマンドの存在チェック
	// cmd1 = exist_cmd(argv[2], env_path);
	// printf("cmd1: %s\n", cmd1);
	// if (cmd1 == NULL)
	// {
	// 	free_env_path(env_path);
	// 	perror("this is not command");
	// }

// 一回実行すべき
	// 1.ファイルの権限をチェックする
	// 2.execveが走る
	// 3.execveの
	// コマンドの引数としての妥当性はexecveのときに確認されるべき



	if (validate_infile(argv[1]))
	{
		perror("bash :infile");
	}
	if (validate_outfile(argv[4]))
	{
		perror("bash :outfile");
	}

	return (0);
}

static int	validate_infile(char *infile)
{
	int	exist_flg;
	int	can_read_flg;

	exist_flg = access(infile, F_OK);
	can_read_flg = access(infile, R_OK);
	if (exist_flg || can_read_flg)
		return (1);
	return (0);
}

static int	validate_outfile(char *outfile)
{
	int	exist_flg;
	int	can_write_flg;
	int	fd;

	exist_flg = access(outfile, F_OK);
	printf("exist_flg %d\n", exist_flg);
	if (exist_flg < 0)
	{
		printf("outfile :%s\n", outfile);
		fd = open(outfile, O_CREAT, 00777);
		printf("fd %d\n", fd);
		if (fd < 0)
			return (1);
	}
	can_write_flg = access(outfile, W_OK);
	if (can_write_flg)
		return (1);
	return (0);
}
