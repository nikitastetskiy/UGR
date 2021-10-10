BIN = bin
SRC = src
OBJ = obj
INC = include
CXX = g++
CPPFLAGS = -I$(INC) -c


all: $(BIN)/viajante_comercio $(BIN)/tsp

clean:
	rm $(OBJ)/*.o
	rm $(BIN)/viajante_comercio
	rm $(BIN)/tsp

$(BIN)/viajante_comercio: $(OBJ)/main.o $(OBJ)/Mapa.o
	$(CXX) -O2 $(OBJ)/main.o $(OBJ)/Mapa.o -o $(BIN)/viajante_comercio -I$(INC)

$(BIN)/tsp: $(OBJ)/tsp.o $(OBJ)/tsp.o
	$(CXX) -O2 $(OBJ)/tsp.o -o $(BIN)/tsp -I$(INC)

$(OBJ)/tsp.o: $(SRC)/tsp.cpp
	$(CXX) -O2 $(CPPFLAGS) $(SRC)/tsp.cpp -o $(OBJ)/tsp.o -I$(INC)

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CXX) -O2 $(CPPFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o -I$(INC)

$(OBJ)/Mapa.o: $(SRC)/Mapa.cpp
	$(CXX) -O2 -c $(SRC)/Mapa.cpp -o $(OBJ)/Mapa.o -I$(INC)
