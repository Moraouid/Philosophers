NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror 


SRCS = philo.c parssing.c philo_status.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)


re: fclean all
 
.PHONY: all clean fclean re