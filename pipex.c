/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:57:18 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/12 14:28:42 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*allow functions: open, close, read, write, malloc, free, perror, strerror,
access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid*/

// original: $> < file1 cmd1 | cmd2 > file2
// my implementation: ./pipex file1 cmd1 cmd2 file2

void	exec_cmd(char **cmd_args, char **envp, char ***commands)
{
	char	*command_path;

	command_path = find_command(cmd_args[0], envp);
	if (command_path)
	{
		execve(command_path, cmd_args, envp);
		perror("Error\n");
		free_cmds(commands);
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd("\n", 2);
		free_cmds(commands);
		exit(127);
	}
}

void	execute_processes(char **cmd, char **envp, char ***commands,
		int *pipe_fds)
{
	close_fds(pipe_fds[0], pipe_fds[1]);
	exec_cmd(cmd, envp, commands);
	exit(EXIT_FAILURE);
}

void	fork_processes(int *in_out_fds, int *pipe_fds, char ***commands,
		char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(in_out_fds[0], STDIN_FILENO);
		dup2(pipe_fds[1], STDOUT_FILENO);
		execute_processes(commands[0], envp, commands, pipe_fds);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipe_fds[0], STDIN_FILENO);
		dup2(in_out_fds[1], STDOUT_FILENO);
		execute_processes(commands[1], envp, commands, pipe_fds);
	}
	close_fds(pipe_fds[0], pipe_fds[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	free_cmds(commands);
	if (status2 != 0)
		exit(status2 >> 8);
}

int	main(int argc, char **argv, char **envp)
{
	char	***commands;
	int		pipe_fds[2];
	int		in_out_fds[2];

	if (argc != 5)
		exit_error();
	in_out_fds[0] = file_check(argv[1], 1);
	in_out_fds[1] = file_check(argv[4], 0);
	if (in_out_fds[0] == -1 || in_out_fds[1] == -1)
		return (1);
	commands = cmds(argv);
	if (!commands)
	{
		close_fds(in_out_fds[0], in_out_fds[1]);
		return (1);
	}
	if (pipe(pipe_fds) == -1)
	{
		free_cmds(commands);
		exit_error();
	}
	fork_processes(in_out_fds, pipe_fds, commands, envp);
	close_fds(in_out_fds[0], in_out_fds[1]);
	return (0);
}

/*
# 04: The program does not crash with no parameters                         [OK]
# 05: The program does not crash with one parameter                         [OK]
# 06: The program does not crash with two parameters                        [OK]
# 07: The program does not crash with three parameters                      [OK]
# 09: The program handles infile's open error                               [OK]
# 10: The output when infile's open error occur is correct                  [OK]
*/
