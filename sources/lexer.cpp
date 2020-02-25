/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:28:38 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 19:23:08 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"
#include "lexer.hpp"
#include "exceptions.hpp"

Lexer::Lexer(void) : _error(0) {}
Lexer::Lexer(const Lexer & l)
{
	*this = l;
}
Lexer::~Lexer(void) {}
Lexer & Lexer::operator=(const Lexer & rhs)
{
	this->_tokenList = rhs._tokenList;
	this->_error = rhs._error;
	this->_patternMap = rhs._patternMap;
	return (*this);
}

Lexer::Lexer(int argc, char **argv) : _error(false)
{
	if (argc == 1)
		this->_tokenizer(std::cin, 0);
	else if (argc == 2)
	{
		std::ifstream ifs(argv[1]);
		if (ifs.is_open())
		{
			this->_tokenizer(ifs, 1);
			ifs.close();
		}
		else
		{
			this->_error = true;
			throw FileNotOpen();
		}
	}
	else
		throw TooManyArguments();
}

#define COMMENT_CHAR	';'

void	Lexer::_removeComment(char *line)
{
	char *ptr;

	ptr = std::strchr(line, COMMENT_CHAR);
	if (ptr)
		*ptr = 0;
}

void	Lexer::_addTokenToList(tokenType type, char *value)
{
	struct token	*new_token = new struct token;

	new_token->type = type;
	new_token->value.assign(value);
	this->_tokenList.push_back(new_token);
}

void	Lexer::_analyseToken(char *str)
{
	std::cmatch	match;
	std::regex	regex;

	for (auto & e : Lexer::_patternMap)
	{
		regex = e.first;
		std::regex_match(str, match, regex);
		if (!match.empty())
		{
			this->_addTokenToList(e.second, str);
			return ;	
		}
	}
	throw NotAValidToken();
}

#define SEPARATOR	" \t\r"

void	Lexer::_tokenizer(std::istream & stream, int mode)
{
	std::string	tmp;
	char		*line;
	char		*word;

	while (std::getline(stream, tmp))
	{
		line = new char [tmp.size() + 1];
		std::strcpy(line, tmp.c_str());

		if (mode == 0 && std::string(line) == ";;")
		{
			delete [] line;
			return ;
		}

		this->_removeComment(line);
		word = std::strtok(line, SEPARATOR);
		while (word)
		{
			this->_analyseToken(word);
			word = std::strtok(NULL, SEPARATOR);
		}

		this->_addTokenToList(tokenType::NL, (char*)"new line");
		delete [] line;
	}
}