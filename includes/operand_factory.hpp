/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_factory.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:54:47 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 19:14:49 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_FACTORY_HPP
# define OPERAND_FACTORY_HPP

#include "abstract_vm.hpp"

/*
**	Good article on pointer to member functions:
**	https://isocpp.org/wiki/faq/pointers-to-members
*/

class IOperand;
class OperandFactory;

typedef IOperand const * (OperandFactory::*createOperandFct)( std::string const & value ) const;

class OperandFactory
{
public:
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;

private:
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

	
	createOperandFct	_createOperandArray[5] =
	{
		&OperandFactory::createInt8,
		&OperandFactory::createInt16,
		&OperandFactory::createInt32,
		&OperandFactory::createFloat,
		&OperandFactory::createDouble
	};
};

#endif
