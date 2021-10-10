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
  b_normales_caras=false;
  b_normales_vertices=false;

  ambiente_difusa=_vertex4f(0.2,0.4,0.9,1.0); //coeficiente ambiente y difuso
  especular=_vertex4f(0.7,0.7,0.7,1.0);
  brillo=40;
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

void _triangulos3D::draw_solido_multicolor(colores vector[])
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBegin(GL_TRIANGLES);
	
	for (int i = 0; i < caras.size(); i++)
	{
		glColor3f(vector[i].r, vector[i].g, vector[i].b);
		glVertex3fv((GLfloat *)&vertices[caras[i]._0]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._1]);
		glVertex3fv((GLfloat *)&vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo iluminación plana
//*************************************************************************

void _triangulos3D::draw_iluminacion_plana()
{
int i;
if (b_normales_caras==false) calcular_normales_caras();

glShadeModel(GL_FLAT);
glEnable (GL_LIGHTING);
glEnable (GL_NORMALIZE);

glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) &especular);
glMaterialf(GL_FRONT, GL_SHININESS, brillo);

glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
  glNormal3fv((GLfloat *) &normales_caras[i]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
glDisable(GL_LIGHTING);
}

//*************************************************************************
// dibujar en modo iluminación suave
//*************************************************************************

void _triangulos3D::draw_iluminacion_suave()
{
int i;
if (b_normales_caras==false) calcular_normales_caras();
if (b_normales_vertices==false) calcular_normales_vertices();

glEnable (GL_LIGHTING);
glShadeModel (GL_SMOOTH);
glEnable (GL_NORMALIZE);

glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difusa);
glMaterialfv(GL_FRONT, GL_SPECULAR, (GLfloat *) &especular);
glMaterialf(GL_FRONT, GL_SHININESS, brillo);

glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

