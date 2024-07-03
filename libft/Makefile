CCFLAGS = -Wall -Wextra -Werror
NAME = libft.a
BUILD_DIR = build

SRCS = $(wildcard src/character/*.c) \
	$(wildcard src/list/*.c) \
	$(wildcard src/memory/*.c) \
	$(wildcard src/string/*.c)
HDRS = $(wildcard include/*.h)
OBJS = $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(SRCS))

all: $(BUILD_DIR)/$(NAME)

$(BUILD_DIR)/%.o : src/%.c $(HDRS)
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) -c -I./include $< -o $@ 
	
$(BUILD_DIR)/$(NAME): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	@ar rcs $@ $(OBJS)
	@echo "[$(NAME)] $(BLUE)Built static library $@$(RESET)"

clean:
	@rm -rf $(OBJS)
	@echo "[$(NAME)] $(GREEN)Object files cleaned.\033[0m"

fclean: clean
	@rm -rf $(BUILD_DIR)
	@echo "$(NAME)] $(GREEN)Everything deleted.\033[0m"

re: fclean all
	@echo "$(NAME)] $(GREEN)Everything rebuilt.\033[0m"

.PHONY: all clean fclean re

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
BLUE = \033[34m


