# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rimagalh <rimagalh@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/28 11:36:50 by rimagalh          #+#    #+#              #
#    Updated: 2025/06/11 18:31:45 by rimagalh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

NAME = minishell

SRC = src/main.c \
	src/commands/builtins/cd.c \
	src/commands/builtins/echo.c \
	src/commands/builtins/env.c \
	src/commands/builtins/exit.c \
	src/commands/builtins/pwd.c \
	src/commands/cmd_paths.c \
	src/commands/cmd.c \
	src/expansion/expansion.c \
	src/memory/cmd.c \
	src/memory/data.c \
	src/memory/free.c \
	src/memory/token.c \
	src/parsing/cmd.c \
	src/parsing/parsing.c \
	src/parsing/syntax.c \
	src/utils/strings.c \
	src/utils/builtins.c \
	src/utils/cmd.c \
	src/utils/env.c \
	src/utils/error.c \
	src/utils/parsing.c \
	src/utils/signal.c \

OBJ = $(SRC:.c=.o)

OBJ_DIR = objs
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS) $(LIBFT)

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re nof
