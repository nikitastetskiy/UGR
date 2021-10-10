SRC = src
OBJ = obj
INC = include
CXX = g++
CPPFLAGS = -I$(INC) -c


all: viajante_comercio

viajante_comercio: $(OBJ)/main.o $(OBJ)/Mapa.o
	$(CXX) $(OBJ)/main.o $(OBJ)/Mapa.o -o viajante_comercio -I$(INC)

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CXX) $(CPPFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o -I$(INC)

$(OBJ)/Mapa.o: $(SRC)/Mapa.cpp
	$(CXX) -c $(SRC)/Mapa.cpp -o $(OBJ)/Mapa.o -I$(INC)

