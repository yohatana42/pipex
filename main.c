/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 17:11:24 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/23 17:15:01 by yohatana         ###   ########.fr       */
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
		validate_args(argv, env_path);
		data = create_pipex_data_struct(argc);
		if (!data)
			error_pipex(data);
		data_set_to_struct(argc, argv, data, env_path);
		set_fds(argc, argv, data, &fds);
		if (pipe(fds.pipe) < 0)
			error_pipex(data);
		make_process(data, fds);
		exit_status = WEXITSTATUS(data->proc[1]->status);
		end_exec(data, fds);
		return (exit_status);
	}
	else
		exit_error("the number of pipex arguments is 4");
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

void	end_exec(t_pipex_data *data, t_fds fds)
{
	close(fds.in_file);
	close(fds.out_file);
	free_pipex_data(data);
}
