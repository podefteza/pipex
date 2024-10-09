/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:20:21 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/09 14:22:30 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_command(char *cmd, char **envp)
{
	char	*path;
	char	*full_path;
	int		i;
	int		j;
	char	dir[1024];

	path = NULL;

	full_path = malloc(1024);
	if (!full_path)
		return (NULL);
	// Find PATH in envp using while loop
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = envp[i] + 5; // Skip "PATH="
			break ;
		}
		i++;
	}
	if (path == NULL)
	{
		free(full_path);
		return (NULL);
	}
	j = 0;
	while (*path)
	{
		if (*path == ':')
		{
			dir[j] = '\0'; // Terminate the current directory string
			// Build the full path
			ft_strlcpy(full_path, dir, 1024); // Copy directory to full_path
			ft_strlcat(full_path, "/", 1024); // Append '/'
			ft_strlcat(full_path, cmd, 1024); // Append command
			// Print the full path being tried
			//printf("Trying path: %s\n", full_path);
			// Check if the command is executable
			if (access(full_path, X_OK) == 0)
				return (full_path); // Found the executable
			// Reset the directory buffer index for the next directory
			j = 0;
		}
		else
			dir[j++] = *path; // Store the character in the directory buffer
		path++;
	}
	// Handle the last directory after the loop
	dir[j] = '\0';                    // Terminate the last directory string
	ft_strlcpy(full_path, dir, 1024); // Copy last directory to full_path
	ft_strlcat(full_path, "/", 1024); // Append '/'
	ft_strlcat(full_path, cmd, 1024); // Append command
	if (access(full_path, X_OK) == 0)
		return (full_path); // Found the executable
	free(full_path);
	return (NULL); // Command not found
}
