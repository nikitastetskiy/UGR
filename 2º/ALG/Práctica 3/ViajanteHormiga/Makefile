SRC = src
OBJ = obj
INC = include
CXX = g++
CPPFLAGS = -I$(INC) -c


all: viajante_comercio tsp

viajante_comercio: $(OBJ)/main.o $(OBJ)/Mapa.o
	$(CXX) $(OBJ)/main.o $(OBJ)/Mapa.o -o viajante_comercio -I$(INC)

tsp: $(OBJ)/tsp.o $(OBJ)/tsp.o
	$(CXX) $(OBJ)/tsp.o -o tsp -I$(INC)

$(OBJ)/tsp.o: $(SRC)/tsp.cpp
	$(CXX) $(CPPFLAGS) $(SRC)/tsp.cpp -o $(OBJ)/tsp.o -I$(INC)

$(OBJ)/main.o: $(SRC)/main.cpp
	$(CXX) $(CPPFLAGS) $(SRC)/main.cpp -o $(OBJ)/main.o -I$(INC)

$(OBJ)/Mapa.o: $(SRC)/Mapa.cpp
	$(CXX) -c $(SRC)/Mapa.cpp -o $(OBJ)/Mapa.o -I$(INC)
