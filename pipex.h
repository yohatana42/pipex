/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:50:23 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/04 17:53:04 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "./libft/libft.h"
#include "./printf/libftprintf.h"

#define IN 0
#define OUT 1

typedef struct s_cmd
{
	char	*cmd1;
	char	*cmd2;
} t_cmd;

typedef struct s_file
{
	char	*cmd1;
	char	*cmd2;
} t_file;

void	free_env_path(char **env_path);
void	exec(char **argv, char **env_path);
