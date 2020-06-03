/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operand_template.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:40:02 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 20:01:16 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_TEMPLATE_HPP
# define OPERAND_TEMPLATE_HPP

#include "abstract_vm.hpp"
#include "ioperand.hpp"
#include "exceptions.hpp"

template <typename T>
class Operand : public IOperand
{
private:
   	T               _val;
	std::string     _str;
    eOperandType    _type;

public:
    static OperandFactory   factory;

    int				    	getPrecision( void ) const;
	eOperandType		    getType( void ) const;

	virtual IOperand const * operator+( IOperand const & rhs ) const;
	virtual IOperand const * operator-( IOperand const & rhs ) const;
	virtual IOperand const * operator*( IOperand const & rhs ) const;
	virtual IOperand const * operator/( IOperand const & rhs ) const;
	virtual IOperand const * operator%( IOperand const & rhs ) const;
	virtual std::string const & toString( void ) const;

	Operand(void);
	Operand(const Operand & rhs);
	Operand(T n);
	~Operand(void);
	Operand & operator=(const Operand & rhs);
};



/*
**  Static definition
*/

template <typename T>
OperandFactory   Operand<T>::factory;


/*
**  Method definitions
*/

template <typename T>
int Operand<T>::getPrecision( void ) const
{
    if (typeid(T) == typeid(int8_t))
        return (0);
    else if (typeid(T) == typeid(int16_t))
        return (0);
    else if (typeid(T) == typeid(int32_t))
        return (0);
    else if (typeid(T) == typeid(float))
        return (7);
    else if (typeid(T) == typeid(double))
        return (15);
    return (-1);
}


template <typename T>
eOperandType Operand<T>::getType( void ) const
{
    if (typeid(T) == typeid(int8_t))
        return (Int8);
    else if (typeid(T) == typeid(int16_t))
        return (Int16);
    else if (typeid(T) == typeid(int32_t))
        return (Int32);
    else if (typeid(T) == typeid(float))
        return (Float);
    else
        return (Double);
}


template <typename T>
std::string const & Operand<T>::toString( void ) const
{
    return (this->_str);
}


/*
**  Operator overloads
*/

template <typename T>
IOperand const * Operand<T>::operator+( IOperand const & rhs ) const
{
    eOperandType type = std::max(this->getType(), rhs.getType());
    int precision = std::max(this->getPrecision(), rhs.getPrecision());
    long double nb = std::stold(this->toString()) + std::stold(rhs.toString());
    std::stringstream sstr;
    if (precision > 0)
        sstr << std::setprecision(precision);
    sstr << nb;
    return (this->factory.createOperand(type, sstr.str()));
}


template <typename T>
IOperand const * Operand<T>::operator-( IOperand const & rhs ) const
{
    eOperandType type = std::max(this->getType(), rhs.getType());
    int precision = std::max(this->getPrecision(), rhs.getPrecision());
    long double nb = std::stold(this->toString()) - std::stold(rhs.toString());
    std::stringstream sstr;
    if (precision > 0)
        sstr << std::setprecision(precision);
    sstr << nb;
    return (this->factory.createOperand(type, sstr.str()));
}


template <typename T>
IOperand const * Operand<T>::operator*( IOperand const & rhs ) const
{
    eOperandType type = std::max(this->getType(), rhs.getType());
    int precision = std::max(this->getPrecision(), rhs.getPrecision());
    long double nb = std::stold(this->toString()) * std::stold(rhs.toString());
    std::stringstream sstr;
    if (precision > 0)
        sstr << std::setprecision(precision);
    sstr << nb;
    return (this->factory.createOperand(type, sstr.str()));
}


template <typename T>
IOperand const * Operand<T>::operator/( IOperand const & rhs ) const
{
    if (std::stold(rhs.toString()) == 0.0)
        throw DivisionByZero();
    eOperandType type = std::max(this->getType(), rhs.getType());
    int precision = std::max(this->getPrecision(), rhs.getPrecision());
    long double nb = std::stold(this->toString()) / std::stold(rhs.toString());
    std::stringstream sstr;
    if (precision > 0)
        sstr << std::setprecision(precision);
    sstr << nb;
    return (this->factory.createOperand(type, sstr.str()));
}


template <typename T>
IOperand const * Operand<T>::operator%( IOperand const & rhs ) const
{
    if (this->getType() > Int32 || rhs.getType() > Int32)
        throw ModuloWithNonIntegers();
    if (std::stold(rhs.toString()) == 0.0)
        throw DivisionByZero();
    eOperandType type = std::max(this->getType(), rhs.getType());
    int precision = std::max(this->getPrecision(), rhs.getPrecision());
    int nb = std::stoi(this->toString()) % std::stoi(rhs.toString());
    std::stringstream sstr;
    if (precision > 0)
        sstr << std::setprecision(precision);
    sstr << nb;
    return (this->factory.createOperand(type, sstr.str()));
}


/*
**  Constructors and destructor
*/

template <typename T>
Operand<T>::Operand(void)
    : _val(0), _str(""), _type(this->getType())
{}

template <typename T>
Operand<T>::Operand(const Operand & rhs)
{ *this = rhs; }

template <typename T>
Operand<T>::Operand(T n)
    : _val(n), _type(this->getType())
{
    int precision = this->getPrecision();
    std::stringstream sstr;
    if (precision > 0)
        sstr << std::setprecision(precision);
    if (this->getType() == Int8)
        sstr << (int)n;
    else
        sstr << n;
    this->_str = sstr.str();
}

template <typename T>
Operand<T>::~Operand(void) {}

template <typename T>
Operand<T> & Operand<T>::operator=(const Operand<T> & rhs)
{
        this->_val = rhs._val;
        this->_str = rhs._str;
        this->_type = rhs._type;
}

#endif