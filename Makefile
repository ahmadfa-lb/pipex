NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror

FT_PRINTF_LIB = ft_printf/libftprintf.a
FT_PRINTF = ft_printf
SRCS = pipex.c utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(FT_PRINTF)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(FT_PRINTF_LIB)

clean:
	make -C $(FT_PRINTF) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(FT_PRINTF) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
