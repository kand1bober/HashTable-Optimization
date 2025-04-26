CC = gcc

CFLAGS = -z execstack -O3 -msse4.2 -msse3 -msse2 -msse -mavx2 -mavx 
#-no-pie -z execstack

SOURCES_DIR_TABLE = HashTable/hash_table_src
SOURCES_DIR_LIST = List

SOURCES_TABLE = $(wildcard $(SOURCES_DIR_TABLE)/*cpp ) 
SOURCES_LIST = $(wildcard $(SOURCES_DIR_LIST)/*cpp ) 

OBJECTS_TABLE = $(SOURCES_TABLE:.cpp =.o) 
OBJECTS_LIST = $(SOURCES_LIST:.cpp =.o) 
OBJECTS_ASM = ASM1/MyStrcmp.o 

EXECUTABLE = hashtable

#----------------------------
DEBUG 	:= 0

ifeq ($(DEBUG), 1)
CFLAGS += -fsanitize=address,undefined -D _DEBUG -Wall -Wextra
endif
#----------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_TABLE) $(OBJECTS_LIST) $(OBJECTS_ASM)
	$(CC) $(OBJECTS_TABLE) $(OBJECTS_LIST) $(OBJECTS_ASM) $(CFLAGS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	@rm -rf $(EXECUTABLE)	
	@rm -rf perf.data 


