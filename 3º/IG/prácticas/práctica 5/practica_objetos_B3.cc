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
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, ARTICULADO, CILINDRO, CONO, ESFERA} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
// int Window_x=50,Window_y=50,Window_width=450,Window_high=450;

int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=450,UI_window_height=450;

int estadoRaton[3], xc, yc, cambio=0;

// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion;
_cilindro cilindro;
_cono cono;
_esfera esfera;
_cuborubik crubik(2.0);
int dibujo = -1;
float alfa = 0.0;
float beta = -300.0;
vector<_triangulos3D> objetos;
int Ancho=450, Alto=450;

// _objeto_ply *ply1;

void pick_color(int x, int y);

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

// formato(x_minimo,x_maximo, y_minimo, y_maximo,Front_plane, plano_traser)
//  Front_plane>0  Back_plane>PlanoDelantero)
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
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

float r1 = 1.0,g1 = 0.0, b1 = 0.0;

void draw_objects()
{

	if(dibujo != -1){
		if(dibujo == 7)
			crubik.draw(modo,r1,g1,b1,3);
		else if(dibujo == 2){
			glPushMatrix();
			glScalef(3,3,3);
			if(objetos[dibujo].renderIsSelect)glLoadName(dibujo+1);
			objetos[dibujo].draw(modo,r1,g1,b1,0.0,1.0,0.0,2);
			glPopMatrix();
		}
		else{
			if(objetos[dibujo].renderIsSelect)glLoadName(dibujo+1);
			objetos[dibujo].draw(modo,r1,g1,b1,0.0,1.0,0.0,2);
		}
	}

// switch (t_objeto){
// 	case CUBO: {cubo.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;}
// 	case PIRAMIDE: {piramide.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;}
//         case OBJETO_PLY: {ply.draw(modo,1.0,0.6,0.0,0.0,1.0,0.3,2);break;}
//         case ROTACION: {rotacion.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;}
// 	case CILINDRO: {cilindro.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;}
// 	case CONO: {cono.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;}
// 	case ESFERA: {esfera.draw(modo,1.0,0.0,0.0,0.0,1.0,0.0,2);break;}
//         case ARTICULADO: {crubik.draw(modo,1.0,0.0,0.0,3);break;}
// 	}

}

void luces (float alfa, float beta){
  GLfloat luz_ambiente [] = {0.2, 0.2, 0.2, 1.0},
          luz1 [] = {1.0, 1.0, 1.0, 1.0},
          pos1 [] = {0.0, 0.0, 30.0, 1.0},
          luz2 [] = {0.2, 1.0, 0.5, 1.0},
          pos2 [] = {-20.0, 0.0, 0.0, 1.0};

  glLightfv (GL_LIGHT0, GL_AMBIENT, luz_ambiente);
  glLightfv (GL_LIGHT1, GL_DIFFUSE, luz1);
  glLightfv (GL_LIGHT1, GL_SPECULAR, luz1);

  glLightfv (GL_LIGHT2, GL_DIFFUSE, luz2);
  glLightfv (GL_LIGHT2, GL_SPECULAR, luz2);

  glPushMatrix();
  glRotatef(alfa, 0, 1, 0);
  glLightfv (GL_LIGHT1, GL_POSITION, pos1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, beta, 0);
  glLightfv (GL_LIGHT2, GL_POSITION, pos2);
  glPopMatrix();


  glDisable (GL_LIGHT0);
  glEnable (GL_LIGHT1);
  glEnable (GL_LIGHT2);
}

//**************************************************************************
//
//***************************************************************************

