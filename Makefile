CC = cc
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a
FTPRINTFDIR = ft_printf
FTPRINTF = $(FTPRINTFDIR)/libftprintf.a
CFLAGS = -g -Wall -Wextra -Werror
NAME = pipex
OBJ = $(SRC:.c=.o)
INCLUDES = -I $(LIBFTDIR) -I $(FTPRINTFDIR)
RM := rm -f
SRC = main.c\
parsing.c\
childs.c\
utils.c\

all: $(NAME)
	
$(NAME): $(OBJ) $(LIBFT) $(FTPRINTF)
	$(CC) $(CFLAGS) $^ -o $@
$(LIBFT):
	@make -C $(LIBFTDIR) --no-print-directory
$(FTPRINTF):
	@make -C $(FTPRINTFDIR) --no-print-directory
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
clean:
	@$(RM) $(OBJ)
	@make clean -C $(LIBFTDIR) --no-print-directory
	@make clean -C $(FTPRINTFDIR) --no-print-directory
fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFTDIR) --no-print-directory
	@make fclean -C $(FTPRINTFDIR) --no-print-directory
re: fclean all


.PHONY: all clean fclean re