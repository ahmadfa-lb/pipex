NAME = libftprintf.a



SRCS =  ft_printf.c  ft_printf_u.c ft_printf_p.c\
		ft_printf_c.c ft_printf_hex.c  ft_printf_d.c ft_printf_s.c 

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	cp libft/libft.a $(NAME) 
	ar -rcs $(NAME) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean:	clean
	make -C libft fclean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re