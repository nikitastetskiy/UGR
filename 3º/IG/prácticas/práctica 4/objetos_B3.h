//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include <vector>
#include <GLUT/glut.h>
//#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>
#include "file_ply_stl.hpp"
#include <stack>

struct colores {
	float r;
	float g;
	float b;
};

using namespace std;

const float AXIS_SIZE=5000;
const int TAM = 3;                                      // PARA VARIAR EL TAMAÑO DEL CUBO DE RUBIK
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,RUBIK,SOLID_ILLUMINATED_FLAT,SOLID_ILLUMINATED_GOURAUD,SOLID_MULTICOLOR} _modo;

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
void   draw_rubik();
void 	draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2);
void 	draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor);
void 	draw_iluminacion_suave();
void 	draw_solido_multicolor(colores vector[]);
void	draw_iluminacion_plana();
void	calcular_normales_caras();
void	calcular_normales_vertices();

vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;

bool b_normales_caras;
bool b_normales_vertices;

_vertex4f ambiente_difusa;     //coeficientes ambiente y difuso
_vertex4f especular;           //coeficiente especular
float brillo;

vector<_vertex3i> caras;
vector<_vertex3f> color;
};


//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);

       _cubo(const _cubo &otro);
       void rotarColor(int num);
	_cubo& operator=(const _cubo &otro);
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

//*************************************************************************
// clase cuborubik
//*************************************************************************

class _cuborubik: public _triangulos3D{
public:

	_cuborubik(float tb);
	_cuborubik(const _cuborubik &otro);
	void draw(_modo modo, float r, float g, float b, int grosor);
	bool chanceMov(char giro) const;
       void decMov(char m);
	void borrarGiro();
	_cuborubik& operator=(const _cuborubik &otro);
	bool cCara1(int c);
	bool cCara2(int c);
	bool cCara3(int c);
	bool cCara4(int c);
	bool cCara5(int c);
	bool cCara6(int c);


	vector<_cubo> rubik;
	float dist;
	int tamanio = TAM;
	float escala;
	bool sentido = true;
	float giro_1,giro_2,giro_3,giro_4,giro_5,giro_6;
	int matriz_pos[TAM][TAM][TAM];
	stack<char> array_mov;
	char movant = 's';
};
