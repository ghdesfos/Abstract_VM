/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:14:47 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 19:51:52 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"
#include "parser.hpp"
#include "exceptions.hpp"

// the input is a list of tokens
// we should check this "stream" of tokens
// check if the each line corresponds to the syntactic grammar
// if so, then we should trigger the action
// 

// BESOIN de free tout a la fin

std::map<std::string, actionFct>	Parser::_actionMap =
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
};

std::map<std::string, instructionFct>	Parser::_instructionMap =
{
	{"push", &Parser::_push},
	{"assert", &Parser::_assert}
};

std::map<std::string, eOperandType>		Parser::_operandTypeMap =
{
	{"Int8", eOperandType::Int8},
	{"Int16", eOperandType::Int16},
	{"Int32", eOperandType::Int32},
	{"Float", eOperandType::Float},
	{"Double", eOperandType::Double}
};

Parser::Parser(void) {}
Parser::Parser(const Parser & rhs)
{
	*this = rhs;
}
Parser::~Parser(void) {}
Parser & Parser::operator=(const Parser & rhs)
{
	this->_tokenList = rhs._tokenList;
	this->_stack = rhs._stack;
	return (*this);
}

Parser::Parser(std::list<struct token> tokenList)
	: _tokenList(tokenList)
{
	this->_parserizer();
}

/*
**	possible grammar sequence: [NL], [ACTION] [NL], [INSTR] [PARAM] [NL]
*/

void			Parser::_expect(tokenType type,
							std::list<struct token>::iterator it)
{
	if (it == this->_tokenList.end())
		throw SyntaxGrammarError();
	if (type == it->type)
		return ;
	throw SyntaxGrammarError();
}

void			Parser::_triggerAction(std::string & action)
{
	for (auto & e : this->_actionMap)
	{
		if (action.compare(e.first) == 0)
		{
			(this->*(e.second))();
			return ;
		}
	}
	throw UnknownAction();
}

eOperandType	Parser::_getParameterType(std::string & str)
{
	for (auto & e : this->_operandTypeMap)
	{
		std::string operandStr = e.first;
		if (str.compare(0, operandStr.length(), operandStr) == 0)
			return (e.second);
	}
	throw UnknownType();
}

void			Parser::_triggerInstruction(std::string & instruction,
										std::string & wrappedParam)
{
	eOperandType operandType = this->_getParameterType(wrappedParam);

	size_t startSubstr = wrappedParam.find('(') + 1;
	size_t lenSubstr = wrappedParam.find(')') - startSubstr;
	std::string unwrappedParam = wrappedParam.substr(startSubstr, lenSubstr);

	for (auto & e : this->_instructionMap)
	{
		if (instruction.compare(e.first) == 0)
		{
			(this->*(e.second))(operandType, unwrappedParam);
			return ;
		}
	}
	throw UnknownInstruction();
}

void			Parser::_parserizer(void)
{
	for (std::list<struct token>::iterator it = this->_tokenList.begin()
			; it != this->_tokenList.end() ; it++)
	{
		// try {} to surround all below errors ?
		if (it->type == tokenType::NL)
			continue ;
		else if (it->type == tokenType::ACTION)
		{
			auto currIt = it;
			auto nextIt = ++it;
			this->_expect(tokenType::NL, nextIt);
			this->_triggerAction(currIt->value);
		}
		else if (it->type == tokenType::INSTR)
		{
			auto currIt = it;
			auto nextIt = ++it;
			auto nextNextIt = ++it;
			this->_expect(tokenType::PARAM, nextIt);
			this->_expect(tokenType::NL, nextNextIt);
			this->_triggerInstruction(currIt->value, nextIt->value);
		}
		else
			throw SyntaxGrammarError();
	}
}
