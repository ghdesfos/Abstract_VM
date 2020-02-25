/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 19:40:00 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 19:11:39 by ghdesfos         ###   ########.fr       */
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


class AOperand : public IOperand
{
public:
	static	OperandFactory	factory;

	virtual IOperand const * operator+( IOperand const & rhs ) const;
	virtual IOperand const * operator-( IOperand const & rhs ) const;
	virtual IOperand const * operator*( IOperand const & rhs ) const;
	virtual IOperand const * operator/( IOperand const & rhs ) const;
	virtual IOperand const * operator%( IOperand const & rhs ) const;
	virtual std::string const & toString( void ) const = 0;
};

class Int8 : public AOperand
{
public:
	Int8(void);
	Int8(const Int8 & rhs);
	Int8(char n);
	~Int8(void);
	Int8 & operator=(const Int8 & rhs);

public:
	int					getPrecision( void ) const;
	eOperandType		getType( void ) const;
	std::string const &	toString( void ) const;
	char				getVal( void ) const;

private:
	char		_val;
	std::string	_str;
};


class Int16 : public AOperand
{
public:
	Int16(void);
	Int16(const Int16 & rhs);
	Int16(short n);
	~Int16(void);
	Int16 & operator=(const Int16 & rhs);

public:
	int					getPrecision( void ) const;
	eOperandType		getType( void ) const;
	std::string const &	toString( void ) const;

private:
	short		_val;
	std::string	_str;
};


class Int32 : public AOperand
{
public:
	Int32(void);
	Int32(const Int32 & rhs);
	Int32(int n);
	~Int32(void);
	Int32 & operator=(const Int32 & rhs);

public:
	int					getPrecision( void ) const;
	eOperandType		getType( void ) const;
	std::string const &	toString( void ) const;

private:
	int			_val;
	std::string	_str;
};


class Float : public AOperand
{
public:
	Float(void);
	Float(const Float & rhs);
	Float(float n);
	~Float(void);
	Float & operator=(const Float & rhs);

public:
	int					getPrecision( void ) const;
	eOperandType		getType( void ) const;
	std::string const &	toString( void ) const;

private:
	float		_val;
	std::string	_str;
};


class Double : public AOperand
{
public:
	Double(void);
	Double(const Double & rhs);
	Double(double n);
	~Double(void);
	Double & operator=(const Double & rhs);

public:
	int					getPrecision( void ) const;
	eOperandType		getType( void ) const;
	std::string const &	toString( void ) const;

private:
	double		_val;
	std::string	_str;
};

#endif
