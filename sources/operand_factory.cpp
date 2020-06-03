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
#include "operand_template.hpp"
#include "exceptions.hpp"

IOperand const * OperandFactory::createInt8( std::string const & value ) const
{
	long double nb = std::stold(value);
	if (nb < std::numeric_limits<int8_t>::min())
		throw Underflow();
	if (nb > std::numeric_limits<int8_t>::max())
		throw Overflow();
	IOperand *operand = new Operand<int8_t>(static_cast<int8_t>(nb));
	return (operand);
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const
{
	long double nb = std::stold(value);
	if (nb < std::numeric_limits<int16_t>::min())
		throw Underflow();
	if (nb > std::numeric_limits<int16_t>::max())
		throw Overflow();
	IOperand *operand = new Operand<int16_t>(static_cast<int16_t>(nb));
	return (operand);
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const
{
	long double nb = std::stold(value);
	if (nb < std::numeric_limits<int32_t>::min())
		throw Underflow();
	if (nb > std::numeric_limits<int32_t>::max())
		throw Overflow();
	IOperand *operand = new Operand<int32_t>(static_cast<int32_t>(nb));
	return (operand);
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const
{
	long double nb = std::stold(value);
	if (nb < std::numeric_limits<float>::min())
		throw Underflow();
	if (nb > std::numeric_limits<float>::max())
		throw Overflow();
	IOperand *operand = new Operand<float>(static_cast<float>(nb));
	return (operand);
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const
{
	long double nb = std::stold(value);
	if (nb < std::numeric_limits<double>::min())
		throw Underflow();
	if (nb > std::numeric_limits<double>::max())
		throw Overflow();
	IOperand *operand = new Operand<double>(static_cast<double>(nb));
	return (operand);
}

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const
{
	IOperand const *operand = (this->*_createOperandArray[type])(value);
	return (operand);
}
