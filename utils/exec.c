/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 09:32:17 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/16 09:39:58 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	cmd_not_found(char *cmd_name, char ***commands)
{
	ft_putstr_fd("Command not found: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd("\n", 2);
	free_cmds(commands);
	exit(127);
}

void	exec_cmd(char **cmd_args, char **envp, char ***commands)
{
	char	*command_path;

	command_path = find_command(cmd_args[0], envp);
	if (command_path)
	{
		execve(command_path, cmd_args, envp);
		perror("Error\n");
		free_cmds(commands);
		exit(EXIT_FAILURE);
	}
	else
		cmd_not_found(cmd_args[0], commands);
}

void	execute_processes(char **cmd, char **envp, char ***commands,
		int *pipe_fds)
{
	close_fds(pipe_fds[0], pipe_fds[1]);
	exec_cmd(cmd, envp, commands);
	exit(EXIT_FAILURE);
}

void	fork_processes(int *in_out_fds, int *pipe_fds, char ***commands,
		char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		status1;
	int		status2;

	pid1 = fork();
	if (pid1 == 0)
	{
		dup2(in_out_fds[0], STDIN_FILENO);
		dup2(pipe_fds[1], STDOUT_FILENO);
		execute_processes(commands[0], envp, commands, pipe_fds);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipe_fds[0], STDIN_FILENO);
		dup2(in_out_fds[1], STDOUT_FILENO);
		execute_processes(commands[1], envp, commands, pipe_fds);
	}
	close_fds(pipe_fds[0], pipe_fds[1]);
	waitpid(pid1, &status1, 0);
	waitpid(pid2, &status2, 0);
	free_cmds(commands);
	if (status2 != 0)
		exit(status2 >> 8);
}