glBegin(GL_TRIANGLES);
for (i=0;i<caras.size();i++){
  glNormal3fv((GLfloat *) &normales_vertices[caras[i]._0]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
  glNormal3fv((GLfloat *) &normales_vertices[caras[i]._1]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
  glNormal3fv((GLfloat *) &normales_vertices[caras[i]._2]);
	glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
glEnd();
glDisable(GL_LIGHTING);
}

void _triangulos3D::calcular_normales_caras(){
normales_caras.resize(caras.size());

for(unsigned long i = 0; i<caras.size(); i++){
  // obtener 2 vectores en el triangulo y calcular el producto vectorial
  _vertex3f
    a1 = vertices[caras[i]._1]-vertices[caras[i]._0],
    a2 = vertices[caras[i]._2]-vertices[caras[i]._0],
    n=a1.cross_product(a2);
    // modulo
    float m = sqrt(n.x*n.x+n.y*n.y+n.z*n.z);
    // normalizacion
    normales_caras[i] = _vertex3f(n.x/m, n.y/m, n.z/m);
}
b_normales_caras=true;
}

void _triangulos3D::calcular_normales_vertices(){

int n,m,i;
n = vertices.size();
normales_vertices.resize(n);

for(i=0; i<n; i++){
  normales_vertices[i].x=0.0;
  normales_vertices[i].y=0.0;
  normales_vertices[i].z=0.0;
}

m = caras.size();

for (i=0; i<m; i++){
  normales_vertices[caras[i]._0]+=normales_caras[i];
  normales_vertices[caras[i]._1]+=normales_caras[i];
  normales_vertices[caras[i]._2]+=normales_caras[i];
}

b_normales_vertices=true;
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
  case SOLID_ILLUMINATED_FLAT:draw_iluminacion_plana();break;
  case SOLID_ILLUMINATED_GOURAUD:draw_iluminacion_suave();break;
  case SOLID_MULTICOLOR:
		colores vector[caras.size()];
		for (int i = 0; i < caras.size(); i++){
		vector[i].r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		vector[i].g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		vector[i].b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}
		draw_solido_multicolor(vector);
		break;
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

void _cubo::reajustarColor(){
  	color.clear();

  	color.push_back(_vertex3f(0,0.5,0.93));
	color.push_back(_vertex3f(0,1,0.5));
	color.push_back(_vertex3f(1,0.83,0));
	color.push_back(_vertex3f(1,1,1));
	color.push_back(_vertex3f(1,0,0)); 
	color.push_back(_vertex3f(0.95,0.43,0.014));
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


//*************************************************************************
// clase piramide
//*************************************************************************

_piramide::_piramide(float tam, float al)
{

	//vertices
	vertices.resize(5);
	vertices[0].x = -tam;
	vertices[0].y = 0;
	vertices[0].z = tam;
	vertices[1].x = tam;
	vertices[1].y = 0;
	vertices[1].z = tam;
	vertices[2].x = tam;
	vertices[2].y = 0;
	vertices[2].z = -tam;
	vertices[3].x = -tam;
	vertices[3].y = 0;
	vertices[3].z = -tam;
	vertices[4].x = 0;
	vertices[4].y = al;
	vertices[4].z = 0;

	caras.resize(6);
	caras[0]._0 = 0;
	caras[0]._1 = 1;
	caras[0]._2 = 4;
	caras[1]._0 = 1;
	caras[1]._1 = 2;
	caras[1]._2 = 4;
	caras[2]._0 = 2;
	caras[2]._1 = 3;
	caras[2]._2 = 4;
	caras[3]._0 = 3;
	caras[3]._1 = 0;
	caras[3]._2 = 4;
	caras[4]._0 = 3;
	caras[4]._1 = 1;
	caras[4]._2 = 0;
	caras[5]._0 = 3;
	caras[5]._1 = 2;
	caras[5]._2 = 1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************

_objeto_ply::_objeto_ply()
{
	// leer lista de coordenadas de vértices y lista de indices de vértices

	vector<float> v;
	vector<int> c;

	// Para leer el fichero
	// Obtenemos los vértices del fichero
	//using namespac _file_ply;
	_file_ply::read("beethoven", v, c);

	_vertex3f vertice;
	for (int i = 0; i < v.size(); i += 3)
	{
		vertice.x = v[i];
		vertice.y = v[i + 1];
		vertice.z = v[i + 2];

		vertices.push_back(vertice);
	}

	_vertex3i cara;
	for (int i = 0; i < c.size(); i += 3)
	{
		cara.x = c[i];
		cara.y = c[i + 1];
		cara.z = c[i + 2];

		caras.push_back(cara);
	}
}

//************************************************************************
// objeto por revolucion
//************************************************************************

_rotacion::_rotacion()
{
}


void _rotacion::parametros(vector<_vertex3f> perfil, int num)
{
	int i, j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// TRATAMIENTO VERTICES

	num_aux = perfil.size();
	vertices.resize(num_aux * num);
	for (j = 0; j < num; j++)
	{
		for (i = 0; i < num_aux; i++)
		{
			vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
							perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));
			vertice_aux.z = -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
							perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));
			vertice_aux.y = perfil[i].y;
			vertices[i + j * num_aux] = vertice_aux;
		}
	}

	// TRATEMIENTO CARAS

	for (j = 0; j < num; j++)
	{
		for (i = 0; i < num_aux - 1; i++)
		{
			cara_aux._0 = i + ((j + 1) % num) * num_aux;
			cara_aux._1 = i + 1 + ((j + 1) % num) * num_aux;
			cara_aux._2 = i + 1 + j * num_aux;
			caras.push_back(cara_aux);

			cara_aux._0 = i + 1 + j * num_aux;
			cara_aux._1 = i + j * num_aux;
			cara_aux._2 = i + ((j + 1) % num) * num_aux;
			caras.push_back(cara_aux);
		}
	}
	// TAPA INFERIOR
	if (fabs(perfil[0].x) > 0.0)
	{
		vertice_aux.y = perfil[0].y;
		vertice_aux.x = 0.0;
		vertice_aux.z = 0.0;
		vertices.push_back(vertice_aux);

		cara_aux._0 = num_aux * num + 1;

		for (int i = 0; i < num; i++)
		{
			cara_aux._1 = ((i + 1) % num) * num_aux;
			cara_aux._2 = i * num_aux;
			caras.push_back(cara_aux);
		}
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
  int k = 1;
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
		if(renderIsSelect)glLoadName(k); 
        glTranslatef(k1+q1, k2+q3, k3+q2);
        glScalef(escala,escala,escala);
        rubik[c].draw(modo, r, g, b, 0, 0, 0, grosor);
        glPopMatrix();
		k++;
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

//*********************************************
// objeto por revolucion CILINDRO
//*********************************************

_cilindro::_cilindro(float r, float h, int n, int tapitas)
{

	num = n;
	this->tapitas = tapitas;
	_vertex3f aux;

	aux.z = 0.0;
	aux.x = r;
	aux.y = h;
	perfil.push_back(aux);

	aux.z = 0.0;
	aux.x = r;
	aux.y = -h;
	perfil.push_back(aux);
}

void _cilindro::rotacion()
{
	int i, j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// TRATAMIENTO VERTICES

	num_aux = perfil.size();
	vertices.resize(num_aux * num);

	for (j = 0; j < num; j++)
	{
		for (i = 0; i < num_aux; i++)
		{
			vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
							perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));
			vertice_aux.z = -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
							perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));
			vertice_aux.y = perfil[i].y;
			vertices[i + j * num_aux] = vertice_aux;
		}
	}

	// TRATAMIENTO CARAS

	for (j = 0; j < num; j++)
	{
		for (i = 0; i < num_aux - 1; i++)
		{
			cara_aux._0 = i + ((j + 1) % num) * num_aux;
			cara_aux._1 = i + 1 + ((j + 1) % num) * num_aux;
			cara_aux._2 = i + 1 + j * num_aux;
			caras.push_back(cara_aux);

			cara_aux._0 = i + 1 + j * num_aux;
			cara_aux._1 = i + j * num_aux;
			cara_aux._2 = i + ((j + 1) % num) * num_aux;
			caras.push_back(cara_aux);
		}
	}

	// TAPA SUPERIOR

	if (fabs(perfil[0].x) > 0.0 && (tapitas == 1 || tapitas == 3))
	{
		vertice_aux.x = 0;
		vertice_aux.y = perfil[0].y;
		vertice_aux.z = 0;
		vertices.push_back(vertice_aux);

		for (i = 0; i < num_aux * num; i += 2)
		{
			cara_aux._0 = vertices.size() - 1;
			cara_aux._1 = i;
			cara_aux._2 = (i + 2) % (vertices.size() - 1);
			caras.push_back(cara_aux);
		}
	}

	// TAPA - INFERIOR

	if (fabs(perfil[num_aux - 1].x) > 0.0 && (tapitas == 2 || tapitas == 3))
	{
		vertice_aux.x = 0;
		vertice_aux.y = perfil[1].y;
		vertice_aux.z = 0;
		vertices.push_back(vertice_aux);

		for (i = 1; i < num_aux * num; i += 2)
		{
			cara_aux._0 = vertices.size() - 1;
			cara_aux._1 = (i + 2) % (vertices.size() - 2);
			cara_aux._2 = i;
			caras.push_back(cara_aux);
		}
	}
}

