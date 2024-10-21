# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 13:17:22 by eedwards          #+#    #+#              #
#    Updated: 2024/10/21 15:00:41 by eedwards         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name and compiler
NAME = minishell
CC = cc -g

# Compiler and linker flags
CFLAGS = -Wall -Werror -Wextra -Ofast
LFLAGS = -L./$(LIB1) -l$(LIB1_NAME) -L./$(LIB2) -l$(LIB2_NAME)

# Libraries
LIB1 = libft
LIB1_NAME = libft.a
LIB2 = lib2_directory
LIB2_NAME = lib2_name

# Directories
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = incl

# Include paths
INC = -I./libft/incl -I./$(LIB2) -I./$(INC_DIR)

# Source files
SOURCES = close.c \
	create_tokens.c \
	ms_main.c \
	replace_env.c \
	signals.c \
	token_utils.c \
	token_utils2.c \


# Object files
SRCS = $(addprefix $(SRC_DIR)/, $(SOURCES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

# Rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIB1)
	@make -C $(LIB2)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS)

clean:
	$(RM) $(OBJS)
	@make -C $(LIB1) clean
	@make -C $(LIB2) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIB1) fclean
	make -C $(LIB2) fclean

re: fclean all

.PHONY: all clean fclean re