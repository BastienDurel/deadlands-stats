SRC=dl.cpp
OBJ=$(SRC:.cpp=.o)
NAME=dl

$(NAME): $(OBJ)
	$(CXX) -o $@ $(OBJ)

test: $(NAME)
	./$(NAME) 4 10

clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
