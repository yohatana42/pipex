/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:11:14 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/23 17:11:37 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	make_process(t_pipex_data *data, t_fds fds)
{
	int	pid1;
	int	pid2;

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
