/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:14:47 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 20:45:16 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"
#include "parser.hpp"
#include "operand_template.hpp"
#include "exceptions.hpp"

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
	{"exit", &Parser::_exit},
	{"b_min", &Parser::_b_min},
	{"b_max", &Parser::_b_max},
	{"b_avg", &Parser::_b_avg},
	{"b_tokens", &Parser::_b_tokens},
	{"b_stack", &Parser::_b_stack}
};

std::map<std::string, instructionFct>	Parser::_instructionMap =
{
	{"push", &Parser::_push},
	{"assert", &Parser::_assert}
};

std::map<std::string, eOperandType>		Parser::_operandTypeMap =
{
	{"int8", eOperandType::Int8},
	{"int16", eOperandType::Int16},
	{"int32", eOperandType::Int32},
	{"float", eOperandType::Float},
	{"double", eOperandType::Double}
};

/*
**	Class methods
*/

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

/*
**	possible grammar sequence: [NL], [ACTION] [NL], [INSTR] [PARAM] [NL]
*/

void			Parser::_expect(tokenType type,
								std::list<struct token *>::iterator it)
{
	if (it == this->_tokenList.end())
		throw SyntaxGrammarError();
	if (type == (*it)->type)
		return ;
	throw SyntaxGrammarError();
}

void			Parser::_parserizer(void)
{
	for (std::list<struct token *>::iterator it = this->_tokenList.begin()
			; it != this->_tokenList.end() ; it++)
	{
		try
		{
			if ((*it)->type == tokenType::NL)
				continue ;
			else if ((*it)->type == tokenType::ACTION)
			{
				auto currIt = it;
				auto nextIt = ++it;
				this->_expect(tokenType::NL, nextIt);
				this->_triggerAction((*currIt)->value);
			}
			else if ((*it)->type == tokenType::INSTR)
			{
				auto currIt = it;
				auto nextIt = ++it;
				auto nextNextIt = ++it;
				this->_expect(tokenType::PARAM, nextIt);
				this->_expect(tokenType::NL, nextNextIt);
				this->_triggerInstruction((*currIt)->value, (*nextIt)->value);
			}
			else
				throw SyntaxGrammarError();
		}		
		catch (UnknownAction & e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (UnknownType & e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (UnknownInstruction & e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (SyntaxGrammarError & e)
		{
			std::cerr << e.what() << std::endl;
		}
	}
	if (!_exitFlag)
		throw MissingExitCommand();
}

/*
**	Constructors and destructor
*/

Parser::Parser(std::list<struct token *> tokenList)
	: _exitFlag(0)
{
	for (auto& x : tokenList)
	{
		struct token *new_token = new struct token;
		new_token->type = x->type;
		new_token->value = x->value;
		this->_tokenList.push_back(new_token);
	}
	this->_parserizer();
}

Parser::Parser(void) : _exitFlag(0) {}
Parser::Parser(const Parser & rhs)
{
	*this = rhs;
}
Parser::~Parser(void)
{
	for (auto& x : this->_stack)
		delete x;
	for (auto& x : this->_tokenList)
		delete x;
}
Parser & Parser::operator=(const Parser & rhs)
{
	for (auto& x : rhs._tokenList)
	{
		struct token *new_token = new struct token;
		new_token->type = x->type;
		new_token->value = x->value;
		this->_tokenList.push_back(new_token);
	}
	for (auto& x : rhs._stack)
	{
		IOperand const *new_operand;
		new_operand = this->_factory.createOperand(x->getType(), x->toString());
		this->_stack.push_back(new_operand);
	}
	this->_exitFlag = rhs._exitFlag;
	return (*this);
}