/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:57:18 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/24 09:31:01 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	char	***commands;
	int		pipe_fds[2];
	int		in_out_fds[2];
	char	*cmd2_path;

	if (argc != 5)
		exit_error();
	in_out_fds[0] = infile_check(argv[1]);
	in_out_fds[1] = outfile_check(argv[4]);
	commands = cmds(argv);
	if (!commands)
		return (1);
	cmd2_path = find_command(commands[1][0], envp);
	if (!cmd2_path)
		cmd2_not_found(cmd2_path, commands, envp);
	free(cmd2_path);
	if (pipe(pipe_fds) == -1)
	{
		free_cmds(commands);
		exit_error();
	}
	fork_processes(in_out_fds, pipe_fds, commands, envp);
	close_fds(in_out_fds[0], in_out_fds[1]);
	free_cmds(commands);
	return (0);
}
