##
## EPITECH PROJECT, 2025
## OOP
## File description:
## raytracer
##

SRC = main.cpp

NAME = raytracer

CPPFLAGS = -std=c++20 -Wall -Wextra -Werror

all:
	g++ $(SRC) -o $(NAME) $(CPPFLAGS)

clean:
	rm -f *.o
	rm -f vgcore*

fclean: clean
	rm -f $(NAME)

re: fclean all
