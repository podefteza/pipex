/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:57:18 by carlos-j          #+#    #+#             */
/*   Updated: 2024/09/27 17:07:12 by carlos-j         ###   ########.fr       */
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
			return (-1);
		}
	}
	return (fd);
}

int	exit_error(void)
{
	ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	exit(0);
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

void	free_cmds(char ***commands)
{
	int	i;
	int	j;

	i = 0;
	while (commands[i])
	{
		j = 0;
		while (commands[i][j])
		{
			free(commands[i][j]);
			j++;
		}
		free(commands[i]);
		i++;
	}
	free(commands);
}

int	main(int argc, char **argv)
{
	int		infile_fd;
	int		outfile_fd;
	char	***commands;
	int		i;
	int		j;

	if (argc != 5)
		exit_error();
	infile_fd = file_check(argv[1], 1);
	if (infile_fd == -1)
		return (1);
	outfile_fd = file_check(argv[4], 0);
	if (outfile_fd == -1)
	{
		close(infile_fd);
		return (1);
	}
	commands = cmds(argv);

	printf("Infile FD: %d\n", infile_fd);
	printf("Outfile FD: %d\n", outfile_fd);

	/*	*/
	// Print the commands (for testing; remove later)
	i = 0;
	while (commands[i])
	{
		j = 0;
		printf("cmd%d: ", i + 1);
		while (commands[i][j])
		{
			printf("|%s|", commands[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}


	// path for execve: create another function "create_path" for this step
	char path1[50] = "/bin/";
	char path2[50] = "/bin/";
	int k = 5;
	int w = 0;
	while (commands[0][0][w])
	{
		path1[k] = commands[0][0][w];
		w++;
		k++;
	}
	path1[k] = '\0';
	k = 5;
	w = 0;
	while (commands[1][0][w])
	{
		path2[k] = commands[1][0][w];
		w++;
		k++;
	}
	path2[k] = '\0';
	printf("path1: |%s|\n", path1);
	printf("path2: |%s|\n", path2);
	// end of create_path

	execve(path1, commands[0], NULL);
	//execve(path2, commands[1], NULL);

	// pipe
	//dup2(infile_fd, STDOUT_FILENO);


	// create a function free_and_exit
	free_cmds(commands);
	close(infile_fd);
	close(outfile_fd);
	return (0);
}
