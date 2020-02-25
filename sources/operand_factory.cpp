/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_factory.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:48:56 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/18 14:02:23 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"

IOperand const * OperandFactory::createInt8( std::string const & value ) const
{
	try
	{
		int nb = std::stoi(value);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	if (nb < std::numeric_limits<char>::min())
		throw Underflow();
	if (nb > std::numeric_limits<char>::max())
		throw Overflow();
	Int8 operand = new Int8(static_cast<char>(nb));
	return (operand);
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const;
{
	try
	{
		int nb = std::stoi(value);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	if (nb < std::numeric_limits<short>::min())
		throw Underflow();
	if (nb > std::numeric_limits<short>::max())
		throw Overflow();
	Int16 operand = new Int16(static_cast<short>(nb));
	return (operand);
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const;
{
	try
	{
		int nb = std::stoi(value);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	if (nb < std::numeric_limits<int>::min())
		throw Underflow();
	if (nb > std::numeric_limits<int>::max())
		throw Overflow();
	Int32 operand = new Int32(nb);
	return (operand);
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const;
{
	try
	{
		float nb = std::stof(value);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	Float operand = new Float(nb);
	return (operand);
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const;
{
	try
	{
		double nb = std::stod(value);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	Double operand = new Double(nb);
	return (operand);
}

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const
{
	try
	{
		((this->_createOperandArray).at(type))(value);
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
}
