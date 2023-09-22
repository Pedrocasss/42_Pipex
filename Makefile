# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/14 20:59:50 by psoares-          #+#    #+#              #
#    Updated: 2023/09/22 12:54:17 by psoares-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC =  	main.c \
		split.c \
		split_utils.c \
		args.c \
		exec.c \
		libft_func.c \

B_SRC = 	get_next_line_bonus.c \
			main_bonus.c \
			args_bonus.c \
			exec_bonus.c \
			libft_func_bonus.c \
			split_bonus.c \
			split_utils_bonus.c \
			here_doc_bonus.c
			
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -I mandatory/
OBJS = $(addprefix mandatory/, $(SRC:.c=.o))
B_OBJS = $(addprefix bonus/, $(B_SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

bonus: $(B_OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(B_OBJS)

clean:
	$(RM) $(OBJS) $(B_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
