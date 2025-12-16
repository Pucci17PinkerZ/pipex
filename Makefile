# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: your_login <your_login@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/01 00:00:00 by your_login       #+#    #+#              #
#    Updated: 2024/01/01 00:00:00 by your_login      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 COLORS                                       #
# **************************************************************************** #

RESET		= \033[0m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
MAGENTA		= \033[35m
CYAN		= \033[36m
RED			= \033[31m

# **************************************************************************** #
#                                 VARIABLES                                    #
# **************************************************************************** #

NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

# **************************************************************************** #
#                                 DIRECTORIES                                  #
# **************************************************************************** #

SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include

# **************************************************************************** #
#                                 SOURCE FILES                                 #
# **************************************************************************** #

SRC_FILES	= main.c \
			  pipex.c \
			  utils.c

SRC			= $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# **************************************************************************** #
#                                 BONUS FILES                                  #
# **************************************************************************** #

BONUS_FILES	= main_bonus.c \
			  pipex_bonus.c \
			  utils_bonus.c

BONUS_SRC	= $(addprefix $(SRC_DIR)/, $(BONUS_FILES))
BONUS_OBJ	= $(addprefix $(OBJ_DIR)/, $(BONUS_FILES:.c=.o))

# **************************************************************************** #
#                                   INCLUDES                                   #
# **************************************************************************** #

INCLUDES	= -I$(INC_DIR)

# **************************************************************************** #
#                                    RULES                                     #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(CYAN)Compiling $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compiled successfully!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

bonus: $(BONUS_OBJ)
	@echo "$(CYAN)Compiling $(NAME) with bonus...$(RESET)"
	@$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) bonus compiled successfully!$(RESET)"

clean:
	@echo "$(RED)Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@echo "$(GREEN)✓ Object files removed!$(RESET)"

fclean: clean
	@echo "$(RED)Removing $(NAME)...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(GREEN)✓ $(NAME) removed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
