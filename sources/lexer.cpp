/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 14:28:38 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/17 20:15:35 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"
#include "lexer.hpp"

Lexer::Lexer(void) : _error(0) {}
Lexer::Lexer(const Lexer & l)
{
	*this = rhs;
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
		this->tokenizer(std::cin, 0);
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
			throw // EXCEPTION_FILE_NOT_OPEN;
		}
	}
	else
		throw // EXCEPTION_TOO_MANY_ARGUMENTS;
}

#define COMMENT_CHAR	;

void	Lexer::_removeComment(char *line)
{
	char *ptr;

	ptr = std::strchr(line, COMMENT_CHAR);
	if (ptr)
		*ptr = 0;
}

void	Lexer::_addTokenToList(tokenType type, char *value)
{
	struct token	new new_token;

	new_token.type = type;
	new_token.value.assign(value);
	this->_tokenList.push_back(new_token);
}

void	Lexer::_analyseToken(char *str)
{
	std::cmatch	match
	std::regex	regex;

	for (auto & e : Lexer::_patternMap)
	{
		regex = e.first;
		std::regex_match(str, match, regex);
		if (match)
		{
			this->_addTokenToList(e.second, str);
			return ;	
		}
	}
	throw //EXCEPTION_NOT_A_VALID_TOKEN;
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

		this->_addTokenToList(tokenType::NL, "new line");
		delete [] line;
	}
}
