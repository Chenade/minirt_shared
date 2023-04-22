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
# CFLAGS		+=	-O3
# CFLAGS		+=	-g -pg
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

SRCS_MAT	= 	math/math_cyl.c				\
				math/math_pl.c				\
				math/math_sp.c				\
				math/check_inside.c			\
				math/vectors_utils.c		\
				math/vectors_ops.c			\
				math/vectors_ops2.c			\

SRCS_UTI	=	utils/general.c				\
				utils/tools.c				\
				utils/helper.c				\

SRCS_PAR	=	parsing/setup.c				\
				parsing/init_env.c			\
				parsing/map_env.c			\
				parsing/init_obj.c			\
				parsing/map_obj.c			\
				parsing/parse.c				\

SRCS_MLX	=	graphic/mlx_setup.c			\
				graphic/keyboard_env.c		\
				graphic/keyboard_obj.c		\
				graphic/transla_rota.c		\
				graphic/collisions.c		\
				graphic/shadows.c			\
				graphic/shadow_tracing.c	\
				graphic/ray_tracing.c		\
				graphic/calculate_colors.c	\
	
SRCS_DIS	=	display/print_obj.c			\
				display/print_env.c			\
				display/draw_gui.c			\
				display/gui_env.c			\
				display/gui_obj.c			\

SRCS		=	$(SRCS_MAT)
SRCS		+=	$(SRCS_UTI)
SRCS		+=	$(SRCS_PAR)
SRCS		+=	$(SRCS_MLX)
SRCS		+=	$(SRCS_DIS)
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