//************************************************************************
// objeto por revolucion CONO
//************************************************************************

_cono::_cono(float r, float h, int n, bool tapitas)
{

	num = n;
	this->tapitas = tapitas;
	_vertex3f aux;

	aux.x = 0.0;
	aux.y = h;
	aux.z = 0.0;
	perfil.push_back(aux);
	aux.x = r;
	aux.y = 0.0;
	aux.z = 0.0;
	perfil.push_back(aux);
}

void _cono::rotacion()
{
	int i, j;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// VERTICES

	num_aux = 1;
	vertices.resize(num_aux + num);
	vertices[0] = perfil[0];

	for (j = 0; j < num; j++)
	{
		vertice_aux.x = perfil[num_aux].x * cos(2.0 * M_PI * j / (1.0 * num)) +
						perfil[num_aux].z * sin(2.0 * M_PI * j / (1.0 * num));
		vertice_aux.z = -perfil[num_aux].x * sin(2.0 * M_PI * j / (1.0 * num)) +
						perfil[num_aux].z * cos(2.0 * M_PI * j / (1.0 * num));
		vertice_aux.y = perfil[num_aux].y;
		vertices[num_aux + j] = vertice_aux;
	}

	// CARAS

	for (i = 0; i < num - 1; i++)
	{
		cara_aux._0 = 0;
		cara_aux._1 = i + 1;
		cara_aux._2 = (i + 2) % (num + num_aux);
		caras.push_back(cara_aux);
	}

	cara_aux._0 = 0;
	cara_aux._1 = num;
	cara_aux._2 = 1;
	caras.push_back(cara_aux);

	// TAPA - INFERIOR

	if (fabs(perfil[1].x) > 0.0 && tapitas)
	{
		vertice_aux.x = 0;
		vertice_aux.y = perfil[1].y;
		vertice_aux.z = 0;
		vertices.push_back(vertice_aux);

		for (i = 0; i < num - 1; i++)
		{
			cara_aux._0 = vertices.size() - 1;
			cara_aux._1 = i + 2;
			cara_aux._2 = i + 1;
			caras.push_back(cara_aux);
		}

		cara_aux._0 = vertices.size() - 1;
		cara_aux._1 = 1;
		cara_aux._2 = vertices.size() - 2;
		caras.push_back(cara_aux);
	}
}

