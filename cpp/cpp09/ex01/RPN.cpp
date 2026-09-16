#include "RPN.hpp"


RPN::RPN() {}

RPN::RPN(const RPN &src)
{
	*this = src;
}

RPN &RPN::operator=(const RPN &src)
{
	if (this != &src)
		_stack = src._stack;
	return (*this);
}

RPN::~RPN() {}

bool	RPN::isOperator(const std::string &token) const
{
	return (token == "+" || token == "-"
		|| token == "*" || token == "/");
}

bool	RPN::isNumber(const std::string &token) const
{
	if(token.size() != 1 || !std::isdigit((token[0])))
		return false;
	return (true);
}

void	RPN::applyOperator(const std::string &op)
{
	if (_stack.size() < 2)
		throw Error("Error: not enough operands");

	int b = _stack.top();
	_stack.pop();
	int a = _stack.top();
	_stack.pop();
	long result = 0;

	if (op == "+")
	{
		result = a + (long)b;
		if (result > INT_MAX || result < INT_MIN)
			throw Error("Error: out of rang");
	}
	else if (op == "-")
	{
		result = a - (long)b;
		if (result > INT_MAX || result < INT_MIN)
			throw Error("Error: out of rang");
	}
	else if (op == "*")
	{
		result = a * (long)b;
		if (result > INT_MAX || result < INT_MIN)
			throw Error("Error: out of rang");
	}
	else if (op == "/")
	{
		if (b == 0)
			throw Error("Error: division by zero");
		result = a / b;
	}
	_stack.push(result);
}

RPN::Error::Error()
{
	_str_error = "standar error";
}

RPN::Error::Error(const std::string &str)
{
	_str_error = str ; 
}
void RPN::Error::write_error()
{
	std::cerr<< _str_error << std::endl;
}
int	RPN::eval(char **arr)
{
	std::string			token;
	std::istringstream	strin(arr[1]);
	while (strin >> token)
	{
		if (isNumber(token))
			_stack.push(token[0] - '0');
		else if (isOperator(token))
		{
			applyOperator(token);
		}
		else
		{
			throw Error("Error: invalid  token");
		}
	}
	if (_stack.size() != 1)
		throw Error("Error: invalid expression");

	return (_stack.top());
}