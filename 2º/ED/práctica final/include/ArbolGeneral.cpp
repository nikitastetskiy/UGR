/******************************************************************************
 *
 * ED - Estructura de Datos
 * Grado en Ingeniería Informática
 *
 * 2014 - Ernesto Serrano <erseco@correo.ugr.es>
 * ---------------------------------------------
 *
 *  Implementación del T.D.A Arbol General
 *
 *  NOTA: Este código está  basado en el arbol binario del Prof. J.F. Valdivia
 *
 ******************************************************************************/

/*____________________________________________________________ */
/*____________________________________________________________ */
//               FUNCIONES PRIVADAS
/*____________________________________________________________ */
/*____________________________________________________________ */

template <class T>
void ArbolGeneral <T> :: destruir (nodo * n)
{
	if (n!=0){             //Si no es un nodo nulo,
		destruir(n->izqda);  //destruimos recursivamente su hijo izquierda y
		destruir(n->drcha);  //destruimos recursivamente su hermano derecha
		delete n;            //Una vez borrados los descendientes, borramos el nodo
	}
}

/*____________________________________________________________ */

template <class T>
void ArbolGeneral<T>::copiar(nodo * & dest, nodo * orig)
{
	if (orig == 0)                      //Si el nodo origen es nulo,
		dest = 0;
	else
	{                               //Si no es el nodo nulo,

		dest = new nodo;                  //Reservamos el nodo destino
		dest->etiqueta = orig->etiqueta;  //Copiamos la etiqueta

		// Lo copiamos con este sistema
		dest->padre = orig->padre;
		dest->izqda = orig->izqda;
		dest->drcha = orig->drcha;

		copiar(dest->izqda, orig->izqda); //Copiamos recursivamente el hijo izqda
		copiar(dest->drcha, orig->drcha); //Copiamos recursivamente el hijo drcha
		// if (dest->izqda != 0)             //Si hay hijo izquierda,
		// 	dest->izqda->padre = dest;      //actualizamos su padre
		// if (dest->drcha != 0)             //Si hay hijo derecha,
		// {
		// 	cout << dest->etiqueta << endl;
		// 	dest->drcha->padre = dest;      //actualizamos su padre
		// }
		// 	//dest->drcha->padre = dest->padre;      //actualizamos su padre MARTA

	}

}


/*____________________________________________________________ */

template <class T>
int ArbolGeneral<T>::contar(const nodo * n) const
{
	if (n==0)      //Si es el nodo nulo,
		return 0;    //devuelve 0
	else
		return 1+contar(n->izqda)+contar(n->drcha); //Caso general (recursivo)
}

/*____________________________________________________________ */

template <class T>
bool ArbolGeneral<T>::soniguales(const nodo * n1, const nodo * n2) const
{
	if (n1==0 && n2==0)                        //Si los dos nodos son nulos,
		return true;                             //devolvemos true
	else if (n1==0 || n2==0)                   //Si uno es nulo y el otro no
		return false;                            //devolvemos false
	else if (n1->etiqueta!=n2->etiqueta)       //Si sus etiquetas son distintas
		return false;                            //devolvemos false
	else if (!soniguales(n1->izqda,n2->izqda)) //Si los hijos izquierda no son =
		return false;                            //devolvemos false
	else if (!soniguales(n1->drcha,n2->drcha)) //Si los hijos derecha no son =
		return false;                            //devolemos false
	else                                       //En otro caso
		return true;                             //devolvemos true
}

/*____________________________________________________________ */

template <class T>
void ArbolGeneral <T>::lee_arbol(std::istream& in, nodo * & nod){
	char c;
	in >> c;                     //Lectura de un carácter
	if (c=='n'){                 //Si es 'n'
		nod= new nodo;             //Reservamos un nuevo nodo
		in >> nod->etiqueta;       //Leemos la etiqueta
		lee_arbol(in,nod->izqda);  //Leemos recursivamente el hijo izquierda
		lee_arbol(in,nod->drcha);  //Leemos recursivamente el hijo derecha
		if (nod->izqda!=0)         //Si hay hijo izquierda,
			nod->izqda->padre=nod;   //actualizamos su padre
		if (nod->drcha!=0)         //Si hay hijo derecha,
			nod->drcha->padre=nod;   //actualizamos su padre
	}
	else nod= 0;                 //Si no es 'n' hay un error en la entrada
															 //o no hay más caracteres que leer,
															 //y devolvemos un árbol nulo
}

