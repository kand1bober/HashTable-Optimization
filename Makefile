CC = g++

CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra

SOURCES_DIR_TABLE = List/list_src
SOURCES_DIR_LIST = HashTable/hash_table_src

SOURCES_TABLE = $(wildcard $(SOURCES_DIR_PROC)/*cpp ) 
SOURCES_LIST = $(wildcard $(SOURCES_DIR_STACK)/*cpp ) 

OBJECTS_TABLE = $(SOURCES_PROC:.cpp =.o) 
OBJECTS_LIST = $(SOURCES_STACK:.cpp =.o) 

EXECUTABLE = HashTable

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_PROC) $(OBJECTS_STACK)
	$(CC) $(OBJECTS_PROC) $(OBJECTS_STACK) $(CFLAGS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm  $(OBJECTS_TABLE)  $(OBJECTS_LIST)  $(EXECUTABLE)