# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 14:57:36 by lkilpela          #+#    #+#              #
#    Updated: 2024/01/28 17:07:01 by lkilpela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CCFLAGS = -Wall -Wextra -Werror -g 
NAME = libft.a

SRCS = $(wildcard src/character/*.c) \
	$(wildcard src/list/*.c) \
	$(wildcard src/memory/*.c) \
	$(wildcard src/string/*.c)
HDRS = $(wildcard include/*.h)
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

%.o : %.c $(HDRS)
	$(CC) $(CCFLAGS) -c -I./include $< -o $@
	
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

#-fsanitize=undefined
#for finding buffer overruns et al: -fsanitize=address
#for leak detection: -fsanitize=leak