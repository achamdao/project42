#ifndef RPN_HPP
# define RPN_HPP

# include <string>
# include <stack>
# include <climits>
# include <exception>
#include <sstream>
#include <iostream>
class RPN
{
	public:
		RPN();
		RPN(const RPN &src);
		RPN &operator=(const RPN &src);
		~RPN();

		int	eval(char **arr);
		class Error
		{
			std::string _str_error;
			public:
			Error();
			Error(const std::string &str);
			void write_error();
		};
	private:
		std::stack<int>	_stack;
		
		bool	isOperator(const std::string &token) const;
		bool	isNumber(const std::string &token) const;
		void	applyOperator(const std::string &op);
};

#endif