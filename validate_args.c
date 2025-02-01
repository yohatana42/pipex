/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:41:45 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/01 23:18:10 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

static int	exist_cmd(char **argv);
static int	validate_infile(char *infile);
static int	validate_outfile(char *outfile);

int	validate_args(char **argv)
{
	// コマンドの存在チェック
	if (exist_cmd(argv))
	{
		perror("this is not command");
		// strerror(eroonum);
	}
	if (validate_infile(argv[1]))
	{
		perror("infile does not exist or does not have authority of infile");
	}
	if (validate_outfile(argv[2]))
	{
		perror("does not have authority of outfile");
	}
	return (0);
}

static int	exist_cmd(char **argv)
{
	char	*cmd1;
	char	*cmd2;
	int		exist_flg;
	int		exist_flg2;

	//todo $PATHに実行ファイルがなければcomannd not foundになる
	cmd1 = ft_strjoin("/bin/", argv[2]);
	cmd2 = ft_strjoin("/bin/", argv[3]);
	exist_flg = access(cmd1, F_OK);
	exist_flg2 = access(cmd2, F_OK);
	free(cmd1);
	free(cmd2);
	if (exist_flg || exist_flg2)
		return (1);
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
	// int	execve_result;

	exist_flg = access(outfile, F_OK);
	if (exist_flg)
	{
		// ない場合は新規作成するフラグを作る
		open(outfile, 0);
		// if (execve_result)
		// {
		// 	perror("make outfile failed");
		// }
	}
	can_write_flg = access(outfile, W_OK);
	if (can_write_flg)
		return (1);
	return (0);
}
