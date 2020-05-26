/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:45:08 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 19:44:36 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"

class DivisionByZero : public std::exception
{
	public:
		DivisionByZero() {};
		~DivisionByZero() {};

	public:
		virtual const char* what() const throw();
};

class Underflow : public std::exception
{
	public:
		Underflow() {};
		~Underflow() {};

	public:
		virtual const char* what() const throw();
};

class Overflow : public std::exception
{
	public:
		Overflow() {};
		~Overflow() {};

	public:
		virtual const char* what() const throw();
};

class FileNotOpen : public std::exception
{
	public:
		FileNotOpen() {};
		~FileNotOpen() {};

	public:
		virtual const char* what() const throw();
};

class TooManyArguments : public std::exception
{
	public:
		TooManyArguments() {};
		~TooManyArguments() {};

	public:
		virtual const char* what() const throw();
};

class NotAValidToken : public std::exception
{
	public:
		NotAValidToken() {};
		~NotAValidToken() {};

	public:
		virtual const char* what() const throw();
};

class SyntaxGrammarError : public std::exception
{
	public:
		SyntaxGrammarError() {};
		~SyntaxGrammarError() {};

	public:
		virtual const char* what() const throw();
};

class UnknownAction : public std::exception
{
	public:
		UnknownAction() {};
		~UnknownAction() {};

	public:
		virtual const char* what() const throw();
};

class UnknownInstruction : public std::exception
{
	public:
		UnknownInstruction() {};
		~UnknownInstruction() {};

	public:
		virtual const char* what() const throw();
};

class UnknownType : public std::exception
{
	public:
		UnknownType() {};
		~UnknownType() {};

	public:
		virtual const char* what() const throw();
};

class StackEmpty : public std::exception
{
	public:
		StackEmpty() {};
		~StackEmpty() {};

	public:
		virtual const char* what() const throw();
};

class AssertError : public std::exception
{
	public:
		AssertError() {};
		~AssertError() {};

	public:
		virtual const char* what() const throw();
};

class NumberOfElementsTooLow : public std::exception
{
	public:
		NumberOfElementsTooLow() {};
		~NumberOfElementsTooLow() {};

	public:
		virtual const char* what() const throw();
};

class PrintWrongType : public std::exception
{
	public:
		PrintWrongType() {};
		~PrintWrongType() {};

	public:
		virtual const char* what() const throw();
};

class MissingExitCommand : public std::exception
{
	public:
		MissingExitCommand() {};
		~MissingExitCommand() {};

	public:
		virtual const char* what() const throw();
};