/*____________________________________________________________ */

template <class T>
void ArbolGeneral<T>::escribe_arbol(std::ostream& out, nodo * nod) const{
	if (nod==0)                            //Si el nodo es nulo
		out << "x ";                         //escribimos 'x'
	else {                                 //Si el nodo no es nulo
		out << "n "<< nod->etiqueta << " ";  //escribimos su etiqueta
		escribe_arbol(out,nod->izqda);    //Escribimos el hijo izqda recursivamente
		escribe_arbol(out,nod->drcha);    //Escribimos el hijo drcha recursivamente
	}
}

/*____________________________________________________________ */
/*____________________________________________________________ */
//               FUNCIONES PUBLICAS
/*____________________________________________________________ */
/*____________________________________________________________ */


template <class T>
inline ArbolGeneral<T>::ArbolGeneral(){
	laraiz = 0;  //El constructor por defecto crea un árbol vacío
}

/*____________________________________________________________ */

template <class T>
ArbolGeneral<T>::ArbolGeneral(const T& e)
{
	laraiz = new nodo;      //Crea el nodo raíz
	laraiz->padre =         //No tiene padre,
	laraiz->izqda =         //ni hijo izquierda
	laraiz->drcha = 0;      //ni hermano derecha.
	laraiz->etiqueta = e;   //Asignamos valor a la etiqueta de la raíz
}

/*____________________________________________________________ */

template <class T>
ArbolGeneral<T>::ArbolGeneral (const ArbolGeneral<T>& v)
{
	copiar (laraiz,v.laraiz); //Llamamos a copiar desde la raíz
	if (laraiz!=0)            //Si no es el árbol vacío
		laraiz->padre= 0;       //actualizamos el padre
}

/*____________________________________________________________ */

template <class T>
inline ArbolGeneral<T>::~ArbolGeneral(){
	destruir(laraiz);  //Destruye llamando a destruir desde la raíz
}

/*____________________________________________________________ */

template <class T>
ArbolGeneral<T> &
ArbolGeneral<T>::operator = (const ArbolGeneral<T>&v){
	if (this!=&v){              //Comprobación de rigor. Si no es el mismo objeto
		destruir(laraiz);         //destruimos el objeto *this
		copiar (laraiz,v.laraiz); //Llamamos a copiar desde la raíz
		if (laraiz!=0)            //Si no es el árbol vacío
			laraiz->padre= 0;       //actualizamos el padre
	}
	return *this; //Devolvemos *this para permitir encadenamientos (a=b=c)
}

/*____________________________________________________________ */

template <class T>
void ArbolGeneral<T>::AsignaRaiz(const T& e){
	destruir(laraiz);     //Destruye el árbol actual
	laraiz = new nodo;    //Reservamos el nodo raíz
	laraiz->padre =       //No tiene padre,
	laraiz->izqda =       //ni hijo izquierda,
	laraiz->drcha = 0;    //ni hijo derecha.
	laraiz->etiqueta= e;  //Damos valor a la etiqueta de la raíz
}

/*____________________________________________________________ */

template <class T>
inline typename ArbolGeneral<T>::Nodo
ArbolGeneral<T>::raiz() const{
	return laraiz;
}

/*____________________________________________________________ */

template <class T>
inline typename ArbolGeneral<T>::Nodo
ArbolGeneral<T>::hijomasizquierda(const Nodo p) const{
	assert(p!=0);       //El nodo no debe ser nulo
	return (p->izqda);
}

/*____________________________________________________________ */

template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::hermanoderecha(const Nodo p) const{
	assert(p!=0);       //El nodo no debe ser nulo
	return (p->drcha);
}

/*____________________________________________________________ */

template <class T>
typename ArbolGeneral<T>::Nodo ArbolGeneral<T>::padre(const Nodo p) const{
	assert(p!=0);       //El nodo no debe ser nulo
	return (p->padre);
}

/*____________________________________________________________ */

template <class T>
T& ArbolGeneral<T>::etiqueta(const Nodo p){
	assert(p!=0);          //El nodo no debe ser nulo
	return (p->etiqueta);
}

/*____________________________________________________________ */

template <class T>
const T& ArbolGeneral<T>::etiqueta(const Nodo p) const{
	assert(p!=0);          //El nodo no debe ser nulo
	return (p->etiqueta);
}

/*____________________________________________________________ */

