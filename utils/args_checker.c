/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:11:27 by carlos-j          #+#    #+#             */
/*   Updated: 2024/11/07 09:44:58 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	remove_quotes(char **args)
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

char	*merge_between_quotes(char *merged_command, char **args, int i)
{
	char	*temp;

	temp = malloc(ft_strlen(merged_command) + ft_strlen(args[i]) + 2);
	if (temp)
	{
		ft_strlcpy(temp, merged_command, ft_strlen(merged_command) + 1);
		ft_strlcat(temp, " ", ft_strlen(temp) + 2);
		ft_strlcat(temp, args[i], ft_strlen(temp) + ft_strlen(args[i]) + 1);
		free(merged_command);
		merged_command = temp;
	}
	if (args[i][ft_strlen(args[i]) - 1] == '\''
	|| (args[i][ft_strlen(args[i]) - 1] == '\"'))
	{
		temp = malloc(ft_strlen(merged_command) - 1);
		if (temp)
		{
			ft_strlcpy(temp, merged_command + 1,
				ft_strlen(merged_command) - 1);
			free(merged_command);
			merged_command = temp;
		}
		return (merged_command);
	}
	return (merged_command);
}

char	*combine_quoted_arguments(char **args)
{
	char	*merged_command;
	int		i;

	merged_command = NULL;
	i = 0;
	remove_quotes(args);
	while (args[i])
	{
		if ((args[i][0] == '\'' && !merged_command)
		|| (args[i][0] == '\"' && !merged_command))
			merged_command = ft_strdup(args[i]);
		else if (merged_command)
			merged_command = merge_between_quotes(merged_command, args, i);
		i++;
	}
	return (merged_command);
}

char	***cmds(char **argv)
{
	char	***commands;
	char	*merged_command;
	int		i;

	commands = initialize_commands(argv);
	if (!commands)
		return (NULL);
	remove_quotes(commands[0]);
	merged_command = combine_quoted_arguments(commands[1]);
	if (merged_command)
	{
		i = 1;
		while (commands[1][i])
		{
			free(commands[1][i]);
			commands[1][i] = NULL;
			i++;
		}
		commands[1][1] = merged_command;
		commands[1][2] = NULL;
	}
	return (commands);
}
