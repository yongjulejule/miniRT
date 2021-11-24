# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 14:49:19 by ghan              #+#    #+#              #
#    Updated: 2021/11/24 14:24:02 by ghan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc

ifdef DEBUG
	CFLAGS = -g3 -fsanitize=address -D BUFFER_SIZE=64 -D WIN_W=1920 -D WIN_H=1080
else ifdef LEAKS
	CFLAGS = -g -D BUFFER_SIZE=64 -D WIN_W=1920 -D WIN_H=1080
else 
	CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=64 -D WIN_W=1920 -D WIN_H=1080
endif

NAME			= miniRT

SRCS_DIR		= ./src/
SRCS_PARSE_DIR	= ./src/parse/
SRCS_RENDER_DIR	= ./src/render/

# TODO - Select a version of minilibx and declare LFAGS & INC

LIBFT_DIR		= ./lib/libft/
LIBFT_FLAGS		= -L./$(LIBFT_DIR) -lft
LIBFT_FILE		= $(LIBFT_DIR)libft.a

MLX_DIR			= ./lib/libmlx/
MLX_FLAGS		= -L./$(MLX_DIR) -lmlx -framework OpenGl -framework Appkit
MLX_FILE		= $(MLX_DIR)libmlx.a

INC_DIR_MAN		= ./include/

SRCS_PARSE		= $(addprefix $(SRCS_PARSE_DIR), \
				parse_main.c\
				conf_lst.c\
				obj_lst.c\
				fill_setting.c\
				fill_sph_pl.c\
				fill_cy.c\
				get_next_line.c\
				get_next_line_utils.c\
				)

SRCS_RENDER		= $(addprefix $(SRCS_RENDER_DIR), \
				create_cy_img.c\
				create_pl_img.c\
				create_sph_img.c\
				fill_img.c\
				img_util.c\
				init_struct.c\
				math_util.c\
				)

SRCS_MAN		= $(addprefix $(SRCS_DIR), \
				main.c\
				)

SRCS_MAN		+= $(SRCS_PARSE) $(SRCS_RENDER)

SRCS_BONUS		= $(addprefix $(SRCS_DIR_BONUS), \
				)

OBJS_MAN		= ${SRCS_MAN:%.c=%.o}
OBJS_BONUS		= ${SRCS_BONUS:%.c=%.o}
OBJ_FILES		= $(OBJS_MAN)

INC_DIR			= $(INC_DIR_MAN)
INC_DIR_LIBFT	= ./lib/libft/
INC_DIR_MLX		= ./lib/libmlx/

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
					@echo $(CUT)$(UP)$(BOLD)$(L_PUPLE) 🌏 miniRT Compiled 🥳$(RESET)

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

leaks			:
					@make -C $(LIBFT_DIR) LEAKS=1
					@make LEAKS=1
					@echo $(CUT)$(RED)$(BOLD) Is there Leaks?🚰$(RESET)