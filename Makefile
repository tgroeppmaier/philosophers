CC=clang
CFLAGS = -Wall -Wextra -Werror -g -pthread
NAME = philo
SRC = main.c check_input.c initialize.c libft.c free.c start.c getter_setter.c time.c supervisor.c
OBJ = $(SRC:.c=.o)
HEADER = philo.h

.PHONY: all fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re: fclean all

