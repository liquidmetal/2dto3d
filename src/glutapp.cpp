
#include<Windows.h>
#include<GL/glut.h>
#include "glutapp.h"
GlutApp::GlutApp(int& argc,char* argv[])
{
        glutInit(&argc,argv);
        glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
        glutInitWindowSize(600,600);
        glutInitWindowPosition(0,0);
        glutCreateWindow("Mesh Rendering");
}
void GlutApp :: init(){
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glEnable(GL_DEPTH_TEST);
//glOrtho(-10.0,10.0,-10.0,10.0,-10,10); /*Use this for the hand.ply */
//glOrtho(-10,10,-10,10,-10*100,10*100);
glOrtho(-400,400,-400,400,-1400,1400);
glMatrixMode(GL_MODELVIEW);
glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
glEnable(GL_LIGHTING);
}
GlutApp::~GlutApp()
{
        //dtor
}
