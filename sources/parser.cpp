/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:14:47 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/18 17:54:21 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"
#include "parser.hpp"

// the input is a list of tokens
// we should check this "stream" of tokens
// check if the each line corresponds to the syntactic grammar
// if so, then we should trigger the action
// 

// BESOIN de free tout a la fin

Parser::Parser(void) {}
Parser::Parser(const Parser & rhs)
{
	*this = rhs;
}
Parser::~Parser(void) {}
Parser & Parser::operator=(const Parser & rhs)
{
// TBD
}

Parser::Parser(std::list<struct token> tokenList)
	: _tokenList(tokenList)
{
	this->_parserizer();
}

/*
**	possible grammar sequence: [NL], [ACTION] [NL], [INSTR] [PARAM] [NL]
*/

void	Parser::_expect(tokenType type,
							std::list<struct token>::iterator it, 
							int rk)
{
	int i = -1;
	while (++i < rk)
	{
		if (it + i == this->_tokenList.end())
			throw // EXCEPTION_SYNTAX_GRAMMAR_ERROR;
	}
	if (type == (it + rk)->type)
		return ;
	throw // EXCEPTION_SYNTAX_GRAMMAR_ERROR;
}

void	Parser::_triggerAction(std::string & action)
{
	for (auto & e : this->_actionMap)
	{
		if (action.compare(e.first) == 0)
		{
			(e.second)();
			return ;
		}
	}
	throw // EXCEPTION_UNKNOWN_ACTION;
}

int		Parser::_getParameterType(std::string & str)
{
	for (auto & e : this->_operandTypeMap)
	{
		char *operandStr = e.first;
		if (str.compare(0, strlen(operandStr), operandStr) == 0)
			return (type = e.second);
	}
}

void	Parser::_triggerInstruction(std::string & instruction,
										std::string & wrappedParam)
{
	eOperandType operandType = this->_getParameterType(wrappedParam);

	size_t startSubstr = wrappedParam.find('(') + 1;
	size_t lenSubstr = wrappedParam.find(')') - start;
	std::string unwrappedParam = wrappedParam.substr(startSubstr, lenSubstr);

	for (auto & e : this->_instructionMap)
	{
		if (instruction.compare(e.first) == 0)
		{
			(e.second)(operandType, unwrappedParam);
			return ;
		}
	}
	throw // EXCEPTION_UNKNOWN_INSTRUCTION;
}

void	Parser::_parserizer(void)
{
	for (std::list<struct token>::iterator it = this->_tokenList.begin()
			; it != this->_tokenList.end() ; it++)
	{
		// try {} to surround all below errors ?
		if (it->type == tokenType::NL)
			continue ;
		else if (it->type == tokenType::ACTION)
		{
			expect(tokenType::NL, it, 1);
			this->_triggerAction(it->value);
			it += 1;
		}
		else if (it->type == tokenType::INSTR)
		{
			expect(tokenType::PARAM, it, 1);
			expect(tokenType::NL, it, 2);
			this->_triggerInstruction(it->value, (it + 1)->value);
			it += 2;
		}
		else
			throw // EXCEPTION_SYNTAX_GRAMMAR_ERROR;
	}
}








std::map<char*, commandFunction*>	Parser::_actionMap =
{
	{"pop", &Parser::_pop},
	{"dump", &Parser::_dump},
	{"add", &Parser::_add},
	{"sub", &Parser::_sub},
	{"mul", &Parser::_mul},
	{"div", &Parser::_div},
	{"mod", &Parser::_mod},
	{"print", &Parser::_print},
	{"exit", &Parser::_exit}
}

std::map<char*, commandFunction*>	Parser::_instructionMap =
{
	{"push", &Parser::_push},
	{"assert", &Parser::_assert}
}

std::map<char*, eOperandType>		Parser::_operandTypeMap =
{
	{"Int8", eOperandType::Int8},
	{"Int16", eOperandType::Int16},
	{"Int32", eOperandType::Int32},
	{"Float", eOperandType::Float},
	{"Double", eOperandType::Double}
}
