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
	@$(CC) $(CCFLAGS) -c -I./include $< -o $@ && printf "Compiling libft: $(notdir $<)\n"
	
$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

clean:
	@echo "Cleaning object files and build directories..."
	@rm -f $(OBJS)
	@rm -f build

fclean: clean
	@echo "Removing executable..."
	@rm -f $(NAME)

re: fclean all
	@echo "Rebuilding everything..."

.PHONY: all clean fclean re

#-fsanitize=undefined
#for finding buffer overruns et al: -fsanitize=address
#for leak detection: -fsanitize=leak
