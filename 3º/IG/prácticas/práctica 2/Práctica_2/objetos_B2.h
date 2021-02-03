//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

// Cambiar sistema operativo por OSX / LINUX correspondiente
#include <GLUT/glut.h>
//#include <GL/gl.h>
#include <vector>
#include "vertex.h"
#include <stdlib.h>

struct color {
	float r;
	float g;
	float b;
};

const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,SOLID_MULTICOLOR} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw_solido_multicolor(color vector[]);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);

vector<_vertex3i> caras;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=0.75);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

int   parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************

class _rotacion: public _triangulos3D
{
public:
       _rotacion();
void  parametros(vector<_vertex3f> perfil1, int num1);

vector<_vertex3f> perfil; 
};

/*
class _esfera: public _triangulos3D
{
public:
       _esfera(float radio, int num1, int num2); // numero de lados y numero de puntos con el que quiero aproximar la esfera
int num;
};

class _cono: public _triangulos3D
{
public:
       _cono(float radio, int num1, int altura); // numero de lados
int num;
};

class _cilindro: public _triangulos3D
{
public:
       _cilindro(float radio, int num1, int altura); // numero de lados
int num;
};
*/

//*************************************************************************
// clase objeto cilindro
//*************************************************************************

class _cilindro: public _triangulos3D
{
public:

  // si {
  //    tapitas == 1 signfica tapa superior
  //    tapitas == 2 signfica tapa inferior
  //    tapitas == 3 signfica ambas tapitas
  // }
  // sino {
  //    no hay tapitas
  // }

  _cilindro(float r=1, float h=1, int n=20, int tapitas=3);
  void  rotacion();

  vector<_vertex3f> perfil;
  int num;
  int tapitas;
};

//*************************************************************************
// clase objeto cono
//*************************************************************************

class _cono: public _triangulos3D
{
public:

  // tapitas = true signfica tapa activada
  // tapitas = false signfica tapa desactivada

  _cono(float r=1.0, float h=1, int n=20, bool tapitas=true);
  void  rotacion();

  vector<_vertex3f> perfil;
  int num;
  bool tapitas;
};

//************************************************************************
// clase objeto esfera
//************************************************************************

class _esfera: public _triangulos3D
{
public:
  
  // si {
  //    tapitas == 1 signfica tapa superior
  //    tapitas == 2 signfica tapa inferior
  //    tapitas == 3 signfica ambas tapitas
  // }
  // sino {
  //    no hay tapitas
  // }

  _esfera(float r=1, int lat=6, int lon=6, int tapitas=3);
  void  rotacion();

  vector<_vertex3f> perfil; 
  int num;
  int tapitas;
};
