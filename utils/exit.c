/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:25:34 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/23 13:40:07 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	close_fds(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	free_cmds(char ***commands)
{
	int	i;
	int	j;

	if (!commands)
		return ;
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

int	exit_error(void)
{
	ft_putstr_fd("Usage: ./pipex \"infile\" \"cmd1\" \"cmd2\" \"outfile\"\n",
		2);
	exit(1);
}
