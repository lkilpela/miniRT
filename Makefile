# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 10:55:51 by lkilpela          #+#    #+#              #
#    Updated: 2024/10/09 17:26:31 by lkilpela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minirt

CC			=	cc
CCFLAGS		=	-Wall -Wextra -Werror -pthread
CC_DEBUG	=	-g
INCLUDES	= 	./include
HDRS		=	 -I $(INCLUDES)  -I $(LIBFT_INCLUDES) -I $(LIBMLX_INCLUDES)
CC_FULL		=	$(CC) $(CCFLAGS) $(HDRS) $(CC_DEBUG)


LIBFT_DIR		=	./lib/libft
LIBFT			=	$(LIBFT_DIR)/libft.a
LIBFT_INCLUDES	=	$(LIBFT_DIR)/include

LIBMLX_DIR		=	./lib/MLX42
LIBMLX			=	$(LIBMLX_DIR)/build/libmlx42.a
LIBMLX_LINUX	=	-ldl -lglfw -lm
LIBMLX_OS		=	-L$(LIBMLX_DIR)/build -lmlx42 -lglfw -framework Cocoa -framework OpenGL -framework IOKit
LIBMLX_INCLUDES	=	$(LIBMLX_DIR)/include/
RPATH_FLAGS		=	-Wl,-rpath,/usr/local/lib/

MINIRT_HDRS 	= 	$(INCLUDES)/tuple.h \
					$(INCLUDES)/structs.h \
					$(INCLUDES)/matrix.h \
					$(INCLUDES)/window.h \
					$(INCLUDES)/error.h \
					$(INCLUDES)/shapes.h \
					$(INCLUDES)/parser.h

OBJ_DIR			=	./obj
SRC_DIR			=	./src
SRCS			=	camera.c \
					color.c \
					cylinder.c \
					cylinder1.c \
					error.c \
					equation.c \
					intersections.c \
					lights.c \
					main.c \
					materials.c \
					matrix.c \
					matrix1.c \
					matrix_math.c \
					parser_obj.c \
					parser_scene.c \
					parser_utils.c \
					parser_utils1.c \
					plane.c \
					print.c \
					ray.c \
					render.c \
					shapes.c \
					sphere.c \
					shader.c \
					transformations.c \
					tuple.c \
					tuple_math.c \
					tuple_math1.c \
					tuple_math2.c \
					window.c \
					world.c


OBJECTS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# vpath for finding source files
vpath %.c $(SRC_DIR) $(SRC_DIR)/matrix $(SRC_DIR)/parser $(SRC_DIR)/scene $(SRC_DIR)/shapes $(SRC_DIR)/intersections $(SRC_DIR)/utils
		 
all: libmlx $(NAME)

mac: CCFLAGS += -D__MACOS__
mac: libmlx libft $(NAME)_mac

clone_mlx42:
	if [ ! -d "$(LIBMLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX_DIR); \
	fi

libmlx: clone_mlx42
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4

$(NAME): $(LIBFT) $(LIBMLX) $(OBJECTS)
	@echo "--------------------------------------------"
	@$(CC_FULL) $(OBJECTS) $(LIBFT) $(LIBMLX) $(LIBMLX_LINUX) $(RPATH_FLAGS) -o $(NAME) 
	@echo "[$(NAME)] $(B)Built target $(NAME)$(RC)"
	@echo "--------------------------------------------"

$(NAME)_mac: $(LIBFT) $(LIBMLX) $(OBJECTS)
	@echo "--------------------------------------------"
	@$(CC_FULL) $(OBJECTS) $(LIBFT) $(LIBMLX) $(LIBMLX_OS) $(RPATH_FLAGS) -o $(NAME) 
	@echo "[$(NAME)] $(B)Built target $(NAME)$(RC)"
	@echo "--------------------------------------------"

$(OBJ_DIR)/%.o: %.c $(MINIRT_HDRS)
	@mkdir -p $(@D)
	@$(CC_FULL) -c $< -o $@
	@echo "$(G)Compiled: $< $(RC)"

$(LIBFT): libft_force
	@make -C $(LIBFT_DIR)

libft_force:
	@true

clean:
	@rm -rf $(NAME).dSYM/ obj/
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(LIBMLX_DIR)/build
	@echo "[$(NAME)] Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(LIBMLX_DIR)
	@echo "[$(NAME)] Everything deleted."

re: fclean all
	@echo "[$(NAME)] Everything rebuilt."


################################################################################
# NORM
################################################################################
norm:
	norminette . | grep -v "OK!" || true

norm2:
	norminette .

################################################################################
# VALGRIND
################################################################################
VG = valgrind

VG_FLAGS = --leak-check=full \
	--show-leak-kinds=all \
	--trace-children=yes \
	--track-fds=yes \
	--quiet \
	--suppressions=readline.supp

VG_LOG_FLAGS = $(VG_FLAGS) \
	--log-file=$(VG_LOG) \
	--track-origins=yes \
	--verbose \
	--gen-suppressions=all

VG_LOG = valgrind_leaks.log

VG_ARGS = 

vg: vg_build
	$(VG) $(VG_FLAGS) ./$(NAME) $(VG_ARGS)

vglog: vg_build
	$(VG) $(VG_LOG_FLAGS) ./$(NAME) $(VG_ARGS)

vg_build: $(OBJECTS)
	$(CC_FULL) $(OBJECTS) $(LIBMLX) $(LIBFT) -o $(NAME)

vglog_clean: fclean
	rm -f $(VG_LOG)

################################################################################
# PHONY
################################################################################
.PHONY: all bonus re clean fclean libft_force clone_mlx42 mac db vg vglog vglog_clean norm norm2

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
BLUE = \033[34m
