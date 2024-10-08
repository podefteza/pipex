/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:25:34 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/08 14:26:56 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	exit_error(void)
{
	ft_putstr_fd("Usage: ./pipex infile cmd1 cmd2 outfile\n", 2);
	exit(0);
}