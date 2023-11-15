# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/26 14:57:36 by lkilpela          #+#    #+#              #
#    Updated: 2023/11/15 14:13:45 by lkilpela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CCFLAGS = -Wall -Wextra -Werror -g
NAME = libft.a

SRCS = \
	ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_isascii.c \
	ft_memset.c \
	ft_bzero.c \
	ft_strjoin.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_atoi.c \
	ft_strdup.c \
	ft_calloc.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_substr.c \
	ft_itoa.c \
	ft_striteri.c \
	ft_strmapi.c \
	ft_strtrim.c \
	ft_split.c \

BONUS = \
	ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c
				
HDRS = $(wildcard *.h)
OBJS = $(SRCS:%.c=%.o)
BONUS_OBJS = $(BONUS:%.c=%.o)

all: $(NAME)

%.c : %.h

%.o : %.c
	$(CC) $(CCFLAGS) -c -I. $< -o $@
	
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: .bonus

.bonus: $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)
	touch .bonus

clean:
	rm -f $(OBJS) $(BONUS_OBJS)
	rm -f .bonus	

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re