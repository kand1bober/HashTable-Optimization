CC = g++

CFLAGS = -O3 -msse3 -msse2 -msse -mavx2 -mavx

SOURCES_DIR_TABLE = List/list_src
SOURCES_DIR_LIST = HashTable/hash_table_src

SOURCES_TABLE = $(wildcard $(SOURCES_DIR_TABLE)/*cpp ) 
SOURCES_LIST = $(wildcard $(SOURCES_DIR_LIST)/*cpp ) 

OBJECTS_TABLE = $(SOURCES_TABLE:.cpp =.o) 
OBJECTS_LIST = $(SOURCES_LIST:.cpp =.o) 

EXECUTABLE = hashtable


#----------------------------
TEST	:= 1
DEBUG 	:= 0

ifeq ($(TEST), 1)
CFLAGS += -DTESTS
endif

ifeq ($(DEBUG), 1)
CFLAGS += -fsanitize=address,undefined -D _DEBUG Wall -Wextra
endif
#----------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_TABLE) $(OBJECTS_LIST)
	$(CC) $(OBJECTS_TABLE) $(OBJECTS_LIST) $(CFLAGS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -rf $(EXECUTABLE)	
	@rm -rf perf.data 
	