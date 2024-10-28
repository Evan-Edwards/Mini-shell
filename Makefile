# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 13:17:22 by eedwards          #+#    #+#              #
#    Updated: 2024/10/28 17:35:36 by eedwards         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name and compiler
NAME = minishell
CC = cc -g

# Compiler and linker flags
CFLAGS = -Wall -Wextra -Ofast
LFLAGS = -L./$(LIBFT) -lft -lreadline

# Libraries
LIBFT = libft
LIBFTA = libft.a

# Directories
OBJ_DIR = obj
SRC_DIR = src
INC_DIR = incl

# Include paths
INC = -I./libft/incl -I./$(INC_DIR)

# Source files
SOURCES = close.c \
	distribute.c \
	distribute2.c \
	ex_cd.c \
	ex_cd2.c \
	ex_echo.c \
	ex_env.c \
	ex_exit.c \
	ex_export_arg.c \
	ex_export.c \
	ex_export2.c \
	ex_history.c \
	ex_pwd.c \
	ex_unset.c \
	execute_commands.c \
	file_handling.c \
	find_path.c \
	free.c \
	history.c \
	main.c \
	path.c \
	path2.c \
	set_types.c \
	signals.c \
	tok_env_exp.c \
	tok_lst.c \
	tok_main.c \
	tok_quotes.c \
	tok_utils.c \

# Object files
SRCS = $(addprefix $(SRC_DIR)/, $(SOURCES))
OBJS = $(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

# Rules
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS)

clean:
	$(RM) $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re

# Test files
TEST_DIR = tests
TEST_SRC = test_env_expansion.c
TEST_OBJ = $(addprefix $(OBJ_DIR)/, $(TEST_SRC:.c=.o))
TEST_NAME = test_env

# Add test object compilation rule
$(OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# New test targets
test: $(TEST_NAME)
	./$(TEST_NAME)

$(TEST_NAME): $(filter-out $(OBJ_DIR)/main.o, $(OBJS)) $(TEST_OBJ)
	@make -C $(LIBFT)
	$(CC) $(CFLAGS) -o $(TEST_NAME) $^ $(LFLAGS)

test_clean: fclean
	$(RM) $(TEST_NAME)

.PHONY: all clean fclean re test test_clean
