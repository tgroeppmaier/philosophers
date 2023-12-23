CC=clang
CFLAGS = -Wall -Wextra -Werror -g -pthread
TSANFLAGS = -fsanitize=thread
NAME = philo
SRC = main.c check_input.c initialize.c libft.c free.c start.c getter_setter.c time.c supervisor.c
OBJ = $(SRC:.c=.o)
HEADER = philo.h

.PHONY: all fclean re tsan

all: $(NAME)

tsan: CFLAGS += $(TSANFLAGS)
tsan: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) 

fclean: clean
	rm -f $(NAME)

re: fclean all