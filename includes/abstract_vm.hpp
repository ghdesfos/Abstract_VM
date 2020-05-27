/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_vm.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:47:04 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/21 20:31:28 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ABSTRACT_VM_HPP
# define ABSTRACT_VM_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <exception>
#include <cstdint>
#include <limits>
#include <regex>
#include <string>
#include <cstring>
#include <list>
#include <map>
#include <iomanip>

#define COMMENT_CHAR	';'
#define SEPARATOR	" \t\r"

enum eOperandType
{
	Int8,
	Int16,
	Int32,
	Float,
	Double	
};

enum tokenType
{
	ACTION, INSTR, PARAM, NL
};

struct token
{
	tokenType	type;
	std::string	value;
};

#endif
