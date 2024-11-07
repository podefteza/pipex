/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:20:21 by carlos-j          #+#    #+#             */
/*   Updated: 2024/11/07 09:45:28 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*cmd_is_path(char *cmd)
{
	char	*full_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
		{
			full_path = malloc(ft_strlen(cmd) + 1);
			if (full_path)
				ft_strlcpy(full_path, cmd, ft_strlen(cmd) + 1);
			return (full_path);
		}
		return (NULL);
	}
	return (NULL);
}

char	*build_path(char *dir, char *cmd)
{
	char	*full_path;

	full_path = malloc(ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (!full_path)
		return (NULL);
	ft_strlcpy(full_path, dir, ft_strlen(dir) + 1);
	ft_strlcat(full_path, "/", ft_strlen(dir) + 2);
	ft_strlcat(full_path, cmd, ft_strlen(dir) + ft_strlen(cmd) + 2);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*get_path_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*search_in_path(char *path, char *cmd)
{
	char	dir[1024];
	int		j;
	char	*full_path;

	j = 0;
	while (*path)
	{
		if (*path == ':')
		{
			dir[j] = '\0';
			full_path = build_path(dir, cmd);
			if (full_path)
				return (full_path);
			j = 0;
		}
		else
			dir[j++] = *path;
		path++;
	}
	dir[j] = '\0';
	return (build_path(dir, cmd));
}

char	*find_command(char *cmd, char **envp)
{
	char	*path;
	char	*full_path;

	full_path = cmd_is_path(cmd);
	if (full_path)
		return (full_path);
	path = get_path_from_env(envp);
	if (!path)
		return (NULL);
	return (search_in_path(path, cmd));
}
