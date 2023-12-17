CC=clang
CFLAGS = -Wall -Wextra -Werror -g
NAME = philo
SRC = main.c input_check.c
OBJ = $(SRC:.c=.o)

.PHONY: all fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

