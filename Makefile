# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:36:01 by fbosch            #+#    #+#              #
#    Updated: 2023/12/12 12:54:33 by apriego-         ###   ########.fr        #
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
FILES_CAMERA	=	init_render.c
FILES_INIT		=	check_arguments.c init_structs.c fill_structs.c init_objs.c\
					put_structs.c fill_objs.c free_structs.c hit_cone.c free_objs.c hit_first.c hit_cylinder.c
FILES_MLX		=	mlx_color.c mlx_events.c mlx_init.c
FILES_UTILS		=	vec3_utils.c vec3_utils2.c math_utils.c ray_utils.c

DIR_MAIN		=	src/main/
DIR_CAMERA		=	src/camera/
DIR_INIT		=	src/init/
DIR_UTILS		=	src/utils/
DIR_MLX_F		=	src/mlx/

DIR_INCLUDE		=	include/
DIR_BUILD		=	.build/

MLX				=	libmlx.a
DIR_MLX			=	minilibx_macos/

SRC_MAIN		=	$(addprefix $(DIR_MAIN),$(FILES_MAIN))
SRC_CAMERA		=	$(addprefix $(DIR_CAMERA),$(FILES_CAMERA))
SRC_INIT		=	$(addprefix $(DIR_INIT),$(FILES_INIT))
SRC_MLX			=	$(addprefix $(DIR_MLX_F),$(FILES_MLX))
SRC_UTILS		=	$(addprefix $(DIR_UTILS),$(FILES_UTILS))

OBJ_MAIN		=	$(addprefix $(DIR_BUILD),$(SRC_MAIN:.c=.o))
OBJ_CAMERA		=	$(addprefix $(DIR_BUILD),$(SRC_CAMERA:.c=.o))
OBJ_INIT		=	$(addprefix $(DIR_BUILD),$(SRC_INIT:.c=.o))
OBJ_UTILS		=	$(addprefix $(DIR_BUILD),$(SRC_UTILS:.c=.o))
OBJ_MLX			=	$(addprefix $(DIR_BUILD),$(SRC_MLX:.c=.o))

OBJ_ALL			=	$(OBJ_MAIN) $(OBJ_CAMERA) $(OBJ_INIT) $(OBJ_MLX) $(OBJ_UTILS)

DEP				=	$(OBJ_ALL:%.o=%.d) #$(BONUS_OBJ:%.o=%.d)

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -O2
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
