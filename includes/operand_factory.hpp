/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_factory.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 13:54:47 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/18 14:19:50 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_FACTORY_HPP
# define OPERAND_FACTORY_HPP

#include "abstract_vm.hpp"

typedef IOperand const * createOperand( std::string const & value ) const;

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

	std::array<createOperand*> _createOperandArray
	{
		&createInt8,
		&createInt16,
		&createInt32,
		&createFloat,
		&createDouble
	};
}

#endif
