# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/15 14:49:19 by ghan              #+#    #+#              #
#    Updated: 2021/11/16 16:10:51 by ghan             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= gcc

ifdef DEBUG
	CFLAGS = -g3 -fsanitize=address -D BUFFER_SIZE=64
else ifdef LEAKS
	CFLAGS = -g -D BUFFER_SIZE=64
else 
	CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=64
endif

NAME			= miniRT

SRCS_DIR		= ./src/
SRCS_PARSE_DIR	= ./src/parse/

# TODO - Select a version of minilibx and declare LFAGS & INC

LIB_DIR			= ./lib/
LIBFT_DIR		= $(LIB_DIR)libft/
LIBFT_FLAGS		= -L./$(LIBFT_DIR) -lft
LIBFT_FILE		= $(LIBFT_DIR)libft.a

INC_DIR_MAN		= ./include/

SRCS_PARSE		= $(addprefix $(SRCS_PARSE_DIR), \
				parse_main.c\
				conf_lst.c\
				get_next_line.c\
				get_next_line_utils.c\
				)

SRCS_MAN		= $(addprefix $(SRCS_DIR), \
				main.c\
				)

SRCS_MAN		+= $(SRCS_PARSE)

SRCS_BONUS		= $(addprefix $(SRCS_DIR_BONUS), \
				)

OBJS_MAN		= ${SRCS_MAN:%.c=%.o}
OBJS_BONUS		= ${SRCS_BONUS:%.c=%.o}
OBJ_FILES		= $(OBJS_MAN)

INC_DIR			= $(INC_DIR_MAN)
INC_DIR_LIBFT	= ./lib/libft/

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

$(NAME)			: 	$(LIBFT_FILE) $(OBJ_FILES)
					@$(CC) $(CFLAGS) $(OBJ_FILES) $(RDLN_LFLAGS) $(RDLN_INC) $(LIBFT_FLAGS) -I$(INC_DIR) -o $@ 
					@printf $(CUT)$(DOWN)$(CUT)
					@echo $(CUT)$(UP)$(BOLD)$(L_PUPLE) 🌏 miniRT Compiled 🥳$(RESET)

%.o				: 	%.c
					@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(INC_DIR_LIBFT) -c $< -o $@
					@echo $(CUT)$(BOLD)$(L_GREEN) Compiling with $(CFLAGS)...$(RESET)
					@echo $(CUT)$(GREEN) [$(notdir $^)] to [$(notdir $@)] $(RESET)
					@printf $(UP)$(UP)

$(LIBFT_FILE)	:
					@echo $(CUT)$(YELLOW) Get Library 🏃 $(RESET)
					@make -C $(LIBFT_DIR) bonus

.PHONY			:	clean
clean			:
					@rm -f $(OBJS_MAN) $(OBJS_BONUS)
					@make -C $(LIBFT_DIR) clean
					@echo $(L_RED) Remove🧹 OBJ files in miniRT 👋 $(RESET)


.PHONY			:	fclean
fclean			:	clean
					@rm -f $(NAME)
					@make -C $(LIBFT_DIR) fclean
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