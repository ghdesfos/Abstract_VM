/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_factory.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:48:56 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 19:46:13 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"
#include "operands.hpp"
#include "exceptions.hpp"

IOperand const * OperandFactory::createInt8( std::string const & value ) const
{
	int nb;
	try
	{
		nb = std::stoi(value);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	if (nb < std::numeric_limits<char>::min())
		throw Underflow();
	if (nb > std::numeric_limits<char>::max())
		throw Overflow();
	class Int8 *operand = new class Int8(static_cast<char>(nb));
	return (operand);
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const
{
	int nb;
	try
	{
		nb = std::stoi(value);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	if (nb < std::numeric_limits<short>::min())
		throw Underflow();
	if (nb > std::numeric_limits<short>::max())
		throw Overflow();
	class Int16 *operand = new class Int16(static_cast<short>(nb));
	return (operand);
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const
{
	int nb;
	try
	{
		nb = std::stoi(value);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	if (nb < std::numeric_limits<int>::min())
		throw Underflow();
	if (nb > std::numeric_limits<int>::max())
		throw Overflow();
	class Int32 *operand = new class Int32(nb);
	return (operand);
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const
{
	float nb;
	try
	{
		nb = std::stof(value);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	class Float *operand = new class Float(nb);
	return (operand);
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const
{
	double nb;
	try
	{
		nb = std::stod(value);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	class Double *operand = new class Double(nb);
	return (operand);
}

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const
{
	IOperand const *operand;
	try
	{
		operand = (this->*_createOperandArray[type])(value);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (operand);
}
