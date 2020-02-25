/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghdesfos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:15:19 by ghdesfos          #+#    #+#             */
/*   Updated: 2020/02/18 19:10:58 by ghdesfos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "abstract_vm.hpp"

typedef void	actionFunction(void);
typedef void	instructionFunction(eOperandType type, std::string & operand);

class Parser
{
private:
	void	_parserizer(void);
	void	_expect(tokenType type, std::list<struct token>::iterator it,
								int rk);
	void	_triggerAction(std::string & action);
	int		_getParameterType(std::string & str);
	void	Parser::_triggerInstruction(std::string & instruction,
											std::string & wrappedParam);

	std::list<struct token>			_tokenList;
	std::vector<IOperand const *>	_stack;

	static std::map<char*, actionFunction*>			_actionMap;
	static std::map<char*, instructionFunction*>	_instructionMap;
	static std::map<char*, eOperandType>			_operandTypeMap;

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
}
