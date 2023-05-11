NAME			= pipex

NAME_BONUS		= pipex_bonus

SRCS 			= ./main.c \
					./check_input.c

SRCS_BONUS		= ./bonus/main.c \
					./bonus/check_input.c

LIBFT			=	libft.a

OBJS			=	${SRCS:.c=.o}

OBJS_BONUS		= ${SRCS_BONUS:.c=.o}

CFLAGS = -Wall -Werror -Wextra -g3

CC = cc

LIBRARIES		=	-Llibft -lft

INCLUDES		=	-I. -Ilibft

all				:	${NAME}

$(NAME): $(OBJS)
	@make -C libft
	${CC} ${CFLAGS} $(OBJS) $(INCLUDES) ${LIBRARIES} -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	@make -C libft
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(INCLUDES) ${LIBRARIES} -o $(NAME_BONUS)

clean			:
					make clean -C libft
					rm -rf ${OBJS} ${OBJS_BONUS}

fclean			:	clean
					make fclean -C libft
					rm -rf ${LIBFT}
					rm -rf ${NAME}
					rm -f $(NAME_BONUS)

re				:	fclean all

.PHONY			:	all clean fclean re bonus