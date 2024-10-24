/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:04:18 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/23 17:09:28 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	infile_check(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		fd = open("/dev/null", O_RDONLY);
		if (fd == -1)
		{
			perror("/dev/null");
			exit(EXIT_FAILURE);
		}
	}
	return (fd);
}

int	outfile_check(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		perror(filename);
		exit(EXIT_FAILURE);
	}
	return (fd);
}
