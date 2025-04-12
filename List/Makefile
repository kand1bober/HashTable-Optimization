
CC = g++
CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra

SOURCES_DOT_DIR = list_dump
TO_REMOVE_DOT = $(wildcard $(SOURCES_DOT_DIR)/*.* )

SOURCES_DIR_LIST = list_src

SOURCES_LIST = $(wildcard $(SOURCES_DIR_LIST)/*cpp ) 

OBJECTS_LIST = $(SOURCES_LIST:.cpp =.o) 

EXECUTABLE = List


all: $(EXECUTABLE)


$(EXECUTABLE): $(OBJECTS_LIST) 
	$(CC) $(OBJECTS_LIST) $(CFLAGS) -o $(EXECUTABLE)


%.o: %.cpp
	$(CC) -c $(CFLAGS) -Ilist_obj $< -o $@ 


clean:
	@rm  -rf  $(SOURCES_LIST/*.o) $(EXECUTABLE)
	@rm  -rf  $(TO_REMOVE_DOT)
