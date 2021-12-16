# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 14:49:19 by ghan              #+#    #+#              #
#    Updated: 2021/12/16 16:09:52 by ghan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC						= gcc

ifdef DEBUG
	CFLAGS 	= -g3 -fsanitize=address -D BUFFER_SIZE=64 -D WIN_W=$(WIN_W) -D WIN_H=$(WIN_H)
else ifdef LEAKS
	CFLAGS 	= -g -D BUFFER_SIZE=64 -D WIN_W=$(WIN_W) -D WIN_H=$(WIN_H)
else 
	CFLAGS 	= -Wall -Wextra -Werror -D BUFFER_SIZE=64 -D WIN_W=$(WIN_W) -D WIN_H=$(WIN_H)
endif

ifndef WIN_W
	WIN_W = 1920
endif
ifndef WIN_H
	WIN_H = 1080
endif

NAME					= miniRT

LIBFT_DIR				= ./lib/libft/
LIBFT_FLAGS				= -L./$(LIBFT_DIR) -lft
LIBFT_FILE				= $(LIBFT_DIR)libft.a

MLX_DIR					= ./lib/libmlx/
MLX_FLAGS				= -L./$(MLX_DIR) -lmlx -framework OpenGl -framework Appkit
MLX_FILE				= $(MLX_DIR)libmlx.a

INC_DIR_MAN				= ./include/mandatory
INC_DIR_BONUS			= ./include/bonus

SRCS_MAN_DIR			= ./src/mandatory/
SRCS_MAN_PARSE_DIR		= $(SRCS_MAN_DIR)parse/
SRCS_MAN_RENDER_DIR		= $(SRCS_MAN_DIR)render/

SRCS_MAN_PARSE			= $(addprefix $(SRCS_MAN_PARSE_DIR), \
				conf_lst.c\
				check_commas.c\
				fill_cy.c\
				fill_setting.c\
				fill_sph_pl.c\
				get_next_line.c\
				get_next_line_utils.c\
				obj_lst.c\
				parse_main.c\
				)

SRCS_MAN_RENDER			= $(addprefix $(SRCS_MAN_RENDER_DIR), \
				clone_rt.c\
				cam_hook.c\
				hook_minirt.c\
				img_util.c\
				init_struct.c\
				intersect_cy.c\
				intersect_cy_circle.c\
				intersect_pl.c\
				intersect_sph.c\
				phong_light.c\
				phong_util.c\
				ray_tracing.c\
				shadow.c\
				vect_ops.c\
				vect_util.c\
				view_transform.c\
				)

SRCS_MAN				= $(SRCS_MAN_DIR)main.c $(SRCS_MAN_PARSE) $(SRCS_MAN_RENDER)

SRCS_BONUS_DIR			= ./src/bonus/
SRCS_BONUS_PARSE_DIR	= $(SRCS_BONUS_DIR)parse/
SRCS_BONUS_RENDER_DIR	= $(SRCS_BONUS_DIR)render/

SRCS_BONUS_PARSE		= $(addprefix $(SRCS_BONUS_PARSE_DIR), \
				conf_lst_bonus.c\
				conf_to_spec_bonus.c\
				fill_ch_txt_bonus.c\
				fill_cy_bonus.c\
				fill_cone_bonus.c\
				fill_light_bonus.c\
				fill_setting_bonus.c\
				fill_sph_pl_bonus.c\
				get_next_line_bonus.c\
				get_next_line_utils_bonus.c\
				l_lst_bonus.c\
				obj_lst_bonus.c\
				parse_main_bonus.c\
				read_fill_ppm_bonus.c\
				trail_cons_split_bonus.c\
				txt_lst_bonus.c\
				txt_to_objs_bonus.c\
				)

SRCS_BONUS_RENDER		= $(addprefix $(SRCS_BONUS_RENDER_DIR), \
				apply_texture_bonus.c\
				clone_obj_lst_bonus.c\
				clone_rt_bonus.c\
				cam_hook_bonus.c\
				get_coord_sys_bonus.c\
				hook_minirt_bonus.c\
				img_util_bonus.c\
				init_struct_bonus.c\
				intersect_cy_bonus.c\
				intersect_cy_circle_bonus.c\
				intersect_cn_bonus.c\
				intersect_cn_circle_bonus.c\
				intersect_pl_bonus.c\
				intersect_sph_bonus.c\
				phong_light_bonus.c\
				phong_util_bonus.c\
				ray_tracing_bonus.c\
				shadow_bonus.c\
				shoot_ray_bonus.c\
				vect_ops_bonus.c\
				vect_util_bonus.c\
				view_transform_bonus.c\
				)

SRCS_BONUS				= $(SRCS_BONUS_DIR)main_bonus.c $(SRCS_BONUS_PARSE) $(SRCS_BONUS_RENDER)

