CC = g++

CFLAGS = -fsanitize=address,undefined -D _DEBUG -O0 -Wall -Wextra

SOURCES_DIR_TABLE = List/list_src
SOURCES_DIR_LIST = HashTable/hash_table_src

SOURCES_TABLE = $(wildcard $(SOURCES_DIR_TABLE)/*cpp ) 
SOURCES_LIST = $(wildcard $(SOURCES_DIR_LIST)/*cpp ) 

OBJECTS_TABLE = $(SOURCES_TABLE:.cpp =.o) 
OBJECTS_LIST = $(SOURCES_LIST:.cpp =.o) 

TO_REMOVE_RESOURCES = /home/vyacheslav/HashTable/HashTable/table_dump/table_dump.csv

EXECUTABLE = hashtable


#----------------------------
TEST	:= 1

ifeq ($(TEST), 1)
CFLAGS += -DTESTS
endif
#----------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_TABLE) $(OBJECTS_LIST)
	$(CC) $(OBJECTS_TABLE) $(OBJECTS_LIST) $(CFLAGS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -rf $(TO_REMOVE_RESOURCES)	
	@rm -rf $(EXECUTABLE)	
	
	