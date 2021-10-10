
#include "Diccionario.h"
Diccionario::Diccionario()
{}

set<string>::iterator Diccionario::begin(){
    return datos.begin();
}

set<string>::iterator Diccionario::end(){
    return datos.end();
}
void Diccionario::insertar(string p){
    datos.insert(p);
}

vector<string> Diccionario::PalabrasLongitud(int longitud)
{
    vector<string> palabras;

    for (iterator it_dic = begin(); it_dic != end(); ++it_dic)
    {
        if ((*it_dic).size() == longitud)
            palabras.push_back(*it_dic);

    }

    return palabras;

}

/**
 * @brief Implementación del metodo buscar
 * @details Notese que se ha implementado de dos formas diferentes
 *
 * @param palabra palabra a buscar
 * @return true si la palabra está en el diccionario
 */
bool Diccionario::Esta(string palabra)
{
    string aux;
    bool verdad=false;
    for(iterator iter = begin(); iter != end(); ++iter){
        if(palabra == *iter){
            verdad=true;
        }
    }
    return verdad;
}

istream& operator>> (istream & is,Diccionario &D)
{
    string palabra;
    while (getline(is, palabra)){
        D.insertar(palabra);
    }
    return is;
}

ostream & operator<<(ostream & os, Diccionario &D)
{
    Diccionario::iterator it = D.begin();

    for (; it!=D.end(); ++it)
    {
        os << (*it) << endl;
    }

    // Devolvemos la referencia al flujo
    return os;
}