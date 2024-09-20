/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:57:18 by carlos-j          #+#    #+#             */
/*   Updated: 2024/09/19 14:30:35 by carlos-j         ###   ########.fr       */
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

int	permissions(char *infile)
{
	if (access(infile, R_OK) == -1)
	{
		ft_putstr_fd(infile, 1);
		ft_putstr_fd(": Permission denied\n", 1);
	}
}

//int main(int argc, char **argv)
int main(int argc, char **argv)
{
	//ft_putstr_fd("test\n", 1);
	void(argc);
	int i;
	char	*infile;

	i = 0;
	while (argv[1][i])
	{
		infile[i] = argv[1][i];
		i++;
	}
	printf("%s", infile);

	return (0);
}
