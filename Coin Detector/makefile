CC = g++
LFLAGS = -std=c++11 `pkg-config --libs opencv`
CFLAGS = -c -Wall `pkg-config --cflags opencv`

PROGRAM_ONE = main
COMMON_SOURCES = Coin.cpp ImageFunctions.cpp
PROGRAM_ONE_SOURCE = main.cpp

COMMON_OBJECTS = $(COMMON_SOURCES:.cpp=.o)
PROGRAM_ONE_OBJECT = $(PROGRAM_ONE_SOURCE:.cpp=.o)

all: $(PROGRAM_ONE)

$(PROGRAM_ONE): $(COMMON_OBJECTS) $(PROGRAM_ONE_OBJECT)
	$(CC) -o $(PROGRAM_ONE) $(COMMON_OBJECTS) $(PROGRAM_ONE_OBJECT)

.cpp.o:
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	$(RM) *.o *~ $(PROGRAM_ONE)
