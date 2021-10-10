//**************************************************************************
// Práctica 1 usando objetos
//**************************************************************************

#include "objetos_B3.h"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D()
{
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPointSize(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawArrays(GL_POINTS,0,vertices.size()); 

/*int i;
glPointSize(grosor);
glColor3f(r,g,b);
glBegin(GL_POINTS);
for (i=0;i<vertices.size();i++){
	glVertex3fv((GLfloat *) &vertices[i]);
	}
glEnd();*/
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D()
{
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor)
{
//**** usando vertex_array ****
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);

glEnableClientState(GL_VERTEX_ARRAY);
glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);

/*int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glLineWidth(grosor);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();*/
}

//*************************************************************************
// dibujar en modo sólido
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b)
{
int i;

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glColor3f(r,g,b);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de ajedrez
//*************************************************************************

void _triangulos3D::draw_solido_ajedrez(float r1, float g1, float b1, float r2, float g2, float b2)
{
int i;
glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
	if (i%2==0) glColor3f(r1,g1,b1);
	else glColor3f(r2,g2,b2);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
}

//*************************************************************************
// dibujar en modo sólido con apariencia de rubik
//*************************************************************************

void _triangulos3D::draw_rubik(){
  int num = 0;
  int c = 0;

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glBegin(GL_TRIANGLES);
  if(caras.size() == 0) num++;
  else num = caras.size();
  for(int i = 0; i < num; i++){
    if(i%2 == 0){
      glColor3f(color[c].x, color[c].y, color[c].z);
      c++;
    }
    glVertex3fv((GLfloat *) &vertices[caras[i].x]);
    glVertex3fv((GLfloat *) &vertices[caras[i].y]);
    glVertex3fv((GLfloat *) &vertices[caras[i].z]);
  }
  glEnd();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor3f(0,0,0);
  glLineWidth(4);
  glBegin(GL_TRIANGLES);
  for(unsigned int i = 0; i < caras.size(); i++){
      glVertex3fv((GLfloat *) &vertices[caras[i].x]);
      glVertex3fv((GLfloat *) &vertices[caras[i].y]);
      glVertex3fv((GLfloat *) &vertices[caras[i].z]);
  }
  glEnd();
  glLineWidth(1);
}

//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r1, float g1, float b1, float r2, float g2, float b2, float grosor)
{
switch (modo){
	case POINTS:draw_puntos(r1, g1, b1, grosor);break;
	case EDGES:draw_aristas(r1, g1, b1, grosor);break;
	case SOLID_CHESS:draw_solido_ajedrez(r1, g1, b1, r2, g2, b2);break;
	case SOLID:draw_solido(r1, g1, b1);break;
	case RUBIK:draw_rubik();break;
	}
}

//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam)
{
	color.reserve(6);
	caras.reserve(12);
	vertices.reserve(8);

	color.push_back(_vertex3f(0,0.5,0.93));
	color.push_back(_vertex3f(0,1,0.5));
	color.push_back(_vertex3f(1,0.83,0));
	color.push_back(_vertex3f(1,1,1));
	color.push_back(_vertex3f(1,0,0)); 
	color.push_back(_vertex3f(0.95,0.43,0.014));

	vertices.push_back(_vertex3<float>(-tam/2, -tam/2, tam/2));
	vertices.push_back(_vertex3<float>(tam/2, -tam/2, tam/2));
	vertices.push_back(_vertex3<float>(-tam/2, tam/2, tam/2));
	vertices.push_back(_vertex3<float>(tam/2, tam/2, tam/2));
	vertices.push_back(_vertex3<float>(-tam/2, -tam/2, -tam/2));
	vertices.push_back(_vertex3<float>(tam/2, -tam/2, -tam/2));
	vertices.push_back(_vertex3<float>(-tam/2, tam/2, -tam/2));
	vertices.push_back(_vertex3<float>(tam/2, tam/2, -tam/2));

	caras.push_back(_vertex3<int>(0,1,2));
	caras.push_back(_vertex3<int>(1,2,3));
	caras.push_back(_vertex3<int>(4,5,6));
	caras.push_back(_vertex3<int>(5,6,7));
	caras.push_back(_vertex3<int>(0,1,4));
	caras.push_back(_vertex3<int>(1,4,5));
	caras.push_back(_vertex3<int>(2,3,6));
	caras.push_back(_vertex3<int>(3,6,7));
	caras.push_back(_vertex3<int>(0,2,4));
	caras.push_back(_vertex3<int>(2,4,6));
	caras.push_back(_vertex3<int>(1,3,5));
	caras.push_back(_vertex3<int>(3,5,7));
}

_cubo::_cubo(const _cubo &otro){
	*this = otro;
}

_cubo& _cubo::operator=(const _cubo &otro){
	vertices = otro.vertices;
	color = otro.color;
	caras = otro.caras;
	return (*this);
}

void _cubo::rotarColor(int num){
  _vertex3f aux;
	switch (num) {
		case 0:
			aux = color[3];
			color[3] = color[4];
			color[4] = color[2];
			color[2] = color[5];
			color[5] = aux;
		break;
		case 1:
			aux = color[2];
			color[2] = color[4];
			color[4] = color[3];
			color[3] = color[5];
			color[5] = aux;
		break;
		case 2:
			aux = color[0];
			color[0] = color[3];
			color[3] = color[1];
			color[1] = color[2];
			color[2] = aux;
		break;
		case 3:
			aux = color[1];
			color[1] = color[3];
			color[3] = color[0];
			color[0] = color[2];
			color[2] = aux;

		break;
		case 4:
			 aux = color[0];
			color[0] = color[4];
			color[4] = color[1];
			color[1] = color[5];
			color[5] = aux;
		break;
		case 5:
			aux = color[0];
			color[0] = color[5];
			color[5] = color[1];
			color[1] = color[4];
			color[4] = aux;
		break;
	}
}


int _objeto_ply::parametros(char *archivo)
{
int n_ver,n_car;

vector<float> ver_ply ;
vector<int>   car_ply ;
   
_file_ply::read(archivo, ver_ply, car_ply );

n_ver=ver_ply.size()/3;
n_car=car_ply.size()/3;

printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

//if (n_ver<3 || n_car<1){
//	printf("Error %d %d\n",__FILE__,__LINE__);
//	exit(-1);
//	}

vertices.resize(n_ver);
caras.resize(n_car);

_vertex3f ver_aux;
_vertex3i car_aux;

for (int i=0;i<n_ver;i++)
	{ver_aux.x=ver_ply[i*3];
	 ver_aux.y=ver_ply[i*3+1];
	 ver_aux.z=ver_ply[i*3+2];
	 vertices[i]=ver_aux;
	}

for (int i=0;i<n_car;i++)
	{car_aux.x=car_ply[i*3];
	 car_aux.y=car_ply[i*3+1];
	 car_aux.z=car_ply[i*3+2];
	 caras[i]=car_aux;
	}

return(0);
}


//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{

}


