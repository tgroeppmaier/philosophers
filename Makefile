CC=clang
CFLAGS = -Wall -Wextra -Werror -g
NAME = philo
SRC = main.c check_input.c parse_input.c initialize.c
OBJ = $(SRC:.c=.o)
HEADER = philo.h

.PHONY: all fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ): $(HEADER)
	
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

