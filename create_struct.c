/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:16:25 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/18 14:08:09 by yohatana         ###   ########.fr       */
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
		proc[i] = (t_proc *)ft_calloc(sizeof(t_proc), 1);
		if (!proc[i])
		{
			free_proc(proc, process_count);
			return (NULL);
		}
		proc[i]->pid = 0;
		proc[i]->status = 0;
		proc[i]->cmd = NULL;
		i++;
	}
	proc[i] = NULL;
	printf("i %d\n", i);
	return (proc);
}

// t_pipex_data	*create_pipex_data_struct(int argc, char **argv)
// {
// 	t_pipex_data	*data;
// 	(void)argv;

// 	data = (t_pipex_data *)ft_calloc(sizeof(t_pipex_data), 1);
// 	if (!data)
// 		return (NULL);
// 	data->env_path = NULL;
// 	data->cmd_count = 0;
// 	data->proc = create_struct(argc);
// 	return (data);
// }

t_pipex_data	*create_pipex_data_struct(int argc)
{
	t_pipex_data	*data;

	data = (t_pipex_data *)ft_calloc(sizeof(t_pipex_data), 1);
	if (!data)
		return (NULL);
	data->env_path = NULL;
	data->cmd_count = 0;
	data->proc = create_struct(argc);
	return (data);
}

void	free_pipex_data(t_pipex_data *data)
{
	if (!data)
		return ;
	free_proc(data->proc, data->cmd_count);
	free_path(data->env_path);
	free(data);
}

void	free_proc(t_proc **proc, int process_count)
{
	int	i;

	if (!proc)
		return ;
	i = 0;
	while (i < process_count)
	{
		free(proc[i]->cmd);
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