template <class T>
void ArbolGeneral<T>::asignar_subarbol(const ArbolGeneral<T>& orig,
 const Nodo nod){
	destruir(laraiz);    //Destruye el árbol actual
	copiar(laraiz,nod);  //Copiamos el subárbol que cuelga de nod en la raíz
	if (laraiz!=0)       //Si el subárbol copiado no es vacío,
		laraiz->padre=0;   //actualizamos el padre
}

/*____________________________________________________________ */

template <class T>
void ArbolGeneral<T>::podar_hijomasizquierda(Nodo n, ArbolGeneral<T>& dest){
	assert(n!=0);             //El nodo no debe ser nulo
	Nodo *res = 0;
	if (n->izqda!=0)
	{
		res= n->izqda;
		n->izqda = res->drcha;
		res->padre = res->drcha = 0;
	}
}

/*____________________________________________________________ */

template <class T>
void ArbolGeneral<T>::podar_hermanoderecha(Nodo n, ArbolGeneral<T>& dest){
	assert(n!=0);             //El nodo no debe ser nulo
	destruir(dest.laraiz);    //Destruimos el árbol destino
	dest.laraiz=n->drcha;     //Copia el hijo derecha de n en la raíz de dest
	if (dest.laraiz!=0) {     //Si el subárbol copiado no es vacío,
		dest.laraiz->padre=0;   //actualizamos el padre
		n->drcha=0;             //y actualizamos el hijo a la derecha
	}
}

/*____________________________________________________________ */

template <class T>
void ArbolGeneral<T>::insertar_hijomasizquierda(Nodo n, ArbolGeneral<T>& rama)
{
	assert(n!=0);             //El nodo no debe ser nulo

	if (!rama.empty())
	{
		rama.laraiz->drcha = n->izqda;
		rama.laraiz->padre = n;
		n->izqda = rama.laraiz;
		rama.laraiz=0; // Dejamos la rama vacía
	}
}

/*____________________________________________________________ */

template <class T>
void ArbolGeneral<T>::insertar_hermanoderecha(Nodo n, ArbolGeneral<T>& rama){
	assert(n!=0);             //El nodo no debe ser nulo
	if (!rama.empty())
	{
		rama.laraiz->drcha = n->drcha;
		rama.laraiz->padre = n->padre;
		n->drcha = rama.laraiz;
		rama.laraiz=0; // Dejamos la rama vacía
	}

}

/*____________________________________________________________ */

template <class T>
void ArbolGeneral<T>::clear(){
	destruir(laraiz);    //Destruimos el árbol recursivamente desde la raíz
	laraiz= 0;           //Actualizamos la raíz del árbol
}

/*____________________________________________________________ */

template <class T>
inline int ArbolGeneral<T>::size() const{
	return contar(laraiz);  //Contamos los nodos recursivamente desde la raíz
}

/*____________________________________________________________ */

template <class T>
inline bool ArbolGeneral<T>::empty() const{
	return (laraiz==0);
}

/*____________________________________________________________ */

template <class T>
inline bool ArbolGeneral<T>::operator==(const ArbolGeneral<T>& v) const{
	return soniguales(laraiz,v.laraiz); //Comparamos los árboles desde la raíz
}

/*____________________________________________________________ */

template <class T>
inline bool ArbolGeneral<T>::operator!=(const ArbolGeneral<T>& v) const{
	return !(*this==v); //Comparamos los árboles desde la raíz
}

/*____________________________________________________________ */

template <class T>
inline istream& operator>> (istream& in, ArbolGeneral<T>& v){
	v.lee_arbol(in,v.laraiz); //Lee el árbol
	return in;                //Devuelve in para permitir encadenamientos
}

/*____________________________________________________________ */

template <class T>
inline ostream& operator<< (ostream& out, const ArbolGeneral<T>& v){
	v.escribe_arbol(out,v.laraiz); //Escribe el árbol
	return out;                    //Devuelve out para permitir encadenamientos
}

/*____________________________________________________________ */


// ------------------------------------------------------------------
// INICIO ITERADOR ITER_PREORDEN

template<class T>
ArbolGeneral<T>::iter_preorden::iter_preorden()
{
	it = typename ArbolGeneral<T>::Nodo();
	raiz = it;
	level = 0;
}


template <class T>
ArbolGeneral<T>::iter_preorden::iter_preorden(const ArbolGeneral<T>::iter_preorden & i) : it(i.it), raiz(i.it), level(i.level) {}

