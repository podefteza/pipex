/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 14:57:18 by carlos-j          #+#    #+#             */
/*   Updated: 2024/09/13 15:45:22 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
//For most Unix-based system calls (file operations, process control, pipes, duplication).
#include <fcntl.h>
//For open().
#include <stdlib.h>
//For malloc() and free().
#include <stdio.h>
//For perror().
#include <string.h>
//For strerror().
#include <sys/wait.h>
//For wait() and waitpid().

// libft allowed
// ft_printf allowed

// main to accept 4 arguments --> handle cases when argc != 4 ??
// cases where infile/outfile do not exist/don't have permissions??
// 		^no infile: error (no such file or directory: <infile>)
// 		^no outfile: creates it
// 		^no cmd: error (command not found: <cmd>)
