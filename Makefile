# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 14:57:36 by lkilpela          #+#    #+#              #
#    Updated: 2023/10/30 15:34:49 by lkilpela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CCFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRCS =	ft_atoi.c	ft_bzero.c	ft_calloc.c	ft_memchr.c	ft_memcmp.c	ft_memcpy.c\n
		ft_memmove.c	ft_memset.c	ft_strchr.c	ft_strdup.c	ft_strlcat.c	ft_strlcpy.c\n
		ft_strncmp.c	ft_strnstr.c	ft_strrchr.c	ft_tolower.c	ft_toupper.c\n
		ft_isalnum.c	ft_isalpha.c	ft_isalpha.c	ft_isascii.c	ft_isdigit.c\n
		ft_isprint.c	ft_strlen.c	
HDRS = $(wildcard *.h)
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

%.o : %.c %.h
	$(CC) $(CCFLAGS) -c -I $< -o $@
	
$(NAME): $(OBJS)
	@echo [Sources: $(SRCS)]
	@echo [Headers: $(HDRS)]
	@echo [Objects: $(OBJS)]
	@echo [Program: $(NAME)]
	ar rcs $@ $^

.PHONY: all clen fclean re
clean:
	rm -f *.o 	

fclean: clean
	rm -f $(NAME)

re: fclean all