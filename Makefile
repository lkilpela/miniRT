CCFLAGS = -Wall -Wextra -Werror -g 
NAME = libft.a

SRCS = $(wildcard src/character/*.c) \
	$(wildcard src/list/*.c) \
	$(wildcard src/memory/*.c) \
	$(wildcard src/string/*.c)
HDRS = $(wildcard include/*.h)
OBJS = $(patsubst libft/%,build/%,$(SRCS:%.c=%.o))

all: $(NAME)

build/%.o : libft/%.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -c -I./include $< -o $@ && printf "Compiling libft: $(notdir $<)\n"
	
$(NAME): $(OBJS)
	@echo "Cleaning object files and build directories..."
	@ar rcs $(NAME) $(OBJS)

clean:
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
