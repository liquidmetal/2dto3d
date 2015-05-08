#include <string.h>
//#include"../include/meshRenderer.h"
#define GLEW_STATIC
#include<GL/glew.h>
#include <GL/glui.h>
#include<SOIL.H>
extern void disp();
extern void read();
//extern void getImageDimensions(char*,int&,int&);
extern void computeCuboid(int *,int,int);
extern void computeCylinder(int* screen_pick);
extern  void setShaders();
extern void convertVertexToList();
extern char*name;
float xy_aspect;
int   last_x, last_y,record_clicks=0;
int screen_pick[8];
float rotationX = 0.0, rotationY = 0.0;
extern GLuint texture,cube;
extern int im_width,im_height,view_height,view_width;
/** These are the live variables passed into GLUI ***/
int   wireframe = 0;
int   obj_type = 1;
int   segments = 8;
int   segments2 = 8;
int radio_option;
int tex1_enabled=1;
int   light0_enabled = 1;
int   light1_enabled = 1;
float light0_intensity = 1.0;
float light1_intensity = .4;
int   main_window;
extern float scale;
int   show_sphere=1;
int   show_torus=1;
int   show_axes = 1;
int   show_text = 1;
float sphere_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
float torus_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };
extern float view_rotate[16];
extern float obj_pos[3] ;
char *string_list[] = { "Hello World!", "Foo", "Testing...", "Bounding box: on" };
int   curr_string = 0;

/** Pointers to the windows and some of the controls we'll create **/
GLUI *glui, *glui2;
GLUI_Spinner    *light0_spinner, *light1_spinner;
GLUI_RadioGroup *radio;
GLUI_Panel      *obj_panel;

/********** User IDs for callbacks ********/
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT0_INTENSITY_ID  250
#define LIGHT1_INTENSITY_ID  260
#define TEXTURE_ENABLED_ID 400
#define ENABLE_ID            300
#define DISABLE_ID           301
#define SHOW_ID              302
#define HIDE_ID              303
#define RADIO_BUTTON_ID 500


/********** Miscellaneous global variables **********/

GLfloat light0_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat light0_diffuse[] =  {.6f, .6f, 1.0f, 1.0f};
GLfloat light0_position[] = {.5f, .5f, 1.0f, 0.0f};

GLfloat light1_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat light1_diffuse[] =  {.9f, .6f, 0.0f, 1.0f};
GLfloat light1_position[] = {-1.0f, -1.0f, 1.0f, 0.0f};

extern GLfloat lights_rotation[16];

/**************************************** control_cb() *******************/
/* GLUI control callback                                                 */

void control_cb( int control )
{
  if ( control == LIGHT0_ENABLED_ID ) {
    if ( light0_enabled ) {
      glEnable( GL_LIGHT0 );
      light0_spinner->enable();
    }
    else {
      glDisable( GL_LIGHT0 );
      light0_spinner->disable();
    }
  }
  else if ( control == LIGHT1_ENABLED_ID ) {
    if ( light1_enabled ) {
      glEnable( GL_LIGHT1 );
      light1_spinner->enable();
    }

    else {
      glDisable( GL_LIGHT1 );
      light1_spinner->disable();
    }
  }
   else if ( control == TEXTURE_ENABLED_ID ) {
    if ( tex1_enabled ) {
        glEnable(GL_TEXTURE_2D);

    }
    else{
           // texture=0;
            //glBindTexture(GL_TEXTURE_2D,0);
        glDisable( GL_TEXTURE_2D );

    }
     }

  else if ( control == LIGHT0_INTENSITY_ID ) {
    float v[] = {
      light0_diffuse[0],  light0_diffuse[1],
      light0_diffuse[2],  light0_diffuse[3] };

    v[0] *= light0_intensity;
    v[1] *= light0_intensity;
    v[2] *= light0_intensity;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, v );
  }
  else if ( control == LIGHT1_INTENSITY_ID ) {
    float v[] = {
      light1_diffuse[0],  light1_diffuse[1],
      light1_diffuse[2],  light1_diffuse[3] };

    v[0] *= light1_intensity;
    v[1] *= light1_intensity;
    v[2] *= light1_intensity;

    glLightfv(GL_LIGHT1, GL_DIFFUSE, v );
  }
  else if ( control == ENABLE_ID )
  {
    glui2->enable();
  }
  else if ( control == DISABLE_ID )
  {
    glui2->disable();
  }
  else if ( control == SHOW_ID )
  {
    glui2->show();
  }
  else if ( control == HIDE_ID )
  {
    glui2->hide();
  }
}

