# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: apriego- <apriego-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:36:01 by fbosch            #+#    #+#              #
#    Updated: 2023/11/09 12:25:08 by apriego-         ###   ########.fr        #
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
LIBFT_DIR		=	libft/

FILE_MAKE		=	Makefile

SRC				=	main.c check_arguments.c init_structs.c fill_structs.c

SRC_DIR			=	src/

INCLUDE_DIR		=	include/
BUILD_DIR		=	.build/

MLX				=	libmlx.a
MLX_DIR			=	minilibx_macos/

SRC_FILES		=	$(addprefix $(SRC_DIR),$(SRC))

OBJ				=	$(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRC_FILES))

DEP				=	$(OBJ:%.o=%.d) $(BONUS_OBJ:%.o=%.d)

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -O2
DEPFLAGS		=	-I $(INCLUDE_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR) -MMD -MP
MLXFLGS			=	-L$(MLX_DIR) -lmlx -lm -framework OpenGL -framework AppKit
DIR_DUP			=	mkdir -p $(@D)

RM				=	/bin/rm -f

all: make_libs $(NAME)

make_libs:
	@printf "$(YELLOW)COMPILING LIBFT...\n$(END)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@printf "$(YELLOW)COMPILING MINILIBX...\n$(END)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory

$(NAME): $(OBJ) $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX)
		@$(CC) $(CFLAGS) $(DEPFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX) $(MLXFLGS) -o $(NAME)
		@printf "\n$(GREEN)$(NAME) COMPILED!\n$(END)"

$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX) $(FILE_MAKE)
	@printf "\r$(CL_LINE)$(YELLOW)Compiling... $(END)$(patsubst $(BUILD_DIR)%,%,$@)"
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@
	
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory
	@$(RM) $(OBJ) $(DEP)
	@printf "$(RED)$(NAME) OBJECTS DELETED\n$(END)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) fclean --no-print-directory
	@$(RM) $(NAME)
	@$(RM) -r $(BUILD_DIR)
	@printf "$(RED)$(NAME) DELETED\n$(END)"

re: fclean all

norm	:
	@printf "${YELLOW}Norminette...\n${NC}"
	@printf "${RED}"
	@norminette src/*/*.c src/*.c include/*.h > test && printf "$(GREEN)\t[OK]\n" || grep Error test
	@printf "${NC}"
	@rm test

.PHONY: all clean fclean re bonus
	
-include $(DEP)