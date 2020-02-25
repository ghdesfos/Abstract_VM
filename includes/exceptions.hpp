/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 12:45:08 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/12 17:41:15 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"

class divisionByZero : public std::exception
{
	public:
		divisionByZero() {};
		~divisionByZero() {};

	public:
		virtual const char* what() const throw();
}
