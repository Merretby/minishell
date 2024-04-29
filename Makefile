NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=address
MLX_FLAG = -lmlx_Linux -includes_mlx/Lminilibx-linux  -lXext -lX11 -lm -lz
CFILES = so_long.c get_next_line.c get_next_line_utilis.c utiles.c error.c parsing.c\
	moves.c parsing1.c textu.c
BFILES = 

OFILSE = $(CFILES:.c=.o)
PRINTF = printf/libftprintf.a

all: $(NAME)

$(NAME): $(PRINTF) $(OFILSE)
	$(CC) $(CFLAGS) $(OFILSE) $(PRINTF) $(MLX_FLAG) -o $(NAME)

$(PRINTF) :
	make -C printf

clean:
	rm -f $(OFILSE)
	make clean -C printf

fclean: clean
	rm -f $(NAME)
	make fclean -C printf

re: fclean all