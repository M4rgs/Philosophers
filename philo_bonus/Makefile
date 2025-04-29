NAME_BONUS = philo_bonus

SRCS_BONUS = philo_bonus.c helper_fun_bonus.c init_args_bonus.c routine_bonus.c

CC = cc

HEADER_BONUS = philo_bonus.h

CFLAGS = -Wall -Wextra -Werror

OBJ_BONUS = $(SRCS_BONUS:.c=.o)

RM = rm -f

all: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)

%.o: %.c $(HEADER_BONUS) 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_BONUS)

fclean:	clean
	$(RM) $(NAME_BONUS)

re:	fclean all

.PHONY: clean