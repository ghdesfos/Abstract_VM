/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_vm.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:47:04 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/18 19:11:05 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_VM_HPP
# define ABSTRACT_VM_HPP

#include <iostream>
#include <sstream>
#include <exception>
#include <cstdint>
#include <limits>
#include <regex>
#include <string>
#include <cstring>

enum eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double	
};

typedef IOperand const * createOperand( std::string const & value ) const;

std::array<createOperand*> create_operand
{
	&createInt8,
	&createInt16,
	&createInt32,
	&createFloat,
	&createDouble
};

typedef void	commandFunction(std::string const & str);

std::map<char*, commandFunction*> command_map =
{
	{"push", &cmd_push},
	{"pop", &cmd_pop},
	{"dump", &cmd_dump},
	{"assert", &cmd_assert},
	{"add", &cmd_add},
	{"sub", &cmd_sub},
	{"mul", &cmd_mul},
	{"div", &cmd_div},
	{"mod", &cmd_mod},
	{"print", &cmd_print},
	{"exit", &cmd_exit}
}


# define NB_OPERAND_TYPES	5
/*
typedef void	parseFct(void)

typedef struct	s_param
{
	char		*param_type;
	parseFct	*parse_function;
}				t_param;
*/

t_param		params[NB_OPERAND_TYPES]
{
	{"Int8", &parse_int},
	{"Int16", &parse_int},
	{"Int32", &parse_int},
	{"Float", &parse_double},
	{"Double", &parse_double}
}




enum tokenType
{
	ACTION, INSTR, PARAM, NL
};

struct token
{
	tokenType	type;
	std::string	value;
}

#endif
