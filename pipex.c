/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:57:18 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/16 09:35:26 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	***commands;
	int		pipe_fds[2];
	int		in_out_fds[2];
	char	*cmd_path;

	if (argc != 5)
		exit_error();
	in_out_fds[0] = file_check(argv[1], 1);
	in_out_fds[1] = file_check(argv[4], 0);
	commands = cmds(argv);
	cmd_path = find_command(commands[1][0], envp);
	if (!cmd_path)
		cmd_not_found(commands[1][0], commands);
	free(cmd_path);
	if (!commands)
		return (1);
	if (pipe(pipe_fds) == -1)
	{
		free_cmds(commands);
		exit_error();
	}
	fork_processes(in_out_fds, pipe_fds, commands, envp);
	close_fds(in_out_fds[0], in_out_fds[1]);
	return (0);
}