//************************************************************************
// objeto por revolucion ESFERA
//************************************************************************

_esfera::_esfera(float r, int lat, int lon, int tapitas)
{

	num = lon;
	this->tapitas = tapitas;
	_vertex3f aux;

	float increRad = M_PI / lat;
	float angulo = 0;

	aux.x = 0.0;
	aux.y = r;
	aux.z = 0.0;
	perfil.push_back(aux);

	for (int i = 0; i < lat - 1; ++i)
	{
		angulo += increRad;

		aux.x = r * sin(angulo);
		aux.y = r * cos(angulo);
		aux.z = 0.0;

		perfil.push_back(aux);
	}

	aux.x = 0.0;
	aux.y = -r;
	aux.z = 0.0;
	perfil.push_back(aux);
}

void _esfera::rotacion()
{
	int i, j, k;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// VERTICES

	num_aux = perfil.size();
	vertices.resize((perfil.size() - 2) * num + 2);

	vertices[vertices.size() - 2] = perfil[0];
	vertices[vertices.size() - 1] = perfil[perfil.size() - 1];

	k = 0;
	for (j = 0; j < num; j++)
	{
		for (i = 1; i < num_aux - 1; i++)
		{
			vertice_aux.z = -perfil[i].x * sin(2.0 * M_PI * j / (1.0 * num)) +
							perfil[i].z * cos(2.0 * M_PI * j / (1.0 * num));
			vertice_aux.x = perfil[i].x * cos(2.0 * M_PI * j / (1.0 * num)) +
							perfil[i].z * sin(2.0 * M_PI * j / (1.0 * num));
			vertice_aux.y = perfil[i].y;
			vertices[k] = vertice_aux;
			++k;
		}
	}

	// CARAS

	for (j = 0; j < num; j++)
	{
		for (i = 0; i < num_aux - 3; i++)
		{
			cara_aux._0 = i + ((j + 1) % num) * (num_aux - 2);
			cara_aux._1 = i + 1 + j * (num_aux - 2);
			cara_aux._2 = i + 1 + ((j + 1) % num) * (num_aux - 2);
			caras.push_back(cara_aux);

			cara_aux._0 = i + 1 + j * (num_aux - 2);
			cara_aux._1 = i + ((j + 1) % num) * (num_aux - 2);
			cara_aux._2 = i + j * (num_aux - 2);
			caras.push_back(cara_aux);
		}
	}

	// TAPA - SUPERIOR

	if (fabs(perfil[0].x) == 0.0 && (tapitas == 1 || tapitas == 3))
	{
		k = perfil.size() - 2;
		cara_aux._0 = vertices.size() - 2;
		cara_aux._1 = 0;
		cara_aux._2 = perfil.size() - 2;
		caras.push_back(cara_aux);
		auto cara_aux_anterior = cara_aux;

		for (int i = 0; i < num - 2; i++)
		{
			cara_aux._0 = vertices.size() - 2;
			cara_aux._1 = cara_aux_anterior._1 + k;
			cara_aux._2 = cara_aux_anterior._2 + k;
			caras.push_back(cara_aux);
			cara_aux_anterior = cara_aux;
		}

		cara_aux._0 = vertices.size() - 2;
		cara_aux._1 = cara_aux_anterior._1 + k;
		cara_aux._2 = 0;
		caras.push_back(cara_aux);
	}

	// TAPA INFERIOR

	if (fabs(perfil[num_aux - 1].x) == 0.0 && (tapitas == 2 || tapitas == 3))
	{
		k = perfil.size() - 2;
		cara_aux._0 = vertices.size() - 1;
		cara_aux._1 = perfil.size() - 3 + perfil.size() - 2;
		cara_aux._2 = perfil.size() - 3;
		caras.push_back(cara_aux);
		auto cara_aux_anterior = cara_aux;

		for (int i = 0; i < num - 2; i++)
		{
			cara_aux._0 = vertices.size() - 1;
			cara_aux._1 = cara_aux_anterior._1 + k;
			cara_aux._2 = cara_aux_anterior._2 + k;
			caras.push_back(cara_aux);
			cara_aux_anterior = cara_aux;
		}

		cara_aux._0 = vertices.size() - 1;
		cara_aux._1 = perfil.size() - 3;
		cara_aux._2 = cara_aux_anterior._2 + k;
		caras.push_back(cara_aux);
	}
}