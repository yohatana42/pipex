/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:16:25 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/08 14:45:19 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

static void	free_path(char **path);

t_proc	**create_struct(int argc)
{
	t_proc	**proc;
	int		process_count;
	int		i;

	process_count = argc - 3;
	proc = (t_proc **)ft_calloc(sizeof(t_proc *), process_count + 1);
	if (!proc)
		return (NULL);
	i = 0;
	while (i < process_count)
	{
		printf("i %d process_count %d\n", i, process_count);
		proc[i] = (t_proc *)ft_calloc(sizeof(t_proc), 1);
		if (!proc[i])
		{
			free_proc(proc);
			return (NULL);
		}
		proc[i]->pid = 0;
		proc[i]->status = 0;
		// commandようの構造体にすべき？
		proc[i]->cmd = NULL;
		proc[i]->cmd_path = NULL;
		proc[i]->cmd_args = NULL;
		i++;
	}
	proc[i] = NULL;
	return (proc);
}

t_pipex_data	*create_pipex_data_struct(int argc, char **argv)
{
	t_pipex_data	*data;
	(void)argv;

	data = (t_pipex_data *)ft_calloc(sizeof(t_pipex_data), 1);
	if (!data)
		return (NULL);
	data->env_path = NULL;
	data->pipe_fd[0] = 0;
	data->pipe_fd[1] = 0;
	data->infile = NULL;
	data->outfile = NULL;
	data->cmd_count = 0;
	data->proc = create_struct(argc);
	return (data);
}

void	free_pipex_data(t_pipex_data *data)
{
	if (!data)
		return ;
	free_proc(data->proc);
	free_path(data->env_path);
	// free(data->infile);
	// free(data->outfile);
	free(data);
}

void	free_proc(t_proc **proc)
{
	int	i;
	int	j;

	if (!proc)
		return ;
	i = 0;
	while (proc[i])
	{
		free(proc[i]->cmd);
		free(proc[i]->cmd_path);
		if (proc[i]->cmd_args)
		{
			j = 0;
			while (proc[i]->cmd_args[j])
			{
				free(proc[i]->cmd_args[j]);
				j++;
			}
		}
		free(proc[i]->cmd_args);
		free(proc[i]);
		i++;
	}
	free(proc);
}

static void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}
