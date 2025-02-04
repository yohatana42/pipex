/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:51:03 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/04 20:24:01 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*exist_cmd(char *cmd, char **env_path);
static char	*option_trim(char *cmd);

void	exec(char **argv, char **env_path)
{
	char	*cmd1;
	// char	*cmd2;

	// コマンドの存在チェック
	cmd1 = exist_cmd(argv[2], env_path);
	printf("cmd1: %s\n", cmd1);
	if (cmd1 == NULL)
	{
		free_env_path(env_path);
		perror("this is not command");
	}
	char	**cmd1_args;
	cmd1_args = NULL;
	// fdを変更する
	execve(cmd1, cmd1_args, NULL);
}

static char	*exist_cmd(char *cmd, char **env_path)
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
