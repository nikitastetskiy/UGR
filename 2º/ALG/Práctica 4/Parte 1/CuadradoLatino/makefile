PP=main
UTI=CuadradoLatino

OBJ=obj
BIN=bin
LIB=lib
SRC=src
INC=include


all: $(BIN)/$(PP)

clean:
	echo "Limpiando archivos objetos... "
	rm $(OBJ)/*.o

mrproper: clean
	rm $(BIN)/$(PP)

$(OBJ)/$(PP).o: $(SRC)/$(PP).cpp $(INC)/$(UTI).h
	g++ -c -O2 -o $(OBJ)/$(PP).o -I$(INC) $(SRC)/$(PP).cpp

$(OBJ)/$(UTI).o: $(SRC)/$(UTI).cpp $(INC)/$(UTI).h
	g++ -c -O2 -o $(OBJ)/$(UTI).o -I$(INC) $(SRC)/$(UTI).cpp

$(BIN)/$(PP): $(OBJ)/$(PP).o $(OBJ)/$(UTI).o
	g++ -O2 -o $(BIN)/$(PP) $(OBJ)/$(PP).o $(OBJ)/$(UTI).o
