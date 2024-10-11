/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:57:18 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/11 10:31:41 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*allow functions:
open, close, read, write, malloc, free, perror, strerror, access, dup, dup2,
execve, exit, fork, pipe, unlink, wait, waitpid*/

// original: $> < file1 cmd1 | cmd2 > file2
// my implementation: ./pipex file1 cmd1 cmd2 file2

// main to accept 4 arguments --> handle cases when argc != 5 ??
//		bonus1: handle multiple pipes
// cases where infile/outfile do not exist/don't have permissions??
// 		^no infile: error (no such file or directory: <infile>)
// 		^no outfile: creates it
//		^no permissions: <filename>: Permission denied
// 		^no cmd: error (command not found: <cmd>)

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

char	***cmds(char **argv)
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

void	fork_and_execute(int *fds, int *pipefd, char ***commands, char **envp)
{
	pid_t pid1, pid2;
	int status1, status2;
	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_cmd(commands[0], envp, commands);
		exit(1); // Should not reach here if exec_cmd works correctly
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_cmd(commands[1], envp, commands);
		exit(1); // Should not reach here if exec_cmd works correctly
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	// Clean up commands before exiting
	free_cmds(commands);
	// if (status1 != 0)
	//    exit(status1 >> 8);
	if (status2 != 0)
		exit(status2 >> 8);
}

int	main(int argc, char **argv, char **envp)
{
	char	***commands;
	int		pipefd[2];
	int		fds[2];

	if (argc != 5)
		exit_error();
	fds[0] = file_check(argv[1], 1);
	fds[1] = file_check(argv[4], 0);
	if (fds[0] == -1 || fds[1] == -1)
		return (1);
	commands = cmds(argv);
	if (!commands)
	{
		close(fds[0]);
		close(fds[1]);
		return (1);
	}
	if (pipe(pipefd) == -1)
	{
		free_cmds(commands);
		exit_error();
	}
	fork_and_execute(fds, pipefd, commands, envp);
	close(fds[0]);
	close(fds[1]);
	return (0);
}
