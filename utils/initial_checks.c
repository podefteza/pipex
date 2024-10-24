/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:35:15 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/24 09:29:43 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

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

void	cmd1_not_found(char *cmd_name)
{
	ft_putstr_fd("Command not found: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd("\n", 2);
}

void	cmd2_not_found(char *cmd2_path, char ***commands, char **envp)
{
	char	*cmd1;

	cmd1 = find_command(commands[0][0], envp);
	free(cmd2_path);
	if (!cmd1)
		cmd1_not_found(commands[0][0]);
	free(cmd1);
	cmd_not_found(commands[1][0], commands);
}

void	cmd_not_found(char *cmd_name, char ***commands)
{
	int	i;
	int	exit_code;

	i = 0;
	exit_code = 127;
	while (commands[i] != NULL)
	{
		if (ft_strncmp(commands[i][0], "exit", 4) == 0)
		{
			if (commands[i][1] != NULL)
				exit_code = ft_atoi(commands[i][1]);
			free_cmds(commands);
			exit(exit_code);
		}
		i++;
	}
	ft_putstr_fd("Command not found: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd("\n", 2);
	free_cmds(commands);
	exit(127);
}
