/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abstract_vm.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:41:28 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 21:01:45 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"
#include "lexer.hpp"
#include "parser.hpp"

int	main(int argc, char **argv)
{
	try
	{
		Lexer l(argc, argv);
		Parser p(l.getTokenList());
	}
	catch (std::exception & e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (0);
}
