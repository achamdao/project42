CC = c++ 
FLAGS = -Wall -Wextra -Werror -std=c++98
NAME = PmergeMe

SRC =  main.cpp  PmergeMe.cpp

OBJC = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJC)
	$(CC) $(FLAGS) $^ -o $@
%.o: %.cpp PmergeMe.hpp
	$(CC) $(FLAGS) -c $< -o $@
clean :
	rm -rf $(OBJC)
fclean : clean
	rm -rf $(NAME)
re : fclean all