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

FUNCTIONS	= abstract_vm.cpp\
				operand_factory.cpp\
				lexer.cpp\
				parser.cpp\
				parser_commands.cpp\
				exceptions.cpp
			
FILES		= $(addprefix sources/, $(FUNCTIONS))
OBJECTS		= $(FILES:.cpp=.o)
DEPS		= $(OBJECTS:%.o=%.d)

GREEN		= \x1b[32m
RED			= \x1b[31m
COLOR_END	= \x1b[0m

all: $(DEPS) $(NAME)

$(NAME): $(OBJECTS)
	@printf "$(GREEN)Linking into:$(COLOR_END) %s\n" $@
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $@

$(DEPS):
	@touch $@

-include $(DEPS)

g: $(OBJECTS)
	@echo "Linking"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJECTS) -o $@ -g

%.o: %.cpp
	@printf "$(GREEN)Creating object file:$(COLOR_END) %s\n" $@
	@$(CC) $(CFLAGS) -MMD $(INCLUDES) -c $< -o $@

clean:
	@echo "$(RED)Cleaning objects$(COLOR_END)"
	@$(RM) $(OBJECTS)
	@echo "$(RED)Cleaning dependencies$(COLOR_END)"
	@$(RM) $(DEPS)
	@$(RM) *.gch
	@$(RM) *.dSYM

fclean: clean
	@printf "$(RED)Cleaning executable:$(COLOR_END) %s\n" "$(NAME)"
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
