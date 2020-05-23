# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/08 13:28:43 by ghdesfos          #+#    #+#              #
#    Updated: 2020/02/24 20:10:01 by ghdesfos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= abstract_vm

CC			= g++
CFLAGS		= -Wall -Wextra -Werror -std=c++11
RM			= /bin/rm -rf

INCLUDES	= -I includes/

HEADERS		= includes/abstract_vm.h

FUNCTIONS	= abstract_vm.cpp\
				operands.cpp\
				operand_factory.cpp\
				lexer.cpp\
				parser.cpp\
				parser_commands.cpp\
				exceptions.cpp
			
FILES		= $(addprefix sources/, $(FUNCTIONS))
OBJECTS		= $(FILES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $@

g: $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $@ -g

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(HEADERS):

clean:
	$(RM) $(OBJECTS)
	$(RM) *.gch
	$(RM) *.dSYM

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
