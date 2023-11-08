# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lumik <lumik@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 14:57:36 by lkilpela          #+#    #+#              #
#    Updated: 2023/11/08 15:43:28 by lumik            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CCFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRCS =	ft_atoi.c	ft_bzero.c	ft_calloc.c	ft_memchr.c	ft_memcmp.c	ft_memcpy.c\
ft_memmove.c	ft_memset.c	ft_strchr.c	ft_strdup.c	ft_strlcat.c	ft_strlcpy.c\
ft_strncmp.c	ft_strnstr.c	ft_strrchr.c	ft_tolower.c	ft_toupper.c\
ft_isalnum.c	ft_isalpha.c	ft_isalpha.c	ft_isascii.c	ft_isdigit.c\
ft_isprint.c	ft_strlen.c	ft_substr.c	ft_strjoin.c	ft_strtrim.c
HDRS = $(wildcard *.h)
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

%.o : %.c %.h
	$(CC) $(CCFLAGS) -g -c -I $< -o $@
	
$(NAME): $(OBJS)
	@echo [Sources: $(SRCS)]
	@echo [Headers: $(HDRS)]
	@echo [Objects: $(OBJS)]
	@echo [Program: $(NAME)]
	ar rcs $@ $^

.PHONY: all clean fclean re
clean:
	rm -f *.o 	

fclean: clean
	rm -f $(NAME)

re: fclean all