template <class T>
ArbolGeneral<T>::iter_preorden::iter_preorden(ArbolGeneral<T>::Nodo n) : it(n), level(0) {}

template<class T>
T & ArbolGeneral<T>::iter_preorden::operator*()
{
	return (*it).etiqueta;
}

template<class T>
typename ArbolGeneral<T>::Nodo & ArbolGeneral<T>::iter_preorden::operator&()
{
	return it;
}


template<class T>
int ArbolGeneral<T>::iter_preorden::getlevel() const
{
	return level;
}

template<class T>
typename ArbolGeneral<T>::iter_preorden & ArbolGeneral<T>::iter_preorden::operator ++()
{
	if (it==0)
		return *this;

	if (it->izqda != 0)
	{
		it = it->izqda;
		level++; // Incrementamos el nivel
	}
	else if (it->drcha != 0)
	{
		it = it->drcha;
	}
	else
	{

		while ( (it->padre != 0) && (it->padre->drcha == it || it->padre->drcha == 0))
		{
			it = it->padre;
			level--; // Decrementamos el nivel
		}

		if (it->padre == 0)
			it = typename ArbolGeneral<T>::Nodo();
		else
		{
			it = it->padre->drcha;
			level--; // Decrementamos el nivel
		}

	}

	return *this;
}

template<class T>
bool ArbolGeneral<T>::iter_preorden::operator == (const iter_preorden &i)
{
	return it == i.it;
}

template<class T>
bool ArbolGeneral<T>::iter_preorden::operator != (const iter_preorden &i)
{
	return it != i.it;
}

template<class T>
typename ArbolGeneral<T>::iter_preorden ArbolGeneral<T>::begin()
{
	return iter_preorden(laraiz);
}

template<class T>
typename ArbolGeneral<T>::iter_preorden ArbolGeneral<T>::end()
{
	return iter_preorden(typename ArbolGeneral<T>::Nodo());
}

// FIN ITERADOR ITER_PREORDEN

// ------------------------------------------------------------------

// // INICIO ITERADOR CONST_ITER_PREORDEN

template<class T>
ArbolGeneral<T>::const_iter_preorden::const_iter_preorden()
{
	it = typename ArbolGeneral<T>::Nodo();
	raiz = it;
	level = 0;
}


template <class T>
ArbolGeneral<T>::const_iter_preorden::const_iter_preorden(const ArbolGeneral<T>::const_iter_preorden & i) : it(i.it), raiz(i.it), level(0) {}

template <class T>
ArbolGeneral<T>::const_iter_preorden::const_iter_preorden(ArbolGeneral<T>::Nodo n) : it(n) {}

template<class T>
const T & ArbolGeneral<T>::const_iter_preorden::operator*()
{
	return *it;
}

template<class T>
int ArbolGeneral<T>::const_iter_preorden::getlevel() const
{
	return level;
}

template<class T>
typename ArbolGeneral<T>::const_iter_preorden & ArbolGeneral<T>::const_iter_preorden::operator ++()
{
	if (it==0)
		return *this;

	if (it->izqda != 0)
	{
		it = it->izqda;
		level++; // Incrementamos el nivel
	}
	else if (it->drcha != 0)
	{
		it = it->drcha;
	}
	else
	{

		while ( (it->padre != 0) && (it->padre->drcha == it || it->padre->drcha == 0))
		{
			it = it->padre;
			level--; // Decrementamos el nivel
		}

		if (it->padre == 0)
			it = typename ArbolGeneral<T>::Nodo();
		else
		{
			it = it->padre->drcha;
			level--; // Decrementamos el nivel
		}

	}

	return *this;
}

template<class T>
bool ArbolGeneral<T>::const_iter_preorden::operator == (const const_iter_preorden &i)
{
	return it == i.it;
}

template<class T>
bool ArbolGeneral<T>::const_iter_preorden::operator != (const const_iter_preorden &i)
{
	return it != i.it;
}

template<class T>
typename ArbolGeneral<T>::const_iter_preorden ArbolGeneral<T>::begin() const
{
	return const_iter_preorden(laraiz);
}

template<class T>
typename ArbolGeneral<T>::const_iter_preorden ArbolGeneral<T>::end() const
{
	return const_iter_preorden(typename ArbolGeneral<T>::Nodo());
}

// FIN ITERADOR CONST_ITER_PREORDEN
// ------------------------------------------------------------------



