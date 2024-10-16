/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:05:02 by carlos-j          #+#    #+#             */
/*   Updated: 2024/10/16 09:42:40 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

// ./libft/
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// ./utils/args_checker/
int		file_check(char *filename, int is_input);
char	***cmds(char **argv);

// ./utils/exec/
void	cmd_not_found(char *cmd_name, char ***commands);
void	exec_cmd(char **cmd_args, char **envp, char ***commands);
void	execute_processes(char **cmd, char **envp, char ***commands,
			int *pipe_fds);
void	fork_processes(int *in_out_fds, int *pipe_fds, char ***commands,
			char **envp);

// ./utils/exit/
void	close_fds(int fd1, int fd2);
void	free_cmds(char ***commands);
int		exit_error(void);

// ./utils/path/
char	*cmd_is_path(char *cmd);
char	*build_path(char *dir, char *cmd);
char	*get_path_from_env(char **envp);
char	*search_in_path(char *path, char *cmd);
char	*find_command(char *cmd, char **envp);

#endif
