#
#

NOM=libmlx.a
SRC= mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
SRC+= mlx_png.c mlx_mouse.m
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CC=gcc
CFLAGS+=-O2 -w -Wall -Werror -Wextra

# add to match string put with X11 in size and position
CFLAGS+= -DSTRINGPUTX11

######################### Color #########################
GREEN="\033[32m"
L_GREEN="\033[1;32m"
YELLOW="\033[33m"
RED="\033[31m"
L_RED="\033[1;31m"
BLUE="\033[34m"
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

%.o		: %.m
		@$(COMPILE.m) $(OUTPUT_OPTION) $<

%.o		: %.c
		@$(CC) $(CFLAGS) -c $< -o $@
		@echo $(SAVE)$(CUT)$(BOLD)$(L_GREEN) Compiling with $(CFLAGS)...$(RESET)
		@echo $(CUT) $(GREEN)[$^] to [$@] $(RESET)
		@printf $(UP)$(UP)

all		: $(NOM)


$(NOM)	: $(OBJ)
		@ar -cr $(NOM) $(OBJ)
		@ranlib $(NOM)
		@echo $(CUT)$(BOLD)$(L_PUPLE) ✨$(NAME) libmlx.a linked!!📚$(RESET)

clean	:
		@rm -f $(OBJ) *~
		@rm -f mlx_app
		@echo $(L_RED) Remove OBJ files in libmlx 👋 $(RESET)

fclean	: clean
		@rm -f $(NOM)
		@echo $(RED) Remove $(NOM) 🔥 $(RESET)

re		: fclean all

.phony	: all clean fclean re
