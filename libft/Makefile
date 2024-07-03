NAME		=	libft.a

CC			=	cc
CCFLAGS		=	-Wall -Wextra -Werror
CC_DEBUG	=	-g #-fsanitize=leak
OBJ_DIR		=	./obj
INCLUDES	=	./include
HDRS		=	-I $(INCLUDES)
CC_FULL		=	$(CC) $(CCFLAGS) $(HDRS) $(CC_DEBUG)

SRCS		=	ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_lstadd_back.c \
				ft_lstadd_front.c \
				ft_lstclear.c \
				ft_lstdelone.c \
				ft_lstiter.c \
				ft_lstlast.c \
				ft_lstmap.c \
				ft_lstnew.c \
				ft_lstsize.c \
				ft_bzero.c \
				ft_calloc.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				get_next_line.c \
				ft_substr.c \
				ft_strtrim.c \
				ft_strrchr.c \
				ft_strnstr.c \
				ft_strncmp.c \
				ft_strmapi.c \
				ft_strlen.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strjoin.c \
				ft_striteri.c \
				ft_strdup.c \
				ft_strchr.c \
				ft_split.c \
				ft_putunbr.c \
				ft_putstr.c \
				ft_putstr_fd.c \
				ft_putptr.c \
				ft_putnbr.c \
				ft_putnbr_fd.c \
				ft_puthex.c \
				ft_putendl_fd.c \
				ft_putchar.c \
				ft_putchar_fd.c \
				ft_printf.c \
				ft_itoa.c \
				ft_atol.c \
				ft_atoi.c

LIBFT_DIR	=	./src
OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# vpath for finding source files
vpath %.c $(LIBFT_DIR) $(LIBFT_DIR)/character $(LIBFT_DIR)/list \
		$(LIBFT_DIR)/memory  $(LIBFT_DIR)/string

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC_FULL) -c $< -o $@ 
	
$(NAME): $(OBJS)
	@echo "--------------------------------------------"
	@ar -rcs $@ $^
	@echo "[$(NAME)] $(BLUE)Built static library $@$(RESET)"
	@echo "--------------------------------------------"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "[$(NAME)] $(GREEN)Object files cleaned.$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "[$(NAME)] $(GREEN)Everything deleted.$(RESET)"

re: fclean all
	@echo "[$(NAME)] $(GREEN)Everything rebuilt.$(RESET)"

.PHONY: all clean fclean re

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
BLUE = \033[34m
