NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CFILES = minishell.c lexer/token.c linkedlist.c lexer/lexer.c lexer/lexer2.c \
    parsing/parsing.c free.c init.c parsing/error.c parsing/heredoc.c\
    builtins/ft_echo.c builtins/ft_cd.c builtins/ft_pwd.c builtins/ft_export.c \
    builtins/ft_unset.c builtins/ft_env.c builtins/ft_exit.c execution.c \
	expand.c execution/execve.c signals.c 
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

push :
	@make fclean
	@git add .
	@git commit -m "working norme"
	@git push -f
