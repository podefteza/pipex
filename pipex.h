#ifndef PIPEX_H
# define PIPEX_H

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



// libft
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);





#endif