void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tapa)
{
int i,j;
_vertex3f vertice_aux;
_vertex3i cara_aux;
int num_aux;

// tratamiento de los vértice

num_aux=perfil.size();
vertices.resize(num_aux*num);
for (j=0;j<num;j++)
  {for (i=0;i<num_aux;i++)
     {
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
     }
  }

// tratamiento de las caras 

for (j=0;j<num;j++)
  {for (i=0;i<num_aux-1;i++)
     {cara_aux._0=i+((j+1)%num)*num_aux;
      cara_aux._1=i+1+((j+1)%num)*num_aux;
      cara_aux._2=i+1+j*num_aux;
      caras.push_back(cara_aux);
      
      cara_aux._0=i+1+j*num_aux;
      cara_aux._1=i+j*num_aux;
      cara_aux._2=i+((j+1)%num)*num_aux;
      caras.push_back(cara_aux);
     }
  }
     
 // tapa inferior
if (fabs(perfil[0].x)>0.0 && tapa==1)
  {
  }
 
 // tapa superior
 if (fabs(perfil[num_aux-1].x)>0.0 && tapa==1)
  {
  }
}

//************************************************************************
// objeto articulado: rubik
//************************************************************************

_cuborubik::_cuborubik(const _cuborubik &otro){
  *this = otro;
}


