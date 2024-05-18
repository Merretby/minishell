NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CFILES = minishell.c lexer/token.c linkedlist.c lexer/lexer.c lexer/lexer2.c \
	parsing/parsing.c free.c init.c parsing/error.c
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