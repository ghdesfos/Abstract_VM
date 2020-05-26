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
#include "operands.hpp"
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
	if (top->getType() != operandType || top->toString() != operandStr)
		throw AssertError();
		// !!!!! THE PROGRAM SHOULD STOP IN THIS CASE !!!!!
}

void	Parser::_pop(void)
{
	if (this->_stack.empty())
		throw StackEmpty();
		// !!!!! THE PROGRAM SHOULD STOP IN THIS CASE !!!!!
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
		// !!!!! THE PROGRAM SHOULD STOP IN THIS CASE !!!!!
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
		// !!!!! THE PROGRAM SHOULD STOP IN THIS CASE !!!!!
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
		// !!!!! THE PROGRAM SHOULD STOP IN THIS CASE !!!!!
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
		// !!!!! THE PROGRAM SHOULD STOP IN THIS CASE !!!!!
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
		// !!!!! THE PROGRAM SHOULD STOP IN THIS CASE !!!!!
	const IOperand *top = this->_stack.back();
	if (top->getType() != eOperandType::Int8)
		throw PrintWrongType();
		// !!!!! THE PROGRAM SHOULD STOP IN THIS CASE !!!!!
	class Int8 *topReinterpreted =
		const_cast<class Int8 *>(reinterpret_cast<const class Int8 *>(top));
	std::cout << topReinterpreted->getVal() << std::endl;
}

void	Parser::_exit(void)
{
	std::exit(0);
}
