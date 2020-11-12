# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darodrig <darodrig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/24 14:39:02 by darodrig          #+#    #+#              #
#    Updated: 2020/07/01 09:08:58 by darodrig         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c commands.c ft_exit.c ft_pwd.c ft_echo.c utils.c ft_env.c \
		ft_unset.c ft_export.c ft_cd.c utils2.c parse.c parse_redir.c \
		redirections.c commands2.c commands3.c path.c

OBJS = $(SRCS:.c=.o)

INC = srcs/libft/libft.a

NAME = minishell

all: $(NAME)

$(INC):
	Make -C srcs/libft

$(NAME): $(SRCS) $(INC)
	gcc -Wall -Wextra -Werror $(SRCS) $(INC) -o minishell

exec:
	make
	./minishell

clean:
	rm -f $(NAME)
	rm -f $(OBJS)
	Make clean -C srcs/libft

fclean: clean
	rm -f $(NAME) $(INC)



re:	fclean all

push: fclean
	git add $(SRCS)
	git add Makefile minishell.h
	git commit -m "30-6-20"
	git push origin master
