##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile
##

SRC =		main.cpp \
			Display.cpp

OBJ = $(SRC:src/%.c=obj/%.o)

NAME = my_phoenix

CPPFLAGS = -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system -g

all: $(NAME)

$(NAME): $(OBJ)
	g++ -o $(NAME) $(OBJ) $(CPPFLAGS) -I./Server

obj/%.o: src/%.c
	mkdir -p $(dir $@)
	g++ -c -o $@ $< $(CPPFLAGS)

clean:
	rm -rf obj
	rm -f unit_tests
	rm -f *.gcdo
	rm -f *.gcda
	rm -f *.gcno

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME2)

running:
	./$(NAME)

run: all running fclean

re: clean fclean all