#ifndef MESH_H
#define MESH_H
#define CUBE 0
#define CYLINDER 1
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include"../include/glutapp.h"
#include"../include/ply.h"

#define GLEW_STATIC
#include<Windows.h>
#include<GL/glew.h>
#include<GL/glut.h>

void computeQuater(float t,float i,float j,float k,float *val);
using namespace  std;

typedef struct Vertex {
  float x,y,z;
} Vertex;

typedef struct Face {

  unsigned char nverts;
  int *verts;
  float nx,ny,nz;
} Face;
float scale = 1.0;
float obj_pos[] = { 0.0, 0.0, 0.0 };
float view_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
GLfloat lights_rotation[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
GLfloat pos_light1[] = {0.3,0.3,0.3,1} ;
GLfloat pos_light2[] = {0.1 ,1, 0, 1.0 };
GLuint texture,v,f,p,cube;
int flag =0;
int im_width=0, im_height=0,view_width,view_height;
float m_left=-400*2,m_bottom=-400*2,m_right=400*2,m_top=400*2,m_near=-1500,m_far=1500;
float origin[3];
GLfloat *face_normals;
float *vnorms;
Vertex **vlist;
Face **flist;
Vertex **light_list;
char *name;
int faces,vertices,show_mesh=0;
float *list;
float x_trans,y_trans,z_trans;
float x_rot=0,y_rot=0,z_rot=0,delta_rot =5;
float *perVertexNormals;
extern int tex1_enabled,screen_pick[8],radio_option;

float u1[3],u2[3],radius,cx,cy,cz,tilt;
void read();                                                //Read the ply file
void write_file(Vertex** vlist,int);
Vertex* computeNormal(int face );       // Compute Normals of each surface
void computeLightVector();                     // compute Light Vector to each vertex
void convertVertexToList();             // Generate Vertex Array
void disp();                                           //Display Function
void keyboard (unsigned char key, int x, int y);
//void scale(int key, int x, int y);
void doRotation(float deg,float x,float y,float z);
void perVertexNormal();
void setShaders();

float* resultant(float * a, float*b);
void DrawCircle(float cx, float cy, float r, int num_segments);
#endif
