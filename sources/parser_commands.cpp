/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:45:09 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 19:51:37 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"
#include "parser.hpp"
#include "operand_template.hpp"
#include "exceptions.hpp"

OperandFactory	Parser::_factory;

void	Parser::_push(eOperandType operandType, std::string & operandStr)
{
	const IOperand *operand = this->_factory.createOperand(operandType, operandStr);
	this->_stack.push_back(operand);
}

void	Parser::_assert(eOperandType operandType, std::string & operandStr)
{
	if (this->_stack.empty())
		throw StackEmpty();
	const IOperand *top = this->_stack.back();
	if (top->getType() != operandType || std::stold(top->toString()) != std::stold(operandStr))
		throw AssertError();
}

void	Parser::_pop(void)
{
	if (this->_stack.empty())
		throw StackEmpty();
	this->_stack.pop_back();
}

void	Parser::_dump(void)
{
	for (std::vector<IOperand const *>::reverse_iterator it = this->_stack.rbegin()
			; it != this->_stack.rend() ; it++)
		std::cout << (*it)->toString() << std::endl;
}

void	Parser::_add(void)
{
	int size = this->_stack.size();
	if (size < 2)
		throw NumberOfElementsTooLow();
	const IOperand *rhs = this->_stack.at(size - 1);
	const IOperand *lhs = this->_stack.at(size - 2);
	const IOperand *res = *lhs + *rhs;
	this->_stack.pop_back();
	this->_stack.pop_back();
	delete rhs;
	delete lhs;
	this->_stack.push_back(res);
}

void	Parser::_sub(void)
{
	int size = this->_stack.size();
	if (size < 2)
		throw NumberOfElementsTooLow();
	const IOperand *rhs = this->_stack.at(size - 1);
	const IOperand *lhs = this->_stack.at(size - 2);
	const IOperand *res = *lhs - *rhs;
	this->_stack.pop_back();
	this->_stack.pop_back();
	delete rhs;
	delete lhs;
	this->_stack.push_back(res);
}

void	Parser::_mul(void)
{
	int size = this->_stack.size();
	if (size < 2)
		throw NumberOfElementsTooLow();
	const IOperand *rhs = this->_stack.at(size - 1);
	const IOperand *lhs = this->_stack.at(size - 2);
	const IOperand *res = *lhs * *rhs;
	this->_stack.pop_back();
	this->_stack.pop_back();
	delete rhs;
	delete lhs;
	this->_stack.push_back(res);
}

void	Parser::_div(void)
{
	int size = this->_stack.size();
	if (size < 2)
		throw NumberOfElementsTooLow();
	const IOperand *rhs = this->_stack.at(size - 1);
	const IOperand *lhs = this->_stack.at(size - 2);
	const IOperand *res = *lhs / *rhs;
	this->_stack.pop_back();
	this->_stack.pop_back();
	delete rhs;
	delete lhs;
	this->_stack.push_back(res);
}

void	Parser::_mod(void)
{
	int size = this->_stack.size();
	if (size < 2)
		throw NumberOfElementsTooLow();
	const IOperand *rhs = this->_stack.at(size - 1);
	const IOperand *lhs = this->_stack.at(size - 2);
	const IOperand *res = *lhs % *rhs;
	this->_stack.pop_back();
	this->_stack.pop_back();
	delete rhs;
	delete lhs;
	this->_stack.push_back(res);
}

void	Parser::_print(void)
{
	if (this->_stack.empty())
		throw StackEmpty();
	const IOperand *top = this->_stack.back();
	if (top->getType() != eOperandType::Int8)
		throw PrintWrongType();
	std::cout << static_cast<char>(std::stoi(top->toString()));
}

void	Parser::_exit(void)
{
	std::exit(0);
}


void	Parser::_b_min(void)
{
	if (this->_stack.empty())
		std::cout << "The stack is empty, no min value" << std::endl;
	else
	{
		long double min = std::numeric_limits<long double>::infinity();
		for (auto const & value: this->_stack)
		{
			long double val = std::stold(value->toString());
			if (val < min)
				min = val;
		}
		std::cout << "Min value on the stack: " << min << std::endl;
	}
}

void	Parser::_b_max(void)
{
	if (this->_stack.empty())
		std::cout << "The stack is empty, no max value" << std::endl;
	else
	{
		long double max = -std::numeric_limits<long double>::infinity();
		for (auto const & value: this->_stack)
		{
			long double val = std::stold(value->toString());
			if (val > max)
				max = val;
		}
		std::cout << "Max value on the stack: " << max << std::endl;
	}
}

void	Parser::_b_avg(void)
{
	if (this->_stack.empty())
		std::cout << "The stack is empty, no average value" << std::endl;
	else
	{
		long double total_values = 0;
		long double nb_elements = 0;
		for (auto const & value: this->_stack)
		{
			total_values += std::stold(value->toString());
			nb_elements++;
		}
		std::cout << "Average of the values on the stack: " << total_values / nb_elements << std::endl;
	}
}

void	Parser::_b_tokens(void)
{
	if (this->_tokenList.empty())
		std::cout << "The list of tokens is empty, nothing to print" << std::endl;
	else
	{
		std::cout << "--- Top of the token list ---" << std::endl;
		std::list<struct token *>::iterator it;
		for (it = this->_tokenList.begin(); it != this->_tokenList.end(); ++it)
		{
			std::cout << (**it).value << std::endl;
		}
		std::cout << "--- Bottom of the token list ---" << std::endl;
	}
}

void	Parser::_b_stack(void)
{
	if (this->_stack.empty())
		std::cout << "The stack is empty, nothing to print" << std::endl;
	else
	{
		std::cout << "--- Top of the stack ---" << std::endl;
		std::vector<IOperand const *>::reverse_iterator rit;
		for (rit = this->_stack.rbegin(); rit != this->_stack.rend(); ++rit)
		{
			std::cout << (**rit).toString() << std::endl;
		}
		std::cout << "--- Bottom of the stack ---" << std::endl;
	}
}