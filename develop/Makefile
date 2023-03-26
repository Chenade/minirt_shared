###############################################################################
#                                                                             #
#                              Basic Config                                   #
#                                                                             #
###############################################################################

NAME		=	rt

RM			=	rm -rf

CC			=	cc

CFLAGS		=	-Wall -Werror -Wextra 
CFLAGS		+=	-Ofast -flto
CFLAGS		+=	-I $(INCS_DIR) -I $(LIBFT_DIR) -I ${MLX_DIR}
CFLAGS		+=	-g3 -MMD

LFLAGS		= 	-L . -lmlx_Linux -lX11 -lXext -lm

CLIBS		=	-L . -lft

Y			= "\033[33m"
R			= "\033[31m"
GREEN		= "\033[92m"
BLUE		= "\033[94m"
X			= "\033[0m"
UP			= "\033[A"
CUT			= "\033[K"

###############################################################################
#                                                                             #
#                               Libs Config                                   #
#                                                                             #
###############################################################################

LIBFT		=	libft.a

LIBMLX		=	libmlx.a

LIBMLX_2	=	libmlx_Linux.a

LIBS_DIR	=	libs

LIBFT_DIR	=	$(LIBS_DIR)/libft

MLX_DIR		=	$(LIBS_DIR)/minilibx-linux

###############################################################################
#                                                                             #
#                                  Variable                                   #
#                                                                             #
###############################################################################

SRCS_DIR	=	srcs

INCS_DIR	=	incs

OBJS_DIR	=	objs

SRCS_GEN	=	utils/general.c			\
				utils/tools.c			\
				utils/math_sp.c			\
				utils/math_pl.c			\
				utils/vectors.c			\
				utils/helper.c			\


SRCS_PAR	=	parsing/setup.c			\
				parsing/map_checker.c	\
				parsing/parse.c

SRCS_MLX	=	graphic/mlx_setup.c		\
				graphic/keyboard.c		\
				graphic/collision.c		\
				graphic/ray_tracing.c	\
				graphic/draw_gui.c

SRCS		=	$(SRCS_GEN)
SRCS		+=	$(SRCS_PAR)
SRCS		+=	$(SRCS_MLX)
SRCS		+=	main.c

OBJS		=	$(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

###############################################################################
#                                                                             #
#                                   COMMAND                                   #
#                                                                             #
###############################################################################

all:			$(NAME)

norminette:
				@echo ${Y}"\n=====Libft norminette check!====="${X}
				norminette $(LIBS_DIR)/libft
				@echo ${GREEN}"=====Libft norminette check Successfully!=====\n"${X}
				@echo ${Y}"\n=====miniRT norminette check!====="${X}
				norminette $(SRCS_DIR)
				norminette $(INCS_DIR)
				@echo ${GREEN}"=====miniRT norminette check Successfully!=====\n"${X}

$(LIBFT):
				@echo ${Y}"\n=====Libft Compiling!====="${X}
				@$(MAKE) -C $(LIBFT_DIR) all
				mv $(LIBFT_DIR)/$(LIBFT) .
				$(MAKE) -C $(LIBFT_DIR) fclean
				@echo ${GREEN}"=====Libft Compile Successfully=====\n"${X}

$(LIBMLX):
				@echo ${Y}"\n=====Libmlx Compiling!====="${X}
				make -C ${MLX_DIR} all
				mv $(MLX_DIR)/$(LIBMLX) .
				mv $(MLX_DIR)/$(LIBMLX_2) .
				make clean -C ${MLX_DIR}
				@echo ${GREEN}"=====Libmlx Compile Successfully=====\n"${X}


$(NAME):		$(LIBFT) $(LIBMLX) $(OBJS)
				${CC} ${OBJS} ${CFLAGS} ${LFLAGS} $(LIBFT) -o $@
				@echo ${GREEN}"miniRT Compile Successfully"${X}
				@echo ${BLUE}"Command: ./rt {filename}.rt\n"${X}

project:		clean $(OBJS)
				${CC} ${OBJS} ${CFLAGS} ${LFLAGS} $(LIBFT) -o $(NAME)
				@echo ${GREEN}"miniRT Compile Successfully"${X}
				@echo ${BLUE}"Command: ./rt {filename}.rt\n"${X}

$(OBJS_DIR)/%.o:$(SRCS_DIR)/%.c
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS_DIR)

fclean:			clean
				$(RM) $(LIBFT) $(LIBMLX) $(LIBMLX_2)
				@echo ${GREEN}"Lib Clean Successfully\n"${X}
				$(RM) $(NAME)
				@echo ${GREEN}"miniRT Clean Successfully\n"${X}

re:				fclean all

.PHONY:			all clean fclean re project norminette