_cuborubik::_cuborubik(float tb){
  escala = tb;
  int tam = tamanio*tamanio*tamanio;
  giro_1 = giro_2 = giro_3 = giro_4 = giro_5 = giro_6 = 0;
  dist = escala*tamanio;

  for(int i = 0; i < tam; i++){
    rubik.push_back(_cubo(1));
  }
  int cont = 0;
  for(int i = 0; i < tamanio; i++){
    for(int j = 0; j < tamanio; j++){
      for(int k = 0; k < tamanio; k++){
        matriz_pos[i][j][k]=cont++;
      }
    }
  }
  // for(int i = 0; i < tamanio; i++){
  //   for(int j = 0; j < tamanio; j++){
  //     for(int k = 0; k < tamanio; k++){
  //       std::cout<<matriz_pos[i][j][k]<<' ';
  //     }
  //     std::cout<<endl;
  //   }
  //   std::cout<<endl;
  // }
}

bool _cuborubik::cCara3(int c){
  bool cara = false;
  for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        if(matriz_pos[i][0][j] == c)
          cara=true;
      }
  }
  return cara;
}

bool _cuborubik::cCara1(int c){
  bool cara = false;
  for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        if(matriz_pos[i][tamanio-1][j] == c)
          cara=true;
      }
  }
  return cara;
}

bool _cuborubik::cCara2(int c){
  bool cara = false;
  for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        if(matriz_pos[i][j][tamanio-1] == c)
          cara=true;
    }
  }
  return cara;
}

bool _cuborubik::cCara4(int c){
  bool cara = false;
  for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        if(matriz_pos[i][j][0] == c)
          cara=true;
    }
  }
  return cara;
}

bool _cuborubik::cCara5(int c){
  bool cara = false;
  for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        if(matriz_pos[tamanio-1][i][j] == c)
          cara=true;
    }
  }
  return cara;
}

bool _cuborubik::cCara6(int c){
  bool cara = false;
  for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        if(matriz_pos[0][i][j] == c)
          cara=true;
    }
  }
  return cara;
}

