/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_set_to_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 18:19:17 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/17 18:33:50 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	data_set_to_struct(int argc, \
						char **argv, \
						t_pipex_data *data, \
						char **env_path)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	while (data->proc[i])
	{
		data->proc[i]->cmd = ft_strdup(argv[j]);
		if (!data->proc[i]->cmd)
		{
			error_pipex(data);
		}
		i++;
		j++;
	}
	data->cmd_count = argc - 3;
	data->env_path = env_path;
}
