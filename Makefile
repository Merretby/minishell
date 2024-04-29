NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=address
CFILES = 
RFLAGS = -lreadline

OFILSE = $(CFILES:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OFILSE)
	$(CC) $(CFLAGS) $(OFILSE) $(RFLAGS) $(LIBFT) -o $(NAME)

$(LIBFT) :
	make -C libft

clean:
	rm -f $(OFILSE)
	make clean -C libft

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all