/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 12:24:18 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/17 16:04:26 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"

class Lexer
{
private:
	void	_tokenizer(void);
	void	_removeComment(char *line)
	void	_addTokenToList(tokenType type, char *value);
	void	_analyseToken(char *str);

	std::list<struct token>				_tokenList;
	bool								_error;
	std::map<std::string, tokenType>	_patternMap;

public:
	Lexer(void);
	Lexer(const Lexer & l);
	~Lexer(void);
	Lexer & operator=(const Lexer & rhs);

	Lexer(int argc, char **argv);
}

std::map<std::string, tokenType> Lexer::_patternMap =
{
	{"(and|or|pop|dump|add|sub|mul|div|mod|exit|print)", ACTION},
	{"(push|assert)", INSTR},
	{"(((int8|int16|int32)\\(-?[0-9]+\\))|((float|double)\\(-?[0-9]+\.[0-9]+\\)))", PARAM}
};
