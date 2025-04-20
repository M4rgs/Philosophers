NAME = philo
NAME_BONUS = philo_bonus

SRCS = Mandatory/philo.c Mandatory/helper_fun.c Mandatory/init_args.c Mandatory/routine.c Mandatory/death_checker.c
SRCS_BONUS = Bonus/philo_bonus.c Bonus/helper_fun_bonus.c Bonus/init_args_bonus.c

CC = cc

HEADER = Mandatory/philo.h
HEADER_BONUS = Bonus/philo_bonus.h

CFLAGS = -Wall -Wextra -Werror -g
OBJ = $(SRCS:.c=.o)
OBJ_BONUS = $(SRCS_BONUS:.c=.o)

RM = rm -f

all: $(NAME)
bonus: $(NAME_BONUS)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)

Mandatory/%.o: Mandatory/%.c $(HEADER) 
	$(CC) $(CFLAGS) -c $< -o $@

Bonus/%.o: Bonus/%.c $(HEADER_BONUS) 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)

fclean:	clean
	$(RM) $(NAME) $(NAME_BONUS)

re:	fclean all

.PHONY: clean

git:
	git add .
	git commit -m "Philosophers"
	git push