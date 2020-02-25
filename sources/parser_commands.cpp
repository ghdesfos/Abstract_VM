/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_commands.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 14:45:09 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/18 19:17:16 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"
#include "parser.hpp"

void	Parser::_push(eOperandType operandType, std::string & operand)
{
	IOperand *operand = this->_factory.createOperand(operandType, operand);
	this->_stack.push_back(operand);
}

void	Parser::_assert(eOperandType operandType, std::string & operand)
{
	if (this->_vector.empty())
		throw // EXCEPTION_ASSERT_STACK_EMPTY;
		// !!!!! THE PROGRAM SHOULD STOP IN THIS CASE !!!!!
	IOperand *top = this->_stack.back();
	if (top->getType() != operandType || top->toString() != operand)
		throw // EXCEPTION_ASSERT;
		// !!!!! THE PROGRAM SHOULD STOP IN THIS CASE !!!!!
}

void	Parser::_pop(void)
{
	if (this->_vector.empty())
		throw // EXCEPTION_STACK_EMPTY;
	this->_stack.pop_back();
}

void	Parser::_dump(void)
{
	for (std::vector<IOperand const *>::reverse_iterator it = this->_stack.rbegin()
			; it != this->_stack.rend(), i++)
		std::cout << it->toString() << std::endl;
}

// SHOULD we do a try/catch if ever the operation does not work?

void	Parser::_add(void)
{
	if (this->_stack.size() < 2)
		throw //EXCEPTION_NB_ELEMENTS TO LOW;
	IOperand *rhs = this->_stack.pop_back();
	IOperand *lhs = this->_stack.pop_back();
	IOperand *res = *lhs + *rhs;
	delete rhs;
	delete lhs;
	this->_stack.push_back(res);
}

void	Parser::_sub(void)
{
	if (this->_stack.size() < 2)
		throw //EXCEPTION_NB_ELEMENTS TO LOW;
	IOperand *rhs = this->_stack.pop_back();
	IOperand *lhs = this->_stack.pop_back();
	IOperand *res = *lhs - *rhs;
	delete rhs;
	delete lhs;
	this->_stack.push_back(res);
}

void	Parser::_mul(void)
{
	if (this->_stack.size() < 2)
		throw //EXCEPTION_NB_ELEMENTS TO LOW;
	IOperand *rhs = this->_stack.pop_back();
	IOperand *lhs = this->_stack.pop_back();
	IOperand *res = *lhs * *rhs;
	delete rhs;
	delete lhs;
	this->_stack.push_back(res);
}

void	Parser::_div(void)
{
	if (this->_stack.size() < 2)
		throw //EXCEPTION_NB_ELEMENTS TO LOW;
	IOperand *rhs = this->_stack.pop_back();
	IOperand *lhs = this->_stack.pop_back();
	IOperand *res = *lhs / *rhs;
	delete rhs;
	delete lhs;
	this->_stack.push_back(res);
}

void	Parser::_mod(void)
{
	if (this->_stack.size() < 2)
		throw //EXCEPTION_NB_ELEMENTS TO LOW;
	IOperand *rhs = this->_stack.pop_back();
	IOperand *lhs = this->_stack.pop_back();
	IOperand *res = *lhs % *rhs;
	delete rhs;
	delete lhs;
	this->_stack.push_back(res);
}

void	Parser::_print(void)
{
	if (this->_vector.empty())
		throw // EXCEPTION_PRINT_STACK_EMPTY;
		// !!!!! THE PROGRAM SHOULD STOP IN THIS CASE !!!!!
	IOperand *top = this->_stack.back();
	if (top->getType() != eOperandType::Int8)
		throw // EXCEPTION_PRINT_WRONG_TYPE
		// !!!!! THE PROGRAM SHOULD STOP IN THIS CASE !!!!!
	std::cout << top->getVal() << std::endl;
}

void	Parser::_exit(void)
{
	// TBD
}
