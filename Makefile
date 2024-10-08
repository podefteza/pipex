# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carlos-j <carlos-j@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 14:02:56 by carlos-j          #+#    #+#              #
#    Updated: 2024/10/08 14:26:20 by carlos-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = pipex.c \
		path.c \
		exit.c \
		libft/ft_putstr_fd.c \
		libft/ft_split.c \
		libft/ft_strlen.c \
		libft/ft_strjoin.c \
		libft/ft_strncmp.c \
		libft/ft_strlcat.c \
		libft/ft_strlcpy.c

OBJS = ${SRCS:.c=.o}

NAME = pipex

all: ${NAME}

${NAME}: ${OBJS}
	$(CC) ${CFLAGS} ${OBJS} -o ${NAME}
	@echo "Compilation successful."

clean:
	@rm -f ${OBJS}
	@echo "Object files removed."

fclean: clean
	@rm -f ${NAME}
	@echo "Executable removed."

re: fclean all
	@echo "Recompiled all files."

.PHONY: all clean fclean re
