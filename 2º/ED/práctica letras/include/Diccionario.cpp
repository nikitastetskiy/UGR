
Diccionario::Diccionario()
{}

set<string>::iterator Diccionario::begin(){
	return datos.begin();
}

set<string>::iterator Diccionario::end(){
	return datos.end();
}

int Diccionario::getNumero(const char c){
	int contador = 0;
	string frase;
	char cat;
	for (iterator iter = datos.begin(); iter!=datos.end(); ++iter){
		frase = *iter;
		cat = frase[0];
		if (tolower(c) == tolower(cat)){
			contador++;
		}
	}
	return contador;
}

void Diccionario::insertar(string p){
	datos.insert(p);
}

vector<string> Diccionario::PalabrasLongitud(int longitud){
	vector<string> long_palabras;
	for (iterator iter = begin(); iter != end(); ++iter){
		if ((*iter).size() == longitud){
			long_palabras.push_back(*iter);
		}
	}
	return long_palabras;
}

bool Diccionario::Esta(string palabra){
	string aux;
	bool verdad=false;
	for(iterator iter = begin(); iter != end(); ++iter){
        if(palabra == *iter){
            verdad=true;
        }
    }
    return verdad;
}

istream& operator>>(istream &is, Diccionario &D){
	string p;
	while (getline(is, p)){
		D.insertar(p);
	}
	return is;
}

ostream & operator<<(ostream &os, Diccionario &D){
	for (Diccionario::iterator iter = D.begin(); iter!=D.end(); ++iter){
		os <<(*iter) << endl;
	}
	return os;
}

