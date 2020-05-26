/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:15:19 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/24 19:41:53 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"
#include "operand_factory.hpp"

class Parser;

typedef void	(Parser::*actionFct)(void);
typedef void	(Parser::*instructionFct)(eOperandType type, std::string & operand);

class Parser
{
private:
	void			_parserizer(void);
	void			_expect(tokenType type,
								std::list<struct token>::iterator it);
	void			_triggerAction(std::string & action);
	eOperandType	_getParameterType(std::string & str);
	void			_triggerInstruction(std::string & instruction,
											std::string & wrappedParam);

	std::list<struct token>			_tokenList;
	std::vector<IOperand const *>	_stack;
	int								_exitFlag;

	static std::map<std::string, actionFct>			_actionMap;
	static std::map<std::string, instructionFct>	_instructionMap;
	static std::map<std::string, eOperandType>		_operandTypeMap;

	static OperandFactory	_factory;

	void	_pop(void);
	void	_dump(void);
	void	_add(void);
	void	_sub(void);
	void	_mul(void);
	void	_div(void);
	void	_mod(void);
	void	_print(void);
	void	_exit(void);

	void	_push(eOperandType operandType, std::string & operand);
	void	_assert(eOperandType operandType, std::string & operand);

public:
	Parser(void);
	Parser(const Parser & rhs);
	~Parser(void);
	Parser & operator=(const Parser & rhs);
	Parser(std::list<struct token> tokenList);
};
