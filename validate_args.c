/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:41:45 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/22 17:53:26 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

static int	validate_infile(char *infile);
static int	validate_outfile(char *outfile);

int	validate_args(char **argv)
{
	int	err_flg;

	err_flg = 0;
	if (validate_infile(argv[1]))
	{
		err_flg = 1;
		write(2, "bash: ", 6);
		perror(argv[1]);
	}
	if (validate_outfile(argv[4]))
	{
		err_flg = 1;
		write(2, "bash: ", 6);
		perror(argv[4]);
	}
	if (err_flg)
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
	int	fd;

	exist_flg = access(outfile, F_OK);
	if (exist_flg < 0)
	{
		fd = open(outfile, O_CREAT, PLIVILEGE);
		if (fd < 0)
			return (1);
	}
	can_write_flg = access(outfile, W_OK);
	if (can_write_flg)
		return (1);
	return (0);
}
