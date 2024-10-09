/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:57:18 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/09 15:58:52 by carlos-j         ###   ########.fr       */
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

// TODO: verify if possible to merge the first two functions

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

int	check_file(char *file, int is_input)
{
	int	fd;

	fd = file_check(file, is_input);
	if (fd == -1)
		return (-1);
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

void	exec_cmd(char **cmd_args, char **envp)
{
	char	*command_path;

	command_path = find_command(cmd_args[0], envp);
	if (command_path)
	{
		execve(command_path, cmd_args, envp);
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		//perror("Command not found");
		//perror(cmd_args[0]);
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(cmd_args[0], 2);
		ft_putstr_fd("\n", 2);
		exit(EXIT_FAILURE);
		// instead of this, exit this function and create a function to generate the error "Command 'abc' not found."
	}
}

void	fork_and_execute(int *fds, int *pipefd, char ***commands, char **envp)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(fds[0], STDIN_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_cmd(commands[0], envp);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		dup2(fds[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exec_cmd(commands[1], envp);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	***commands;
	int		pipefd[2];
	int		fds[2];

	if (argc != 5)
		exit_error();
	fds[0] = check_file(argv[1], 1);
	fds[1] = check_file(argv[4], 0);
	if (fds[0] == -1 && fds[1] == -1)
		return (1);
	commands = cmds(argv);
	if (pipe(pipefd) == -1)
		exit_error();
	fork_and_execute(fds, pipefd, commands, envp);
	free_cmds(commands);
	close(fds[0]);
	close(fds[1]);
	return (0);
}


/*
create a script to check if the behavior of the pipex is the same as the terminal
output the result of the terminal and the result of the pipex and the result of what was writen into the outfile in the original pipe in the shell vs my pipex
i already have the files in the directory:
---------- 1 carlos-j 2024_porto       0 Sep 27 14:16 in_not_ok.txt
-rw-r--r-- 1 carlos-j 2024_porto      36 Oct  9 10:11 in_ok.txt
---------- 1 carlos-j 2024_porto       0 Sep 27 14:16 out_not_ok.txt
-rw-r--r-- 1 carlos-j 2024_porto    1026 Oct  9 15:39 out_ok.txt


try tests for the following situations:

this infile has no permitions
< in_not_ok.txt cat | ls > out_ok.txt

this outfile has no permitions
< in_ok.txt cat | ls > out_not_ok.txt

both infile and outfile are ok but the cmd1 does not exist
< in_ok.txt abc | ls > out_ok.txt

both infile and outfile are ok but the cmd2 does not exist
< in_ok.txt cat | 123 > out_ok.txt

cmd1 and cmd2 do not exist
< in_ok.txt abc | 123 > out_ok.txt

infile does not exist
< new.txt cat | ls -l > out_ok.txt

outfile does not exist
< int_ok.txt cat | ls -l > new_out.txt

other tests... a mix of existing/non existing input/output files and permissions/no permissions files and existing/non-existing cmds


*/
