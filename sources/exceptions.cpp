/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:43:43 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 19:45:54 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"
#include "exceptions.hpp"

const char* DivisionByZero::what() const throw()
{
	return "Division or modulo by 0 is impossible";
}

const char* Underflow::what() const throw()
{
	return "Underflow exception";
}

const char* Overflow::what() const throw()
{
	return "Overflow exception";
}

const char* FileNotOpen::what() const throw()
{
	return "The file opening failed";
}

const char* TooManyArguments::what() const throw()
{
	return "Too many arguments to the program";
}

const char* NotAValidToken::what() const throw()
{
	return "Unknown token detected";
}

const char* SyntaxGrammarError::what() const throw()
{
	return "Invalid token sequence --> syntax grammar error";
}

const char* UnknownAction::what() const throw()
{
	return "Unknown action detected";
}

const char* UnknownInstruction::what() const throw()
{
	return "Unknown instruction detected";
}

const char* UnknownType::what() const throw()
{
	return "Unknown variable type detected";
}

const char* StackEmpty::what() const throw()
{
	return "The stack is empty, hence the operation has failed";
}

const char* AssertError::what() const throw()
{
	return "Error with the assert operation";
}

const char* NumberOfElementsTooLow::what() const throw()
{
	return "Too few elements on the stack to do the operation";
}

const char* PrintWrongType::what() const throw()
{
	return "No char element on stack top --> the print operation has failed";
}
