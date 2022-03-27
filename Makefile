SRC := main.cpp cracker.cpp util.cpp
OBJ := $(patsubst %.cpp, %.o, $(SRC))
BIN := cracker

CXXFLAGS := -Wall -Wextra

all:	build run

run:
	./$(BIN)
	
build:	$(OBJ)
	gcc $(CXXFLAGS) $(OBJ) -o $(BIN)

%.o: %.cpp
	gcc $(CXXFLAGS) -c $< -o $@

clean:
	rm $(OBJ) $(BIN)
