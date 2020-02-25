# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/08 13:28:43 by ghdesfos          #+#    #+#              #
#    Updated: 2020/02/08 13:42:34 by ghdesfos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= abstract_vm

CC			= g++
CFLAGS		= -Wall -Wextra -Werror
RM			= /bin/rm -rf

INCLUDES	= -I includes/

HEADERS		= includes/abstract_vm.h

FUNCTIONS	= abstract_vm.cpp\
			
FILES		= $(addprefix sources/, $(FUNCTIONS))
OBJECTS		= $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $@

g: $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $@ -g

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJECTS)
	$(RM) *.gch
	$(RM) *.dSYM

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
