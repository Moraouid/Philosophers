NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = philo.c parssing.c philo_status.c philo_utils_1.c philo_utils_2.c philo_thread.c philo_check.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SECONDARY: $(OBJS)

.PHONY: all clean fclean re
