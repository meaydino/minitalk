# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meaydino <meaydino@student.42kocaeli.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/21 12:08:30 by meaydino          #+#    #+#              #
#    Updated: 2026/05/21 12:08:30 by meaydino         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_SERVER = server
NAME_CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_SERVER = server.c
SRC_CLIENT = client.c
SRC_SERVER_BONUS = server_bonus.c
SRC_CLIENT_BONUS = client_bonus.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER_BONUS = $(SRC_SERVER_BONUS:.c=.o)
OBJ_CLIENT_BONUS = $(SRC_CLIENT_BONUS:.c=.o)

all: $(LIBFT)
	@if [ -f .bonus ]; then \
		rm -f .bonus; \
		rm -f $(OBJ_SERVER_BONUS) $(OBJ_CLIENT_BONUS); \
		rm -f $(NAME_SERVER) $(NAME_CLIENT); \
	fi
	@$(MAKE) $(NAME_SERVER) $(NAME_CLIENT)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME_SERVER): $(OBJ_SERVER)
	$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJ_CLIENT)
	$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)

bonus: $(LIBFT)
	@if [ ! -f .bonus ]; then \
		rm -f $(OBJ_SERVER) $(OBJ_CLIENT); \
		rm -f $(NAME_SERVER) $(NAME_CLIENT); \
	fi
	@$(MAKE) .bonus

.bonus: $(OBJ_SERVER_BONUS) $(OBJ_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(OBJ_SERVER_BONUS) $(LIBFT) -o $(NAME_SERVER)
	$(CC) $(CFLAGS) $(OBJ_CLIENT_BONUS) $(LIBFT) -o $(NAME_CLIENT)
	@touch .bonus

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	rm -f $(OBJ_SERVER) $(OBJ_CLIENT) $(OBJ_SERVER_BONUS) $(OBJ_CLIENT_BONUS)
	rm -f .bonus

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME_SERVER) $(NAME_CLIENT)

re: fclean all

.PHONY: all clean fclean re bonus
