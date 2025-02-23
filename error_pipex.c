/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 17:11:52 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/23 17:12:21 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

void	error_pipex(t_pipex_data *data)
{
	perror("");
	free_pipex_data(data);
	exit (1);
}

void	exit_error(char *str)
{
	perror(str);
	exit(1);
}
