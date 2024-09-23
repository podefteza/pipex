/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:57:18 by carlos-j          #+#    #+#             */
/*   Updated: 2024/09/23 12:20:26 by carlos-j         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	int infile_fd, outfile_fd;
	if (argc != 5)
	{
		ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (1);
	}
	if (access(argv[1], F_OK) != 0)
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (1);
	}
	if (access(argv[1], R_OK) != 0)
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (1);
	}
	infile_fd = open(argv[1], O_RDONLY);
	if (infile_fd == -1)
	{
		perror(argv[1]);
		return (1);
	}
	outfile_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
	{
		ft_putstr_fd(argv[4], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		close(infile_fd);
		return (1);
	}
	close(infile_fd);
	close(outfile_fd);
	return (0);
}
