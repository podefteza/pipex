/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:05:02 by carlos-j          #+#    #+#             */
/*   Updated: 2024/09/23 13:10:15 by carlos-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
// For most Unix-based system calls (file operations, process control, pipes, duplication).
# include <fcntl.h>
// For open().
# include <stdlib.h>
// For malloc() and free().
# include <stdio.h>
// For perror().
# include <string.h>
// For strerror().
# include <sys/wait.h>
// For wait() and waitpid().

// libft
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);

#endif
