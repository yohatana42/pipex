/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 22:51:03 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/23 15:19:45 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*create_cmd_path(t_proc *proc, t_pipex_data *data);
static char	*option_trim(char *cmd);
static char	**create_cmd_args(t_pipex_data *data, int num);
static void	change_fds(t_pipex_data *data, t_fds *fds, int num);

void	exec(t_pipex_data *data, int num, t_fds *fds)
{
	char	*cmd_path;
	char	**cmd_args;

	cmd_path = create_cmd_path(data->proc[num], data);
	cmd_args = create_cmd_args(data, num);
	change_fds(data, fds, num);
	if (execve(cmd_path, cmd_args, NULL) == -1)
		error_pipex(data);
}

static char	**create_cmd_args(t_pipex_data *data, int num)
{
	char	**cmd_args;

	cmd_args = ft_split(data->proc[num]->cmd, ' ');
	if (!cmd_args)
		error_pipex(data);
	return (cmd_args);
}

static void	change_fds(t_pipex_data *data, t_fds *fds, int num)
{
	int	fd;

	fd = 0;
	if (num == 0)
	{
		close(fds->pipe[0]);
		close(fds->out_file);
		fd = dup2(fds->in_file, STDIN_FILENO);
		close(fds->in_file);
		if (fd < 0)
			error_pipex(data);
		fd = dup2(fds->pipe[1], STDOUT_FILENO);
		close(fds->pipe[1]);
	}
	else if (num == data->cmd_count -1)
	{
		close(fds->in_file);
		close(fds->pipe[1]);
		fd = dup2(fds->pipe[0], STDIN_FILENO);
		close(fds->pipe[0]);
		fd = dup2(fds->out_file, STDOUT_FILENO);
		close(fds->out_file);
	}
}

static char	*create_cmd_path(t_proc *proc, t_pipex_data *data)
{
	int		i;
	char	*cmd_only;
	char	*cmd_path;

	cmd_only = option_trim(proc->cmd);
	if (!cmd_only)
		error_pipex(data);
	i = 0;
	while (data->env_path[i])
	{
		cmd_path = ft_strjoin(data->env_path[i], cmd_only);
		if (!cmd_path)
		{
			free(cmd_only);
			error_pipex(data);
		}
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	free(cmd_only);
	write(2, proc->cmd, ft_strlen(proc->cmd));
	write(2, ": command not found\n", 21);
	exit(1);
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
	if (space_flg == 1)
		cmd_only = ft_substr(cmd, 0, i);
	else
		cmd_only = ft_strdup(cmd);
	return (cmd_only);
}
