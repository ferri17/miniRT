#<---COLORS--->#
GREEN = \033[1;92m
RED = \033[1;91m
NC = \033[0m
YELLOW=\033[1;33m

#<---NAME--->#
NAME		=	libmlx.a

#<---SRC && OTHERS--->#
OBJ_DIR	=	./obj/

SRC_C	=	mlx_shaders.c mlx_xpm.c mlx_int_str_to_wordtab.c
SRC_M	= 	mlx_new_image.m mlx_new_window.m mlx_init_loop.m

OBJ_C	=	$(addprefix $(OBJ_DIR)src_c/, $(SRC_C:%.c=%.o)) #$(SRC_C:%.c=%.o) 
OBJ_M	=	$(addprefix $(OBJ_DIR)src_m/, $(SRC_M:%.m=%.o)) #$(SRC_M:%.m=%.o) 

CFLAGS	+=	-O2 -Wno-deprecated-declarations -DSTRINGPUTX11

MDP		=	mkdir -p

#<---RULES--->#
$(OBJ_DIR)src_c/%.o: %.c Makefile
	@$(MDP) $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)src_m/%.o: %.m Makefile
	@$(MDP) $(dir $@)
	@$(CC) -MT $@ $(CFLAGS) -MMD -MP -c $< -o $@

all		:
	@$(MAKE) $(NAME)

$(NAME)::	$(OBJ_C) $(OBJ_M)
	@ar -crs $@ $(OBJ_C) $(OBJ_M)
	@#ranlib $@
	@echo "$(GREEN)MLX COMPILED$(NC)"
$(NAME)::
	@echo -n

clean	:
	@rm -rf $(OBJ_DIR) *~
	@rm -f mlx_app
	@echo "$(RED)MLX OBJS DELETED$(NC)"

fclean	:
	@$(MAKE) clean
	@$(RM) $(NAME)
	@echo "$(RED)MLX EXEC DELETED$(NC)"

re: fclean all

.PHONY:	all clean fclean re