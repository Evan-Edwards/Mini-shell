# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 13:17:22 by eedwards          #+#    #+#              #
#    Updated: 2024/10/21 11:51:16 by eedwards         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name and compiler
NAME = minishell
CC = cc -g

# Compiler and linker flags
CFLAGS = -Wall -Werror -Wextra -Ofast
LFLAGS = -L./$(LIB1) -l$(LIB1_NAME) -L./$(LIB2) -l$(LIB2_NAME)

# Libraries
LIB1 = lib1_directory
LIB1_NAME = lib1_name
LIB2 = lib2_directory
LIB2_NAME = lib2_name

# Directories
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = incl

# Include paths
INC = -I./$(LIB1) -I./$(LIB2) -I./$(INC_DIR)

# Source files
SOURCES = create_tokens.c \
	replace_env.c \


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