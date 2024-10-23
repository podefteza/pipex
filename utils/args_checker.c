/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:11:27 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/23 13:35:39 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

/*
// debug... delete later...
void	print_commands(char ***commands)
{
	int		i;
	char	***commands;

	i = 0;
	printf("=================== DEBUG ===================\n");
	for (i = 0; commands[0][i]; i++)
		printf("Command 0 | %d: %s\n", i, commands[0][i]);
	for (i = 0; commands[1][i]; i++)
		printf("Command 1 | %d: %s\n", i, commands[1][i]);
}*/

void	strip_quotes_from_arguments(char **args)
{
	int		i;
	size_t	len;
	char	*stripped;

	i = 0;
	while (args[i])
	{
		len = ft_strlen(args[i]);
		if ((args[i][0] == '\'' && args[i][len - 1] == '\'')
			|| (args[i][0] == '"' && args[i][len - 1] == '"'))
		{
			stripped = malloc(len - 1);
			if (stripped)
			{
				ft_strlcpy(stripped, args[i] + 1, len - 1);
				free(args[i]);
				args[i] = stripped;
			}
		}
		i++;
	}
}

char	*merge_after_strip(char *merged_command, char **args, int i)
{
	char	*temp;
	char	*final_stripped;

	temp = malloc(ft_strlen(merged_command) + ft_strlen(args[i]) + 2);
	if (temp)
	{
		ft_strlcpy(temp, merged_command, ft_strlen(merged_command) + 1);
		ft_strlcat(temp, " ", ft_strlen(temp) + 2);
		ft_strlcat(temp, args[i], ft_strlen(temp) + ft_strlen(args[i]) + 1);
		free(merged_command);
		merged_command = temp;
	}
	if (args[i][ft_strlen(args[i]) - 1] == '\'')
	{
		final_stripped = malloc(ft_strlen(merged_command) - 1);
		if (final_stripped)
		{
			ft_strlcpy(final_stripped, merged_command + 1,
				ft_strlen(merged_command) - 1);
			free(merged_command);
			merged_command = final_stripped;
		}
		return (merged_command);
	}
	return (merged_command);
}

char	*merge_quoted_arguments(char **args)
{
	char	*merged_command;
	int		i;

	merged_command = NULL;
	i = 0;
	strip_quotes_from_arguments(args);
	while (args[i])
	{
		if (args[i][0] == '\'' && !merged_command)
			merged_command = ft_strdup(args[i]);
		else if (merged_command)
			merged_command = merge_after_strip(merged_command, args, i);
		i++;
	}
	return (merged_command);
}

char	***cmds(char **argv)
{
	char	***commands;
	char	*merged_command;
	int		j;

	commands = initialize_commands(argv);
	if (!commands)
		return (NULL);
	strip_quotes_from_arguments(commands[0]);
	merged_command = merge_quoted_arguments(commands[1]);
	if (merged_command)
	{
		j = 1;
		while (commands[1][j])
		{
			free(commands[1][j]);
			commands[1][j] = NULL;
			j++;
		}
		commands[1][1] = merged_command;
		commands[1][2] = NULL;
	}
	return (commands);
}
