#include"../include/quaternion.h"
//#include<Windows.h>
#include<GL/glut.h>
void computeQuat(float t,float i,float j,float k,float *val){

float w,x,y,z;
t = (3.142*t)/180;
w = cos(t/2);
x = sin(t/2)*i;
y = sin(t/2)*j;
z = sin(t/2)*k;

float rot[] ={ 1-2*y*y-2*z*z,          2*x*y+2*w*z,              2*x*z-2*w*y,      0,
        2*x*y-2*w*z,             1-2*x*x-2*z*z,                   2*y*z+2*w*x,          0,
       2*x*z+2*w*y,            2*y*z-2*w*x,              1-2*x*x-2*y*y,                  0,
        0,                              0,                                      0,                                    1};


glMultMatrixf(rot);
glutPostRedisplay();

     val =rot;

}

