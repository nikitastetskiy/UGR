BIN 	= bin
OBJ 	= obj
DOC 	= doc
LIB 	= lib
SRC 	= src
INCLUDE = include
CXX     = g++ -Ofast

EXE = testdiccionario cantidad_letras letras

all: clean $(EXE)

# ************ Compilación de módulos **********************
$(EXE):
	$(CXX) -o $(BIN)/$@ $(SRC)/$@.cpp -I$(INCLUDE)


# ************ Generación de documentación ******************
.PHONY: doc
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza *************************************
.PHONY: clean
clean:
	@echo "...Limpiando..."
	@rm -f $(OBJ)/*\ $(BIN)/*\ $(DOC)/html/*\ $(LIB)/*\ ./*.tgz
