CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
NAME = pipex
SRC_M = $(wildcard ./SRC/*.c)
SRC_B = $(wildcard ./SRC_BONUS/*.c)
INC = -I ./INCLUDES
LIB = ./libft/libft.a

all: $(NAME)

$(NAME): $(SRC_M)
	make -C libft
	$(CC) $(CFLAGS) $(INC) $(SRC_M) $(LIB) -o $@
bonus: $(SRC_B)
	make -C libft
	$(CC) $(CFLAGS) $(INC) $(SRC_B) $(LIB) -o $(NAME)
clean:
		make clean -C libft

fclean: clean
		$(RM) $(LIB)
		$(RM) $(NAME)

re: fclean all