# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 10:55:51 by lkilpela          #+#    #+#              #
#    Updated: 2024/09/26 10:00:23 by lkilpela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minirt

CC			=	cc
CCFLAGS		=	-Wall -Wextra -Werror -pthread
CC_DEBUG	=	-g #-fsanitize=leak
INCLUDES	= 	./include
HDRS		=	 -I $(INCLUDES)  -I $(LIBFT_INCLUDES) -I $(LIBMLX_INCLUDES)
CC_FULL		=	$(CC) $(CCFLAGS) $(HDRS) $(CC_DEBUG)


LIBFT_DIR		=	./lib/libft
LIBFT			=	$(LIBFT_DIR)/libft.a
LIBFT_INCLUDES	=	$(LIBFT_DIR)/include

LIBMLX_DIR		=	./lib/MLX42
LIBMLX			= 	$(LIBMLX_DIR)/build/libmlx42.a
#LIBMLX_LINUX	=	-ldl -lglfw -lm
LIBMLX_OS		=	-L$(LIBMLX_DIR)/build -lmlx42 -lglfw -framework Cocoa -framework OpenGL -framework IOKit
LIBMLX_INCLUDES	=	$(LIBMLX_DIR)/include/
# LIBMLX_FLAGS 	= 	$(LIBMLX_DIR)/build 
RPATH_FLAGS     =   -Wl,-rpath,/usr/local/lib/

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
                    color_math.c \
                    cylinder.c \
                    error.c \
                    intersections.c \
                    lights.c \
                    main.c \
                    materials.c \
                    matrix.c \
                    parser_obj.c \
                    parser_scene.c \
                    parser_utils.c \
                    parser_utils1.c \
                    plane.c \
                    print.c \
                    ray.c \
                    rotation.c \
                    scene.c \
                    shapes.c \
                    sphere.c \
                    transformations.c \
                    tuple.c \
                    tuple_math.c \
					tuple_math1.c \
					utils.c \
                    window.c \
                    world.c

OBJECTS			=	$(addprefix $(OBJ_DIR)/, $(SRCS:%.c=%.o))

# vpath for finding source files
vpath %.c $(SRC_DIR) $(SRC_DIR)/matrix $(SRC_DIR)/parser $(SRC_DIR)/redo $(SRC_DIR)/shapes $(SRC_DIR)/utils
		 
all: libmlx $(NAME)

clone_mlx42:
	if [ ! -d "$(LIBMLX_DIR)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX_DIR); \
	fi

libmlx: clone_mlx42
	@cmake $(LIBMLX_DIR) -B $(LIBMLX_DIR)/build && make -C $(LIBMLX_DIR)/build -j4

# If you have Linux -> use $(LIBMLX_LINUX)
# If you have OS -> use $(LIBMLX_OS)
$(NAME): $(LIBFT) $(LIBMLX) $(OBJECTS)
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
	@echo "[$(NAME)] Object files cleaned."

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@echo "[$(NAME)] Everything deleted."

re: fclean all
	@echo "[$(NAME)] Everything rebuilt."

################################################################################
# TEST
################################################################################
test: $(NAME)
	./$(NAME) test_scene.rt

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
.PHONY: all bonus re clean fclean libft_force libmlx_force db vg vglog vglog_clean norm norm2

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
BLUE = \033[34m
