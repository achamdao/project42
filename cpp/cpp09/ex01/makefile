CC = c++ 
FLAGS = -Wall -Wextra -Werror -std=c++98
NAME = RPN

SRC =  main.cpp RPN.cpp

OBJC = $(SRC:.cpp=.o)

all : $(NAME)

$(NAME) : $(OBJC)
	$(CC) $(FLAGS) $^ -o $@
%.o: %.cpp RPN.hpp
	$(CC) $(FLAGS) -c $< -o $@
clean :
	rm -rf $(OBJC)
fclean : clean
	rm -rf $(NAME)
re : fclean all