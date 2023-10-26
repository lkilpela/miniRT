# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 14:57:36 by lkilpela          #+#    #+#              #
#    Updated: 2023/10/26 14:57:38 by lkilpela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CCFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRCS = ft_isalpha.c	ft_isdigit.c	
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