NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
CFILES = minishell.c lexer/token.c lexer/lexer.c lexer/lexer2.c \
	lexer/lexer3.c parsing/parsing.c free.c parsing/error.c parsing/heredoc.c\
	parsing/heredoc2.c parsing/parsing2.c parsing/parsing3.c \
    builtins/ft_echo.c builtins/ft_cd.c builtins/ft_pwd.c builtins/ft_export.c \
    builtins/ft_unset.c builtins/ft_env.c builtins/ft_exit.c execution/execution.c \
	execution/expand.c execution/execve.c signals.c builtins/ft_export2.c builtins/ft_unset2.c \
	execution/expand2.c execution/expand3.c execution/execve2.c execution/execution2.c \
	execution/execution3.c ini_libft/mini_libft.c ini_libft/mini_libft2.c ini_libft/mini_split.c \
	ini_libft/linkedlist.c  ini_libft/norme.c

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