void _cuborubik::draw(_modo modo, float r, float g, float b, int grosor){
  float k1,k2,k3;
  //int 60 = tamanio*10*2;
  //int 30 = tamanio*10;
  k3 = -dist/tamanio;
  k2 = dist/tamanio;
  k1 = -dist/tamanio;
  int c = 0;
  float q1 = -0.1 ,q2 = -0.1;
  float q3 = 0.1;

  for(int i = 0; i < tamanio;i++,k2-=escala,q3-=0.1){
    for(int j = 0; j < tamanio;j++,k3+=escala,q2+=0.1){
      for(int h = 0;h < tamanio;h++,k1+=escala,c++,q1+=0.1){
        glPushMatrix();
        if(cCara1(c)){ // Azul Delante
           glRotatef(giro_1, 0, 0, 1);
        }
        if(cCara2(c)){ // Derecha
          glRotatef(giro_2, 1, 0, 0);
        }
        if(cCara3(c)){ // Detrás
          glRotatef(giro_3, 0, 0, 1);
        }
        if(cCara4(c)){ // Izquierda
           glRotatef(giro_4, 1, 0, 0);
        }
        if(cCara5(c)){ // Abajo
           glRotatef(giro_5, 0, 1, 0);
        }
        if(cCara6(c)){ // Arriba
           glRotatef(giro_6, 0, 1, 0);
        }
        glTranslatef(k1+q1, k2+q3, k3+q2);
        glScalef(escala,escala,escala);
        rubik[c].draw(modo, r, g, b, 0, 0, 0, grosor);
        glPopMatrix();
      }
      q1 = -0.1;
      k1 = -dist/tamanio;
    }
    q2 = -0.1;
    k3 = -dist/tamanio;
  }

  // Cara 1
  if((int)giro_1 < -60){
    giro_1 = 30;
    vector<_cubo> rubik_aux = rubik;
    for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        rubik[matriz_pos[i][tamanio-1][j]]=rubik_aux[matriz_pos[tamanio-1-j][tamanio-1][i]];
        rubik[matriz_pos[i][tamanio-1][j]].rotarColor(0);
      }
    }
    array_mov.push('W');
  }
  else if((int)giro_1 > 60){
    giro_1 = -30;
    vector<_cubo> rubik_aux = rubik;
    for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        rubik[matriz_pos[i][tamanio-1][j]]=rubik_aux[matriz_pos[j][tamanio-1][tamanio-1-i]];
        rubik[matriz_pos[i][tamanio-1][j]].rotarColor(1);
      }
    }
    array_mov.push('w');
  }
  else if((int)giro_2 < -60){
    giro_2 = 30;
    vector<_cubo> rubik_aux = rubik;
    for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        rubik[matriz_pos[i][j][tamanio-1]]=rubik_aux[matriz_pos[j][tamanio-1-i][tamanio-1]];
        rubik[matriz_pos[i][j][tamanio-1]].rotarColor(3);
      }
    }
    array_mov.push('D');
  }
  else if((int)giro_2 > 60){
    giro_2 = -30;
    vector<_cubo> rubik_aux = rubik;
    for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        //std::cout<<matriz_pos[i][j][tamanio-1]<<" --> "<<matriz_pos[tamanio-1-j][i][tamanio-1]<<endl;
        rubik[matriz_pos[i][j][tamanio-1]]=rubik_aux[matriz_pos[tamanio-1-j][i][tamanio-1]];
        rubik[matriz_pos[i][j][tamanio-1]].rotarColor(2);
      }
    }

    array_mov.push('d');
  }
  else if((int)giro_3 > 60){
    giro_3 = -30;
    vector<_cubo> rubik_aux = rubik;
    for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        rubik[matriz_pos[i][0][j]]=rubik_aux[matriz_pos[j][0][tamanio-1-i]];
        rubik[matriz_pos[i][0][j]].rotarColor(1);
      }
    }
    array_mov.push('s');
  }
  else if((int)giro_3 < -60){
    giro_3 = 30;
    vector<_cubo> rubik_aux = rubik;
    for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        rubik[matriz_pos[i][0][j]]=rubik_aux[matriz_pos[tamanio-1-j][0][i]];
        rubik[matriz_pos[i][0][j]].rotarColor(0);
      }
    }
    array_mov.push('S');
  }
  else if((int)giro_4 > 60){
    giro_4 = -30;
    vector<_cubo> rubik_aux = rubik;
    for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        rubik[matriz_pos[i][j][0]]=rubik_aux[matriz_pos[tamanio-1-j][i][0]];
        rubik[matriz_pos[i][j][0]].rotarColor(2);
      }
    }
    array_mov.push('a');
  }
  else if((int)giro_4 < -60){
    giro_4 = 30;
    vector<_cubo> rubik_aux = rubik;
    for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        rubik[matriz_pos[i][j][0]]=rubik_aux[matriz_pos[j][tamanio-1-i][0]];
        rubik[matriz_pos[i][j][0]].rotarColor(3);
      }
    }
    array_mov.push('A');
  }
  else if((int)giro_5 > 60){
    giro_5 = -30;
    vector<_cubo> rubik_aux = rubik;
    for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        rubik[matriz_pos[tamanio-1][i][j]]=rubik_aux[matriz_pos[tamanio-1][j][tamanio-1-i]];
        rubik[matriz_pos[tamanio-1][i][j]].rotarColor(4);
      }
    }
    array_mov.push('e');
  }
  else if((int)giro_5 < -60){
    giro_5 = 30;
    vector<_cubo> rubik_aux = rubik;
    for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        rubik[matriz_pos[tamanio-1][i][j]]=rubik_aux[matriz_pos[tamanio-1][tamanio-1-j][i]];
        rubik[matriz_pos[tamanio-1][i][j]].rotarColor(5);
      }
    }
    array_mov.push('E');
  }
  else if((int)giro_6 > 60){
    giro_6 = -30;
    vector<_cubo> rubik_aux = rubik;
    for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        rubik[matriz_pos[0][i][j]]=rubik_aux[matriz_pos[0][j][tamanio-1-i]];
        rubik[matriz_pos[0][i][j]].rotarColor(4);
      }
    }
    array_mov.push('f');
  }
  else if((int)giro_6 < -60){
    giro_6 = 30;
    vector<_cubo> rubik_aux = rubik;
    for(int i = 0; i < tamanio; i++){
      for(int j = 0; j < tamanio; j++){
        rubik[matriz_pos[0][i][j]]=rubik_aux[matriz_pos[0][tamanio-1-j][i]];
        rubik[matriz_pos[0][i][j]].rotarColor(5);
      }
    }
    array_mov.push('F');
  }
}

