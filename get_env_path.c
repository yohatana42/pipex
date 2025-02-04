/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yohatana <yohatana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 22:29:27 by yohatana          #+#    #+#             */
/*   Updated: 2025/02/03 20:31:18 by yohatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"pipex.h"

static char	**add_slash(char **path);
static void	free_path(char **path);

char	**get_env_path(char **envp)
{
	char	**path;
	char	*temp;
	int		i;
	char	**env_path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	temp = ft_strtrim(envp[i], "PATH=");
	if (!temp)
		return (NULL);
	path = ft_split(temp, ':');
	if (!path)
	{
		free(temp);
		return (NULL);
	}
	env_path = add_slash(path);
	if (!env_path)
		free_path(path);
	free(temp);
	return (env_path);
}

static char	**add_slash(char **path)
{
	int		i;
	char	*post_path;

	i = 0;
	while (path[i])
	{
		post_path = ft_strjoin(path[i], "/");
		if (!post_path)
			return (NULL);
		free(path[i]);
		path[i] = post_path;
		i++;
	}
	return (path);
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

void	free_env_path(char **env_path)
{
	int	i;

	i = 0;
	while (env_path[i])
	{
		free(env_path[i]);
		i++;
	}
	free(env_path);
}
