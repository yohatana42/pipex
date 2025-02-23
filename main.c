/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:11:24 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/23 15:23:53 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

static void	set_fds(int argc, char **argv, t_pipex_data *data, t_fds *fds);

int	main(int argc, char **argv, char **envp)
{
	char			**env_path;
	t_pipex_data	*data;
	t_fds			fds;
	int				exit_status;

	if (argc == 5)
	{
		env_path = get_env_path(envp);
		if (!env_path)
		{
			perror("env path can not get");
			exit(1);
		}
		if (validate_args(argv))
		{
			free_env_path(env_path);
			exit(1);
		}
		data = create_pipex_data_struct(argc);
		if (!data)
			error_pipex(data);
		data_set_to_struct(argc, argv, data, env_path);
		set_fds(argc, argv, data, &fds);
		if (pipe(fds.pipe) < 0)
			error_pipex(data);
		make_process(data, fds);
		exit_status = WEXITSTATUS(data->proc[1]->status);
		end_exec(data);
		close_fds(fds);
		return (exit_status);
	}
	else
		perror("the number of pipex arguments is 4");
	return (1);
}

static void	set_fds(int argc, char **argv, t_pipex_data *data, t_fds *fds)
{
	fds->in_file = open(argv[1], O_RDONLY);
	if (fds->in_file < 0)
		error_pipex(data);
	fds->out_file = open(argv[argc - 1], \
						O_WRONLY | O_TRUNC | O_CREAT, \
						PLIVILEGE);
	if (fds->out_file < 0)
		error_pipex(data);
}

void	close_fds(t_fds fds)
{
	close(fds.in_file);
	close(fds.out_file);
}

void	make_process(t_pipex_data *data, t_fds fds)
{
	int	i;
	int	pid1;
	int	pid2;

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
	if (pid1 != 0 && pid2 != 0)
	{
		close(fds.pipe[0]);
		close(fds.pipe[1]);
	}
	if (pid1 == 0)
		exec(data, 0, &fds);
	else if (pid2 == 0)
		exec(data, 1, &fds);
	waitpid(pid2, &data->proc[1]->status, 0);
	waitpid(pid1, &data->proc[0]->status, 0);
}

void	end_exec(t_pipex_data *data)
{
	free_pipex_data(data);
}

void	error_pipex(t_pipex_data *data)
{
	int	exit_status;

	perror("");
	exit_status = WEXITSTATUS(data->proc[1]->status);
	free_pipex_data(data);
	exit (1);
}