void _cuborubik::decMov(char m){
  switch (m) {
	case 'E':
      giro_5+=5;
    break;
    case 'e':
      giro_5-=5;
    break;
    case 'F':
      giro_6+=5;
    break;
    case 'f':
      giro_6-=5;
    break;
    case 'W':
      giro_1+=5;
    break;
    case 'w':
      giro_1-=5;
    break;
    case 'D':
      giro_2+=5;
    break;
    case 'd':
      giro_2-=5;
    break;
    case 'S':
      giro_3+=5;
    break;
    case 's':
      giro_3-=5;
    break;
    case 'A':
      giro_4+=5;
    break;
    case 'a':
      giro_4-=5;
    break;
    
  }
}

void _cuborubik::borrarGiro(){
  giro_1 = giro_2 = giro_3 = giro_4 = giro_5 = giro_6 = 0;
}

bool _cuborubik::chanceMov(char giro_) const{
  switch (giro_) {
    case 's':
    case 'w':
      return ((giro_2 >= -10 && giro_2 <= 10) &&
              (giro_4 >= -10 && giro_4 <= 10) &&
              (giro_5 >= -10 && giro_5 <= 10) &&
              (giro_6 >= -10 && giro_6 <= 10)
              );
    break;
    case 'a':
    case 'd':
    return ((giro_1 >= -10 && giro_1 <= 10) &&
            (giro_3 >= -10 && giro_3 <= 10) &&
            (giro_5 >= -10 && giro_5 <= 10) &&
            (giro_6 >= -10 && giro_6 <= 10)
            );
    break;
    case 'f':
    case 'e':
    return ((giro_1 >= -10 && giro_1 <= 10) &&
            (giro_3 >= -10 && giro_3 <= 10) &&
            (giro_2 >= -10 && giro_2 <= 10) &&
            (giro_4 >= -10 && giro_4 <= 10)
            );
    break;
  }
  return false;
}

_cuborubik& _cuborubik::operator=(const _cuborubik &otro){
  rubik = otro.rubik;
  giro_1 = otro.giro_1;
  giro_2 = otro.giro_2;
  giro_3 = otro.giro_3;
  giro_4 = otro.giro_4;
  giro_5 = otro.giro_5;
  giro_6 = otro.giro_6;
  escala = otro.escala;
  array_mov = otro.array_mov;
  movant = otro.movant;
  sentido = otro.sentido;
  return (*this);
}