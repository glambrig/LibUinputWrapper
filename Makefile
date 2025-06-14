.PHONY: all clean fclean re

NAME = libUinputWrapper.a

CMDNAME = cmd_libuinput_demo

CC = gcc

CMDCC = c++

CFLAGS = -Wall -g

CMDSRC = libUinputWrapper.c \
			command_line_test.cpp

SRC = libUinputWrapper.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

cmd:
	$(CMDCC) $(CMDSRC) $(CFLAGS) -o $(CMDNAME)

#$(CMDNAME):
#	$(CMDCC) $(CMDSRC) $(CFLAGS) -o $(CMDNAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $^

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c -o $@ $< -O

clean:
	rm -f ./*.o

fclean: clean
	rm -f $(NAME)
	rm -f $(CMDNAME)

re: fclean all
