NAME = philosophers

SRCS = philo.c helper_fun.c init_args.c routine.c

CC = cc

HEADER = philo.h

CFLAGS = -Wall #-Wextra -Werror #-fsanitize=thread

OBJ = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER) 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: clean

git:
	git add .
	git commit -m "Philosophers"
	git push