OBJS_MAN				= ${SRCS_MAN:%.c=%.o}
OBJS_BONUS				= ${SRCS_BONUS:%.c=%.o}

ifdef WITH_BONUS
	OBJ_FILES	= $(OBJS_BONUS)
	INC_DIR		= $(INC_DIR_BONUS)
	COMPILE_MSG = @echo $(CUT)$(UP)$(BOLD)$(L_RED) 🌌 BONUS 🌠$(RESET)
else
	OBJ_FILES	= $(OBJS_MAN)
	INC_DIR		= $(INC_DIR_MAN)
	COMPILE_MSG = @echo $(CUT)$(UP)$(BOLD)$(L_PUPLE) 🌏 miniRT Compiled 🥳$(RESET)
endif

INC_DIR_LIBFT			= ./lib/libft/
INC_DIR_MLX				= ./lib/libmlx/

######################### Color #########################
GREEN="\033[32m"
L_GREEN="\033[1;32m"
YELLOW="\033[33m"
RED="\033[31m"
L_RED="\033[1;31m"
BLUE="\033[34m"
L_BLUE="\033[1;34m"
MUTED="\033[130m"
RESET="\033[0m"
BOLD="\033[1m"
L_PUPLE="\033[1;35m"
UP = "\033[A"
DOWN = "\033[B"
RIGHT = "\033[C"
LEFT = "\033[D"
CUT = "\033[K"
SAVE = "\033[s"
RESTORE = "\033[u"

########################## Rule ##########################

.PHONY			:	all
all				:	$(LIBFT_FILE) $(OBJ_FILES) $(NAME)

$(NAME)			: 	$(LIBFT_FILE) $(MLX_FILE) $(OBJ_FILES)
					@$(CC) $(CFLAGS) $(OBJ_FILES) $(RDLN_LFLAGS) $(RDLN_INC) $(LIBFT_FLAGS) $(MLX_FLAGS) -I$(INC_DIR) -o $@ 
					@printf $(CUT)$(DOWN)$(CUT)
					$(COMPILE_MSG)

.PHONY			:	bonus
bonus			:
					@make WITH_BONUS=1 all

%.o				: 	%.c
					@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(INC_DIR_LIBFT) -I$(INC_DIR_MLX) -c $< -o $@
					@echo $(CUT)$(BOLD)$(L_GREEN) Compiling with $(CFLAGS)...$(RESET)
					@echo $(CUT)$(GREEN) [$(notdir $^)] to [$(notdir $@)] $(RESET)
					@printf $(UP)$(UP)

$(LIBFT_FILE)	:
					@echo $(CUT)$(YELLOW) Get LIBFT 🏃 $(RESET)
					@make -C $(LIBFT_DIR) bonus

$(MLX_FILE)		:
					@echo $(CUT)$(YELLOW) Get LIBMLX 🏃 $(RESET)
					@make -C $(MLX_DIR) 

.PHONY			:	clean
clean			:
					@rm -f $(OBJS_MAN) $(OBJS_BONUS)
					@make -C $(LIBFT_DIR) clean
					@make -C $(MLX_DIR) clean
					@echo $(L_RED) Remove🧹 OBJ files in miniRT 👋 $(RESET)


.PHONY			:	fclean
fclean			:	clean
					@rm -f $(NAME)
					@make -C $(LIBFT_DIR) fclean
					@make -C $(MLX_DIR) fclean
					@echo $(RED) Remove🧹 $(NAME)🦪 $(RESET)


.PHONY			:	ffclean
ffclean			:	fclean
					@rm -rf $(NAME).dSYM
					@echo $(RED) Remove🧹 $(NAME).dSYM 🎉 $(RESET)

.PHONY			:	re
re				:	fclean all

.PHONY			:	debug
debug			: 
					@make -C $(LIBFT_DIR) DEBUG=1
					@make DEBUG=1
					@echo $(CUT)$(RED)$(BOLD) It\'s DEBUG TIME🤪$(RESET)

.PHONY			:	leaks
leaks			:
					@make -C $(LIBFT_DIR) LEAKS=1
					@make LEAKS=1
					@echo $(CUT)$(RED)$(BOLD) Is there Leaks?🚰$(RESET)

.PHONY			:	b_debug
b_debug			:
					@make -C $(LIBFT_DIR) DEBUG=1 WITH_BONUS=1
					@make DEBUG=1 WITH_BONUS=1
					@echo $(CUT)$(RED)$(BOLD) It\'s DEBUG TIME🤪$(RESET)

.PHONY			:	b_leaks
b_leaks			:
					@make -C $(LIBFT_DIR) LEAKS=1 WITH_BONUS=1
					@make LEAKS=1 WITH_BONUS=1
					@echo $(CUT)$(RED)$(BOLD) Is there Leaks?🚰$(RESET)