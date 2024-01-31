CCFLAGS = -Wall -Wextra -Werror -g 
NAME = libft.a
BUILD_DIR = build

SRCS = $(wildcard src/character/*.c) \
	$(wildcard src/list/*.c) \
	$(wildcard src/memory/*.c) \
	$(wildcard src/string/*.c)
HDRS = $(wildcard include/*.h)
OBJS = $(SRCS:%.c=%.o)

all: $(BUILD_DIR)/$(NAME)

%.o : %.c $(HDRS)
	@$(CC) $(CCFLAGS) -c -I./include $< -o $@ && printf "Compiling libft: $(notdir $<)\n"
	
$(BUILD_DIR)/$(NAME): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	@ar rcs $@ $(OBJS)
	@echo "Archive created at $@"

clean:
	@echo "Cleaning object files and build directories..."
	@rm -rf $(OBJS)
	@rm -rf $(BUILD_DIR)

fclean: clean
	@echo "Removing executable..."
	@rm -rf $(BUILD_DIR)/$(NAME)

re: fclean all
	@echo "Rebuilding everything..."

.PHONY: all clean fclean re

#-fsanitize=undefined
#for finding buffer overruns et al: -fsanitize=address
#for leak detection: -fsanitize=leak
