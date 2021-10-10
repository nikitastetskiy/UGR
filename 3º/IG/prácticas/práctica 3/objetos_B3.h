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

using namespace std;

const float AXIS_SIZE=5000;
const int TAM = 3;                                      // PARA VARIAR EL TAMAÑO DEL CUBO DE RUBIK
typedef enum{POINTS,EDGES,SOLID_CHESS,SOLID,RUBIK} _modo;

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
void  parametros(vector<_vertex3f> perfil1, int num1, int tapas);

vector<_vertex3f> perfil; 
int num;
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
