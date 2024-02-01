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
	@$(CC) $(CCFLAGS) -c -I./include $< -o $@ && printf "[libft] Compiling: $(notdir $<)\n"
	
$(BUILD_DIR)/$(NAME): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	@ar rcs $@ $(OBJS)
	@echo "[libft] Archive created at $@"

clean:
	@echo "[libft] Cleaning object files..."
	@rm -rf $(OBJS)

fclean: clean
	@echo "[libft] Removing build directory and executable..."
	@rm -rf $(BUILD_DIR)

re: fclean all
	@echo "[libft] Rebuilding everything..."

.PHONY: all clean fclean re

#-fsanitize=undefined
#for finding buffer overruns et al: -fsanitize=address
#for leak detection: -fsanitize=leak