/**************************************** myGlutKeyboard() **********/

void myGlutKeyboard(unsigned char Key, int x, int y)
{
  switch(Key)
  {
  case 27:
  case 'q':
    exit(0);
    break;
  };

  glutPostRedisplay();
}


/***************************************** myGlutMenu() ***********/

void myGlutMenu( int value )
{
  myGlutKeyboard( value, 0, 0 );
}


/***************************************** myGlutIdle() ***********/

void myGlutIdle( void )
{
  if ( glutGetWindow() != main_window )
    glutSetWindow(main_window);
  glutPostRedisplay();
}

/***************************************** myGlutMouse() **********/

void myGlutMouse(int button, int button_state, int x, int y )
{
        int tx,ty,tw,th;
        GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
//printf("Screen click %d %d\n",x,y);

                if (button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN){
                         if(record_clicks < 4){
                                screen_pick[2*record_clicks]=x;
                                screen_pick[2*record_clicks+1]=th-y;
                        }
                        ++record_clicks;

                        if(record_clicks ==4){
                                if(radio_option == 0)
                                        computeCuboid(screen_pick,tw,th);
                                else
                                        computeCylinder(screen_pick);
                                record_clicks=100;
                        }
                }
}
/***************************************** myGlutMotion() **********/

void myGlutMotion(int x, int y )
{
  glutPostRedisplay();
}

/**************************************** myGlutReshape() *************/

void myGlutReshape( int x, int y )
{
  int tx, ty, tw, th;
  GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
  glViewport( tx, ty, tw, th );
view_width = tw;
view_height =th;
  xy_aspect = (float)tw / (float)th;
printf("Reshape x ,y %d %d %d %d\n" ,tx,ty,tw,th);
  glutPostRedisplay();
}



/**************************************** main() ********************/

int main(int argc, char* argv[])
{

 name=argv[1];
//read();
//convertVertexToList();
  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowPosition( 0, 0 );
  glutInitWindowSize( 650, 650 );
  //glViewport( 0, 0, 600,600 );

  main_window = glutCreateWindow( "Mesh Rendering" );
 // getImageDimensions("F:\\2DTO3D\\cuboid.jpg",im_width,im_height);
  //printf("Image width %d and height %d",im_width,im_height);
im_width=atoi(argv[2]);
im_height=atoi(argv[3]);
  glutDisplayFunc( disp );

  GLUI_Master.set_glutReshapeFunc( myGlutReshape );
  GLUI_Master.set_glutKeyboardFunc( myGlutKeyboard );
  GLUI_Master.set_glutSpecialFunc( NULL );
  GLUI_Master.set_glutMouseFunc( myGlutMouse );
  glutMotionFunc( myGlutMotion );

glEnable( GL_TEXTURE_2D );

 cube = SOIL_load_OGL_texture
	(
		//"../1.jpg",
		"F:\\2DTO3D\\box.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|SOIL_FLAG_MIPMAPS/*|SOIL_FLAG_TEXTURE_REPEATS*/
		);

    if( 0 == cube)
{
	printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
}


 texture = SOIL_load_OGL_texture
	(
		//"../1.jpg",
		"F:\\horseply\\src\\Tulips.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y|SOIL_FLAG_MIPMAPS/*|SOIL_FLAG_TEXTURE_REPEATS*/
		);

    if( 0 == texture)
{
	printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
}
 //glBindTexture(GL_TEXTURE_2D,texture);
glDisable(GL_TEXTURE_2D);

glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //glEnable(GL_LIGHTING);
  glEnable( GL_NORMALIZE );

  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);


  glEnable(GL_DEPTH_TEST);

  glui = GLUI_Master.create_glui_subwindow( main_window,
			    GLUI_SUBWINDOW_RIGHT );




  GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Lights", false );

  GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Light 1" );
  GLUI_Panel *light1 = new GLUI_Panel( roll_lights, "Light 2" );


  new GLUI_Checkbox( light0, "Enabled", &light0_enabled,
                     LIGHT0_ENABLED_ID, control_cb );
  light0_spinner =
    new GLUI_Spinner( light0, "Intensity:",
                      &light0_intensity, LIGHT0_INTENSITY_ID,
                      control_cb );
  light0_spinner->set_float_limits( 0.0, 1.0 );
  GLUI_Scrollbar *sb;
  sb = new GLUI_Scrollbar( light0, "Red",GLUI_SCROLL_HORIZONTAL,
                           &light0_diffuse[0],LIGHT0_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);
  sb = new GLUI_Scrollbar( light0, "Green",GLUI_SCROLL_HORIZONTAL,
                           &light0_diffuse[1],LIGHT0_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);
  sb = new GLUI_Scrollbar( light0, "Blue",GLUI_SCROLL_HORIZONTAL,
                           &light0_diffuse[2],LIGHT0_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);
  new GLUI_Checkbox( light1, "Enabled", &light1_enabled,
                     LIGHT1_ENABLED_ID, control_cb );
  light1_spinner =
    new GLUI_Spinner( light1, "Intensity:",
                      &light1_intensity, LIGHT1_INTENSITY_ID,
                      control_cb );
  light1_spinner->set_float_limits( 0.0, 1.0 );
  sb = new GLUI_Scrollbar( light1, "Red",GLUI_SCROLL_HORIZONTAL,
                           &light1_diffuse[0],LIGHT1_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);
  sb = new GLUI_Scrollbar( light1, "Green",GLUI_SCROLL_HORIZONTAL,
                           &light1_diffuse[1],LIGHT1_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);
  sb = new GLUI_Scrollbar( light1, "Blue",GLUI_SCROLL_HORIZONTAL,
                           &light1_diffuse[2],LIGHT1_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);

  new GLUI_Checkbox( glui, "Texture Enabled", &tex1_enabled,
                     TEXTURE_ENABLED_ID, control_cb );
