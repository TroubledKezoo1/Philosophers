NAME = philo
CC = cc -Wall -Wextra -Werror #-fsanitize=thread
SOURCE = free.c \
		ft_split.c \
		initialize.c \
		main.c \
		thread_utils.c \
		thread.c \
		time.c \
		utils.c
OBJ = $(SOURCE:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
all : $(NAME)

.c.o:
	$(CC) -c -o $@ $<

clean:
	@rm -rf *.o
fclean: clean
	@rm -rf $(NAME)
re: fclean all

.PHONY: re fclean clean all