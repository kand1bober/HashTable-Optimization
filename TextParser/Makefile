
CC = g++

CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra

EXECUTABLE = parser

all: $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) parser.cpp -o $(EXECUTABLE)

clean: 
	@rm -rf $(EXECUTABLE) parser.o

