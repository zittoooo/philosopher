NAME =  philo_three
SRC	 =  main.c \
		create_philo.c \
		philo.c \
		utils.c

OBJ  = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	clang++ -Wall -Wextra -Werror $^ -o $@ 

%.o : %.cpp
	clang++ -Wall -Wextra -Werror -c $<

re : fclean all

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)
