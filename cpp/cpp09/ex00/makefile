CC = c++ 
FLAGS = -Wall -Wextra -Werror -std=c++98
NAME = btc

SRC =  main.cpp BitcoinExchange.cpp

OBJC = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJC)
	$(CC) $(FLAGS) $^ -o $@
%.o: %.cpp BitcoinExchange.hpp
	$(CC) $(FLAGS) -c $< -o $@
clean :
	rm -rf $(OBJC)
fclean : clean
	rm -rf $(NAME)
re : fclean all