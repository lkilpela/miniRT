CCFLAGS = -Wall -Wextra -Werror -g 
NAME = libft.a
BUILD_DIR = build

SRCS = $(wildcard src/character/*.c) \
	$(wildcard src/list/*.c) \
	$(wildcard src/memory/*.c) \
	$(wildcard src/string/*.c)
HDRS = $(wildcard include/*.h)
OBJS = $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(SRCS)))

all: $(BUILD_DIR)/$(NAME)

$(BUILD_DIR)/%.o : src/%.c $(HDRS)
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -c -I./include $< -o $@ 
	
$(BUILD_DIR)/$(NAME): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	@ar rcs $@ $(OBJS)
	@echo "Archive created at $@"

clean:
	@rm -rf $(OBJS)
	@echo "\033[32m[libft] Object files cleaned.\033[0m\n"

fclean: clean
	@rm -rf $(BUILD_DIR)
	@echo "\033[32m[libft] Everything deleted.\033[0m\n"

re: fclean all
	@echo "\033[32m[libft]Everything rebuilt.\033[0m\n"

.PHONY: all clean fclean re

#-fsanitize=undefined
#for finding buffer overruns et al: -fsanitize=address
#for leak detection: -fsanitize=leak
