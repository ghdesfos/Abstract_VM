/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:40:00 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 20:01:14 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDS_HPP
# define OPERANDS_HPP

# include "abstract_vm.hpp"
# include "operand_factory.hpp"

class IOperand
{
public:
	virtual int getPrecision( void ) const = 0;
	virtual eOperandType getType( void ) const = 0;

	virtual IOperand const * operator+( IOperand const & rhs ) const = 0;
	virtual IOperand const * operator-( IOperand const & rhs ) const = 0;
	virtual IOperand const * operator*( IOperand const & rhs ) const = 0;
	virtual IOperand const * operator/( IOperand const & rhs ) const = 0;
	virtual IOperand const * operator%( IOperand const & rhs ) const = 0;
	virtual std::string const & toString( void ) const = 0;

	virtual ~IOperand( void ) {}
};

#endif
