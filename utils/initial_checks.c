/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:35:15 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/23 13:43:03 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	file_check(char *filename, int is_input)
{
	int	fd;

	if (is_input)
	{
		fd = open(filename, O_RDONLY);
		if (fd == -1)
		{
			perror(filename);
			return (-1);
		}
	}
	else
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1)
		{
			perror(filename);
			exit(EXIT_FAILURE);
		}
	}
	return (fd);
}

char	***initialize_commands(char **argv)
{
	char	***commands;

	commands = (char ***)malloc(3 * sizeof(char **));
	if (!commands)
		return (NULL);
	commands[0] = ft_split(argv[2], ' ');
	commands[1] = ft_split(argv[3], ' ');
	commands[2] = NULL;
	return (commands);
}

void	cmd2_not_found(char *cmd2_path, char ***commands, char **envp)
{
	free(cmd2_path);
	if (!find_command(commands[0][0], envp))
		cmd1_not_found(commands[0][0]);
	cmd_not_found(commands[1][0], commands);
}
