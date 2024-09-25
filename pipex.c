/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:57:18 by carlos-j          #+#    #+#             */
/*   Updated: 2024/09/24 13:22:23 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*open, close, read, write,
malloc, free, perror,
strerror, access, dup, dup2,
execve, exit, fork, pipe,
unlink, wait, waitpid*/

// $> < file1 cmd1 | cmd2 > file2
// ./pipex file1 cmd1 cmd2 file2

// main to accept 4 arguments --> handle cases when argc != 4 ??
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

int	exit_error()
{
	ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	exit (0);
}

int	main(int argc, char **argv)
{
	int	infile_fd;
	int	outfile_fd;
	//char	*cmd1;
	//char	*cmd2;

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
	// pipex
	// printf("%d", infile_fd);
	// printf("%d", outfile_fd);
	close(infile_fd);
	close(outfile_fd);
	return (0);
}
