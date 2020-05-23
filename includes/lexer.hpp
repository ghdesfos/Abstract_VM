/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:24:18 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 21:01:48 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"

class Lexer
{
private:
	void	_tokenizer(std::istream & stream, int mode);
	void	_removeComment(char *line);
	void	_addTokenToList(tokenType type, char *value);
	void	_analyseToken(char *str);

	std::list<struct token>					_tokenList;
	bool									_error;
	static std::map<std::string, tokenType>	_patternMap;

public:
	Lexer(void);
	Lexer(const Lexer & l);
	~Lexer(void);
	Lexer & operator=(const Lexer & rhs);

	Lexer(int argc, char **argv);

	std::list<struct token>	getTokenList(void);
};
