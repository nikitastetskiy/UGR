//**************************************************************************
// Práctica 3 usando objetos
//**************************************************************************

#include <GLUT/glut.h>
//#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B3.h"
#include <thread>
#include <chrono>

using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ARTICULADO} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=450,Window_high=450;


// objetos
_cubo cubo;
//_piramide piramide(0.85,1.3);
//_objeto_ply  ply; 
_rotacion rotacion; 
_cuborubik crubik(2.0);
int dibujo = -1;

// _objeto_ply *ply1;


//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
	// case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
        // case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;
        case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;
        case ARTICULADO: crubik.draw(modo,1.0,0.0,0.0,3);break;
	}

}


//**************************************************************************
//
//***************************************************************************

void draw(void)
{

clean_window();
change_observer();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}


//**********-o*****************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q': {exit(0);}
	case '1': {modo=POINTS;break;}
	case '2': {modo=EDGES;break;}
	case '3': {modo=SOLID;break;}
	case '4': {modo=SOLID_CHESS;break;}
        case '5': {modo=RUBIK;break;}
        // case 'P': {t_objeto=PIRAMIDE;break;}
        case 'C': {t_objeto=CUBO;break;}
        // case 'S': {t_objeto=OBJETO_PLY;break;}	
        //case 'N': {t_objeto=ROTACION;break;}
        case 'R': {t_objeto=ARTICULADO;dibujo=7;break;}
        if(dibujo == 7){
                case '-': {crubik.sentido = !crubik.sentido;break;}
                case 'W':
                {if(crubik.chanceMov('w')){
		        if(crubik.sentido) crubik.giro_1+=5;
                else crubik.giro_1-=5;
	        }       
                break;}
                case 'D':
                {if(crubik.chanceMov('d')){
		        if(crubik.sentido)crubik.giro_2+=5;
		else crubik.giro_2-=5;
	        }
                break;}
                case 'A':
                {if(crubik.chanceMov('a')){
		        if(crubik.sentido) crubik.giro_4+=5;
		else crubik.giro_4-=5;
	        }
                break;}
                case 'S':
                {if(crubik.chanceMov('s')){
		        if(crubik.sentido)crubik.giro_3+=5;
		else crubik.giro_3-=5;
	        }
                break;}
                case 'E':
                {if(crubik.chanceMov('e')){
		        if(crubik.sentido) crubik.giro_5+=5;
		else crubik.giro_5-=5;
	        }
                break;}
                case 'F':
                {if(crubik.chanceMov('f')){
		        if(crubik.sentido) crubik.giro_6+=5;
		else crubik.giro_6-=5;
	        }
                break;}
                case 'X':
                {int num_rand = 0,rant = 0;
                bool sant;
                crubik.borrarGiro();
                for(int i = 0; i < 20; i++){
			num_rand = rand()%6;
		for(int i = 0; i < 19; i++){
			switch (num_rand) {
                        case 0:
                                normal_key('W',x,y);
                        break;
                        case 1:
                                normal_key('S',x,y);
                        break;
                        case 2:
                                normal_key('D',x,y);
                        break;
                        case 3:
                                normal_key('A',x,y);
                        break;
                        case 4:
                                normal_key('E',x,y);
                        break;
                        case 5:
                                normal_key('F',x,y);
                        break;
			}
			clean_window();
			change_observer();
			draw_axis();
			draw_objects();
			glutSwapBuffers();
			std::this_thread::sleep_for(std::chrono::milliseconds(12));
		        }
	        }
                break;}
                case 'V':
                {stack<char> aux;
                aux = crubik.array_mov;
                crubik.borrarGiro();

                while(!aux.empty()){
		char char_c = aux.top();
		for(int i = 0; i < 19; i++){
			crubik.decMov(char_c);
			clean_window();
			change_observer();
			draw_axis();
			draw_objects();
			glutSwapBuffers();
			std::this_thread::sleep_for(std::chrono::milliseconds(12));
		}
		aux.pop();
                }
                while(!crubik.array_mov.empty()){
                        crubik.array_mov.pop();
                }
                break;}
        }
}
glutPostRedisplay();
}

//***************************************************************************
// Funcion l-olamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
        // case GLUT_KEY_F1:tanque.giro__tubo+=1;
        //                  if (tanque.giro__tubo>tanque.giro__tubo_max) tanque.giro__tubo=tanque.giro__tubo_max;
        //                  break;
        // case GLUT_KEY_F2:tanque.giro__tubo-=1;
        //                  if (tanque.giro__tubo<tanque.giro__tubo_min) tanque.giro__tubo=tanque.giro__tubo_min;
        //                  break;break;
        // case GLUT_KEY_F3:tanque.giro__torreta+=5;break;
        // case GLUT_KEY_F4:tanque.giro__torreta-=5;break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=20*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica cua*ply1l sera el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char **argv)
{
 

// creación del objeto ply

// ply.parametros(argv[1]);


// // perfil 

// vector<_vertex3f> perfil2;
// _vertex3f aux;
// aux.x=1.0;aux.y=-1.4;aux.z=0.0;
// perfil2.push_back(aux);
// aux.x=1.0;aux.y=-1.1;aux.z=0.0;
// perfil2.push_back(aux);
// aux.x=0.5;aux.y=-0.7;aux.z=0.0;
// perfil2.push_back(aux);
// aux.x=0.4;aux.y=-0.4;aux.z=0.0;
// perfil2.push_back(aux);
// aux.x=0.4;aux.y=0.5;aux.z=0.0;
// perfil2.push_back(aux);
// aux.x=0.5;aux.y=0.6;aux.z=0.0;
// perfil2.push_back(aux);
// aux.x=0.3;aux.y=0.6;aux.z=0.0;
// perfil2.push_back(aux);
// aux.x=0.5;aux.y=0.8;aux.z=0.0;
// perfil2.push_back(aux);
// aux.x=0.55;aux.y=1.0;aux.z=0.0;
// perfil2.push_back(aux);
// aux.x=0.5;aux.y=1.2;aux.z=0.0;
// perfil2.push_back(aux);
// aux.x=0.3;aux.y=1.4;aux.z=0.0;
// perfil2.push_back(aux);
// rotacion.parametros(perfil2,6,1);


// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 3 [RUBIK] - Nikita Stetskiy");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
