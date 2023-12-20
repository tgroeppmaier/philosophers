CC=clang
CFLAGS = -Wall -Wextra -Werror -g# -fsanitize=thread -std=c11 -pthread -D_XOPEN_SOURCE=600
NAME = philo
SRC = main.c check_input.c initialize.c libft.c free.c start.c print_status.c
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