GLUI_Panel *obj_panel = glui->add_panel( "Primitive Type" );
 GLUI_RadioGroup *group1 =
 glui->add_radiogroup_to_panel(obj_panel,&radio_option,RADIO_BUTTON_ID,control_cb);
 glui->add_radiobutton_to_group( group1, "Cuboid" );
 glui->add_radiobutton_to_group( group1, "Cylinder" );


  new GLUI_Button( glui, "Quit", 0,(GLUI_Update_CB)exit );

  glui->set_main_gfx_window( main_window );


  /*** Create the bottom subwindow ***/
  glui2 = GLUI_Master.create_glui_subwindow( main_window,
                                             GLUI_SUBWINDOW_TOP );
  glui2->set_main_gfx_window( main_window );

  GLUI_Rotation *view_rot = new GLUI_Rotation(glui2, "Model", view_rotate );
  view_rot->set_spin( 1.0 );

  new GLUI_Column( glui2, false );
  GLUI_Rotation *lights_rot = new GLUI_Rotation(glui2, "Light 1", lights_rotation );
  lights_rot->set_spin( .82 );
  new GLUI_Column( glui2, false );
  GLUI_Translation *trans_xy =
    new GLUI_Translation(glui2, "Objects XY", GLUI_TRANSLATION_XY, obj_pos );
  trans_xy->set_speed( .5 );
  new GLUI_Column( glui2, false );
  GLUI_Translation *trans_x =
    new GLUI_Translation(glui2, "Objects X", GLUI_TRANSLATION_X, obj_pos );
  trans_x->set_speed( .5 );
  new GLUI_Column( glui2, false );
  GLUI_Translation *trans_y =
    new GLUI_Translation( glui2, "Objects Y", GLUI_TRANSLATION_Y, &obj_pos[1] );
  trans_y->set_speed( .5 );
  new GLUI_Column( glui2, false );
  GLUI_Translation *trans_z =
    new GLUI_Translation( glui2, "Objects Z", GLUI_TRANSLATION_Z, &scale );
  trans_z->set_speed( .05 );

#if 0
  /**** We register the idle callback with GLUI, *not* with GLUT ****/
  GLUI_Master.set_glutIdleFunc( myGlutIdle );
#endif

  /**** Regular GLUT main loop ****/
//glewInit();
//setShaders();
  glutMainLoop();

  return EXIT_SUCCESS;
}