void draw(void)
{
clean_window();
change_observer();
luces(alfa, beta);
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

void change_window_size(int Ancho1,int Alto1)	//camaras
{
change_projection();
Ancho=Ancho1;
Alto=Alto1;
draw();
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
        case '6': {modo=SOLID_ILLUMINATED_FLAT;break;}
        case '7': {modo=SOLID_ILLUMINATED_GOURAUD;break;}
        case '8': {modo=SOLID_MULTICOLOR;break;}
        case 'T': {t_objeto=PIRAMIDE;dibujo=0;break;}
        case 'Y': {t_objeto=CUBO;dibujo=1;break;}
        case 'U': {t_objeto=OBJETO_PLY;dibujo=2;break;}
        case 'O': {t_objeto=CILINDRO;dibujo=3;break;}
        case 'P': {t_objeto=ESFERA;dibujo=4;break;}
        case 'L': {t_objeto=CONO;dibujo=5;break;}
        case 'I': {t_objeto=ROTACION;dibujo=6;break;}
        case 'R': {t_objeto=ARTICULADO;dibujo=7;break;}
        case '5': {
                if(dibujo!=7) modo = POINTS;
                else modo=RUBIK;
                break;
                }
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
        case GLUT_KEY_F5:alfa+=5;break;
        case GLUT_KEY_F6:
                if(beta>300)
                beta=-100;
                else
                beta+=5;
                break;
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
// Funciones para manejo de eventos del ratón
//***************************************************************************

void clickRaton( int boton, int estado, int x, int y )
{
if(boton== GLUT_RIGHT_BUTTON) {
   if( estado == GLUT_DOWN) {
      estadoRaton[2] = 1;
      xc=x;
      yc=y;
     } 
   else estadoRaton[2] = 1;
   }
if(boton== GLUT_LEFT_BUTTON) {
  if( estado == GLUT_DOWN) {
      estadoRaton[2] = 2;
      xc=x;
      yc=y;
      pick_color(xc, yc);
    } 
  }
}

/*************************************************************************/

void getCamara (GLfloat *x, GLfloat *y)
{
*x=Observer_angle_x;
*y=Observer_angle_y;
}

/*************************************************************************/

void setCamara (GLfloat x, GLfloat y)
{
Observer_angle_x=x;
Observer_angle_y=y;
}



/*************************************************************************/

void RatonMovido( int x, int y )
{
float x0, y0, xn, yn; 
if(estadoRaton[2]==1) 
    {getCamara(&x0,&y0);
     yn=y0+(y-yc);
     xn=x0-(x-xc);
     setCamara(xn,yn);
     xc=x;
     yc=y;
     glutPostRedisplay();
    }
}


//***************************************************************************
// Funciones para la seleccion
//************************************************************************


void procesar_color(GLint hits, GLuint *names)
{
        

        if(names[3] > 0){
		if(dibujo == 7){
			int n = names[3]-1;				
			if(!crubik.rubik[n].seleccionado){
				for(int i = 0; i < crubik.rubik[n].color.size();i++){
					crubik.rubik[n].color[i].x = 0.0;
					crubik.rubik[n].color[i].y = 0.0;
					crubik.rubik[n].color[i].z = 0.0;
				}
				crubik.rubik[n].seleccionado = true;
			}
			else{
				crubik.rubik[n].reajustarColor();
				crubik.rubik[n].seleccionado = false;
			}
		}
		else if(!objetos[dibujo].seleccionado){
			r1 = 0.0;
			g1 = 1.0;
			b1 = 0.0;
			objetos[dibujo].seleccionado = true;
		}
		else{
			r1 = 1.0;
			g1 = 0.0;
			b1 = 0.0;
			objetos[dibujo].seleccionado = false;
		}
	}                 
}



void pick_color(int x, int y)
{
if(dibujo==7)crubik.renderIsSelect = true;
else objetos[dibujo].renderIsSelect = true;
GLuint selectBuf[100]={0};
GLint viewport[4], hits=0;
// Declarar buffer de selección
glSelectBuffer(100, selectBuf);
// Obtener los parámetros del viewport
glGetIntegerv (GL_VIEWPORT, viewport);
// Pasar OpenGL a modo selección
glRenderMode (GL_SELECT);
glInitNames(); glPushName(0);
// Fijar la transformación de proyección para la selección
glMatrixMode (GL_PROJECTION);
glLoadIdentity ();
gluPickMatrix (x,(viewport[3] - y),2.0, 2.0, viewport);
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
// Dibujar la escena
draw();
// Pasar OpenGL a modo render
hits = glRenderMode (GL_RENDER);
if(dibujo==7)crubik.renderIsSelect = false;
else objetos[dibujo].renderIsSelect = false;
// Restablecer la transformación de proyección
glMatrixMode (GL_PROJECTION);
glLoadIdentity();
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
// Procesar el contenido del buffer de selección
procesar_color(hits, selectBuf);
// Dibujar la escena para actualizar cambios
draw(); 
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{

// se inicalizan la ventana y los planos de corte
// Size_x=0.5;
// Size_y=0.5;
Window_width=.5;
Window_height=.5;
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
glViewport(0,0,UI_window_width,UI_window_height);

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

// perfil 

vector<_vertex3f> perfil2;
_vertex3f aux;


ply.parametros(argv[1]);

aux.x=1.0;aux.y=-1.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.0;aux.y=-1.1;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.5;aux.y=-0.7;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=-0.4;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.4;aux.y=1.0;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.6;aux.y=1.1;aux.z=0.0;
perfil2.push_back(aux);
aux.x=0.8;aux.y=1.2;aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.0;aux.y=1.6;aux.z=0.0;
perfil2.push_back(aux);
aux.x=1.4;aux.y=2.0;aux.z=0.0;
perfil2.push_back(aux);

rotacion.parametros(perfil2,6);

// perfil del cilindro

cilindro.rotacion();

// perfil del cono

cono.rotacion();

// perfil de la esfera

esfera.rotacion();


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
glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(UI_window_width,UI_window_height);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("Practica 5 - Nikita Stetskiy");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "tecla_normal" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

// eventos ratón
glutMouseFunc( clickRaton );
glutMotionFunc( RatonMovido );

objetos.push_back(piramide);
objetos.push_back(cubo);
objetos.push_back(ply);
objetos.push_back(cilindro);
objetos.push_back(esfera);
objetos.push_back(cono);
objetos.push_back(rotacion);

// funcion de inicialización
initialize();

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
