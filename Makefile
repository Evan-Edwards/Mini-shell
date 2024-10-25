# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eedwards <eedwards@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 13:17:22 by eedwards          #+#    #+#              #
#    Updated: 2024/10/25 13:36:27 by eedwards         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name and compiler
NAME = minishell
CC = cc -g

# Compiler and linker flags
CFLAGS = -Wall -Werror -Wextra -Ofast
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
	ex_cd.c \
	ex_cd2.c \
	ex_echo.c \
	ex_env.c \
	ex_export.c \
	ex_export2.c \
	ex_pwd.c \
	ex_unset.c \
	execute_commands.c \
	find_path.c \
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