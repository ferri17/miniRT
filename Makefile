# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:36:01 by fbosch            #+#    #+#              #
#    Updated: 2024/02/01 15:43:14 by apriego-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN=\033[1;32m
RED=\033[1;31m
BLUE=\033[1;34m
YELLOW=\x1b[33;01m
END=\033[0m
CL_LINE=\033[K

NAME			=	miniRT

LIBFT			=	libft.a
DIR_LIBFT		=	libft/

FILE_MAKE		=	Makefile

FILES_MAIN		=	main.c
FILES_CAMERA	=	init_render.c object_selector.c render.c light.c outlines.c\
					get_position_obj.c reflection.c render_utils.c
FILES_INIT		=	check_arguments.c init_structs.c fill_structs.c init_objs.c init_func_objs.c\
					put_structs.c fill_objs.c free_structs.c free_objs.c init_utils.c init_texture.c\
					init_img.c check_ident.c
FILES_HIT		=	hit_sphere.c hit_plane.c hit_cylinder.c hit_cone.c hit_disk.c
FILES_MLX		=	mlx_color.c mlx_events.c mlx_init.c events.c
FILES_UTILS		=	vec3_utils.c vec3_utils2.c vec3_utils3.c math_utils.c slider.c\
					ray_utils.c menu.c
FILES_TEXT		=	get_color_obj.c map_objects_uv.c utils.c utils_get_texture.c
FILES_TEXTUR	=	texture.c
DIR_MAIN		=	src/main/
DIR_CAMERA		=	src/camera/
DIR_INIT		=	src/init/
DIR_UTILS		=	src/utils/
DIR_MLX_F		=	src/mlx/
DIR_HIT			=	src/hit/
DIR_TEXT		=	src/textures/

DIR_INCLUDE		=	include/
DIR_BUILD		=	.build/

MLX				=	libmlx.a
DIR_MLX			=	minilibx_macos/

SRC_MAIN		=	$(addprefix $(DIR_MAIN),$(FILES_MAIN))
SRC_CAMERA		=	$(addprefix $(DIR_CAMERA),$(FILES_CAMERA))
SRC_INIT		=	$(addprefix $(DIR_INIT),$(FILES_INIT))
SRC_MLX			=	$(addprefix $(DIR_MLX_F),$(FILES_MLX))
SRC_UTILS		=	$(addprefix $(DIR_UTILS),$(FILES_UTILS))
SRC_HIT			=	$(addprefix $(DIR_HIT),$(FILES_HIT))
SRC_TEXT		=	$(addprefix $(DIR_TEXT),$(FILES_TEXT))

OBJ_MAIN		=	$(addprefix $(DIR_BUILD),$(SRC_MAIN:.c=.o))
OBJ_CAMERA		=	$(addprefix $(DIR_BUILD),$(SRC_CAMERA:.c=.o))
OBJ_INIT		=	$(addprefix $(DIR_BUILD),$(SRC_INIT:.c=.o))
OBJ_UTILS		=	$(addprefix $(DIR_BUILD),$(SRC_UTILS:.c=.o))
OBJ_MLX			=	$(addprefix $(DIR_BUILD),$(SRC_MLX:.c=.o))
OBJ_HIT			=	$(addprefix $(DIR_BUILD),$(SRC_HIT:.c=.o))
OBJ_TEXT		=	$(addprefix $(DIR_BUILD),$(SRC_TEXT:.c=.o))

OBJ_ALL			=	$(OBJ_MAIN) $(OBJ_CAMERA) $(OBJ_INIT) $(OBJ_MLX) $(OBJ_UTILS) $(OBJ_HIT) $(OBJ_TEXT) $(OBJ_TEXTUR)

DEP				=	$(OBJ_ALL:%.o=%.d)

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -O3 #-fsanitize=address
DEPFLAGS		=	-I $(DIR_INCLUDE) -I $(DIR_LIBFT) -I $(DIR_MLX) -MMD -MP
MLXFLGS			=	-L$(DIR_MLX) -lmlx -lm -framework OpenGL -framework AppKit
DIR_DUP			=	mkdir -p $(@D)

RM				=	/bin/rm -f

all: make_libs $(NAME)

make_libs:
	@printf "$(YELLOW)COMPILING LIBFT...\n$(END)"
	@$(MAKE) -C $(DIR_LIBFT) --no-print-directory
	@printf "$(YELLOW)COMPILING MINILIBX...\n$(END)"
	@$(MAKE) -C $(DIR_MLX) --no-print-directory

$(NAME): $(OBJ_ALL) $(DIR_LIBFT)$(LIBFT) $(DIR_MLX)$(MLX)
		@$(CC) $(CFLAGS) $(DEPFLAGS) $(OBJ_ALL) $(DIR_LIBFT)$(LIBFT) $(DIR_MLX)$(MLX) $(MLXFLGS) -o $(NAME)
		@printf "\n$(GREEN)$(NAME) COMPILED!\n$(END)"

$(DIR_BUILD)%.o: %.c $(DIR_LIBFT)$(LIBFT) $(DIR_MLX)$(MLX) $(FILE_MAKE)
	@printf "\r$(CL_LINE)$(YELLOW)Compiling... $(END)$(patsubst $(DIR_BUILD)%,%,$@) "
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
	
clean:
	@$(MAKE) -C $(DIR_LIBFT) clean --no-print-directory
	@$(MAKE) -C $(DIR_MLX) clean --no-print-directory
	@$(RM) $(OBJ_ALL) $(DEP)
	@printf "$(RED)$(NAME) OBJECTS DELETED\n$(END)"

fclean: clean
	@$(MAKE) -C $(DIR_LIBFT) fclean --no-print-directory
	@$(MAKE) -C $(DIR_MLX) fclean --no-print-directory
	@$(RM) $(NAME)
	@$(RM) -r $(DIR_BUILD)
	@printf "$(RED)$(NAME) DELETED\n$(END)"

re: fclean all

norm	:
	@printf "${YELLOW}Norminette...\n${NC}"
	@printf "${RED}"
	@norminette libft src/*/*.c src/*.c include/*.h > test && printf "$(GREEN)\t[OK]\n" || grep Error test
	@printf "${NC}"
	@rm test

.PHONY: all clean fclean re bonus
	
-include $(DEP)
