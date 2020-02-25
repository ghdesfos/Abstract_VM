/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_vm.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 20:08:36 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/17 19:30:42 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"

void	err_exit(int error_nb, char *error_message)
{
	std::cerr << error_message << std::endl;
	exit(error_nb);
}

void	skip_spaces(std::string str, int *rk)
{
	while (str[*rk] == ' ')
		*rk += 1;
}

int		check_valid_parameter(std::string &str, int *rk, int cmd, IOperand **op)
{
	int type;

	if ()
	if (str[*rk] != ' ')
		err_exit(-2, "missing space between command and parameter")
	skip_spaces(str, rk);
	for (type = 0 ; type < NB_OPERAND_TYPES ; type++)
	{
		char *type_str = params[type].param_type;
		if (str.compare(*rk, strlen(type_str), type_str) == 0)
		{
			*rk += 
		}
	}
	return (0);
}

// go through the list of instruc
// il faut un tableau avec les differentes commandes

int		check_valid_command(std::string &str, int *rk)
{
	int cmd_nb;

	for (cmd_nb = 0 ; cmd_nb < NB_COMMANDS ; cmd_nb++)
	{
		char *cmd_str = commands[cmd_nb].cmd_str;
		if (str.compare(*rk, strlen(cmd_str), cmd_str) == 0)
		{
			*rk += strlen(cmd_str);
			return (cmd_nb);
		}
	}
	return (-1);
}

void	parse_line(str, std::vector<double> &stack)
{
	int	rk = 0;
	IOperand *op;

	skip_spaces(str, &rk);
	// ONLY in the case of standard_input
	// CHECK exactly what we are supposed to do in this case
	if (str[rk] == 0)
		return ;
	// SHOULD WE FREE SOMETHING HERE?
	else if (str[rk] == ';' && str[rk + 1] == ';')
		exit(0);
	else if (str[rk] == ';')
		return ;
	// CHECK that we have one of the instruction that we want
	else if ((cmd = check_valid_command(str, &rk)) != -1
				&& check_valid_parameter(str, &rk, cmd, &op) != 0)
		execute_command(cmd, op);
}

void	parse_standard_input(void)
{
	while ()
	{
		
	}
}

void	parse_file_input(char *s, std::vector<double> &stack)
{
	std::ifstream in(s);

	if (!in)
		err_exit(-1, "you need to enter a valid file name");
	std::string str;
	while (1)
	{
		getline(in, str);
		if (in.eof())
			break ;
		parse_line(str, stack);
	}
}

// A PRIORI pas besoin de separer les deux cas en deux fonctions distinctes, \
// il suffit de passer le stream avec un pointer d'une classe parente commune.

void	parse_input(int argc, char **argv, std::vector<double> &stack)
{
	if (argc < 2)
		parse_standard_input(stack);
	else
		parse_file_input(argv[1], stack);
}

int		main(int argc, char **argv)
{
	std::vector<double> stack;

	parse_input(argc, argv, stack);
	return (0);
}
