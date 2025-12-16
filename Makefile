CC = cc
LIBFT = libft.a
LIBFTDIR =
FLAGS = -Wall -Wextra -Werror
NAME = pipex
OBJ = $(SRC:.c=.o)
RM := rm -f
SRC = main.c\
parsing.c\
childs.c\
utils.c\

all: $(NAME)
	

$(NAME): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all


.PHONY: all clean fclean re