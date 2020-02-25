/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:17:08 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/18 19:11:09 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"
#include "ioperand_hpp"

// COULDN'T there be an overflow or underflow when we add 2 numbers too big.
// SHOULDN'T we check for overflow here?

virtual IOperand const * AOperand::operator+( IOperand const & rhs ) const
{
	eOperandType type = std::max(this->getType(), rhs.getType());
	std::stringstream sstr;
	sstr << std::stod(this->toString()) + std::stod(rhs.toString());
	return (this->factory.createOperand(type, sstr.str()));
}

virtual IOperand const * AOperand::operator-( IOperand const & rhs ) const
{
	eOperandType type = std::max(this->getType(), rhs.getType());
	std::stringstream sstr;
	sstr << std::stod(this->toString()) - std::stod(rhs.toString());
	return (this->factory.createOperand(type, sstr.str()));
}

virtual IOperand const * AOperand::operator*( IOperand const & rhs ) const
{
	eOperandType type = std::max(this->getType(), rhs.getType());
	std::stringstream sstr;
	sstr << std::stod(this->toString()) * std::stod(rhs.toString());
	return (this->factory.createOperand(type, sstr.str()));
}

virtual IOperand const * AOperand::operator/( IOperand const & rhs ) const
{
	eOperandType type = std::max(this->getType(), rhs.getType());
	std::stringstream sstr;
	if (std::stod(rhs.toString()) == 0.0)
		throw divisionByZero();
	sstr << std::stod(this->toString()) / std::stod(rhs.toString());
	return (this->factory.createOperand(type, sstr.str()));
}

virtual IOperand const * AOperand::operator%( IOperand const & rhs ) const
{
	eOperandType type = std::max(this->getType(), rhs.getType());
	std::stringstream sstr;
	if (std::stod(rhs.toString()) == 0.0)
		throw divisionByZero();
	sstr << std::stod(this->toString()) % std::stod(rhs.toString());
	return (this->factory.createOperand(type, sstr.str()));
}


//----------------------------------------------------------//


Int8::Int8(void) : _val(0), _str("") { return ; }
Int8::Int8(const Int8 & rhs) { *this = rhs; }
Int8::Int8(char n) : mval(n) {
	std::stringstream s;
	s << n;
	this->_str = s.str();
};
Int8::~Int8(void) { return ; };
Int8 & Int8::operator=(const Int8 & rhs)
{
	this->_val = rhs._val;
	this->_str = rhs._str;
}

int					Int8::getPrecision(void) const { return 0; }
eOperandType		Int8::getType(void) const { return eOperandType::Int8; }
std::string const &	Int8::toString(void) const { return this->_str; }
char				Int8::getVal(void) const { return this->_val; }



Int16::Int16(void) : _val(0), _str("") { return ; }
Int16::Int16(const Int16 & rhs) { *this = rhs; }
Int16::Int16(short n) : _val(n) {
	std::stringstream s;
	s << n;
	this->_str = s.str();
};
Int16::~Int16(void) { return ; };
Int16 & Int16::operator=(const Int16 & rhs)
{
	this->_val = rhs._val;
	this->_str = rhs._str;
}

int					Int16::getPrecision(void) const { return 0; }
eOperandType		Int16::getType(void) const { return eOperandType::Int8; }
std::string const &	Int16::toString(void) const { return this->_str; }



Int32::Int32(void) : _val(0), _str("") { return ; }
Int32::Int32(const Int32 & rhs) { *this = rhs; }
Int32::Int32(int n) : _val(n) {
	std::stringstream s;
	s << n;
	this->_str = s.str();
};
Int32::~Int32(void) { return ; };
Int32 & Int32::operator=(const Int32 & rhs)
{
	this->_val = rhs._val;
	this->_str = rhs._str;
}

int					Int32::getPrecision(void) const { return 0; }
eOperandType		Int32::getType(void) const { return eOperandType::Int8; }
std::string const &	Int32::toString(void) const { return this->_str; }



Float::Float(void) : _val(0), _str("") { return ; }
Float::Float(const Float & rhs) { *this = rhs; }
Float::Float(float n) : _val(n) {
	std::stringstream s;
	s << n;
	this->_str = s.str();
};
Float::~Float(void) { return ; };
Float & Float::operator=(const Float & rhs)
{
	this->_val = rhs._val;
	this->_str = rhs._str;
}

int					Float::getPrecision(void) const { return 7; }
eOperandType		Float::getType(void) const { return eOperandType::Int8; }
std::string const &	Float::toString(void) const { return this->_str; }



Double::Double(void) : _val(0), _str("") { return ; }
Double::Double(const Double & rhs) { *this = rhs; }
Double::Double(double n) : _val(n) {
	std::stringstream s;
	s << n;
	this->_str = s.str();
};
Double::~Double(void) { return ; };
Double & Double::operator=(const Double & rhs)
{
	this->_val = rhs._val;
	this->_str = rhs._str;
}

int					Double::getPrecision(void) const { return 15; }
eOperandType		Double::getType(void) const { return eOperandType::Int8; }
std::string const &	Double::toString(void) const { return this->_str; }
