#include "../include/quaternion.h"
#include "../include/meshRenderer.h"
#include"shader.h"

void doRotation(float deg,float x,float y,float z){
        float *angle = (float*)malloc(sizeof(float)*16);
        computeQuat(deg,x,y,z,angle);
}

void DrawCircle(float cx, float cy,float cz, float r, int num_segments,float *u1, float *u2,float tilt)
{
       //glRotatef(90-(tilt*180)/3.1415926f ,1,0,0);
        //glScalef(3.094778,2.08,1);
        int ii;
       vlist = (Vertex **) malloc (sizeof (Vertex *) * 34);

          /*glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_LINE_LOOP);*/
	vlist[0] = (Vertex *) malloc (sizeof (Vertex));
	vlist[0] -> x = cx;
	vlist[0] -> y= cy;
	vlist[0] -> z = cz;
	for( ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
                vlist[ii+1] = (Vertex *) malloc (sizeof (Vertex));
		/*float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component
                float z= 0;*/
                float x = cx+r*(u1[0]*cosf(theta)+u2[0]*sinf(theta));
                float y= cy+r*(u1[1]*cosf(theta)+u2[1]*sinf(theta));
                float z = cz+r*(u1[2]*cosf(theta)+u2[2]*sinf(theta));

		//glVertex3f(x + cx, y + cy,0);//output vertex
		vlist[ii+1]->x = x;
		vlist[ii+1]->y = y;
		vlist[ii+1]->z = z;
		printf("x %f  y %f  z %f\n",x,y,z);
		//glVertex3f(x,y,z);//output vertex

	}
	int count = ii+1;
	printf("Count = %d\n",count);
	//glEnd();

	//glRotatef(-(90-(tilt*180))/3.1415926f ,1,0,0);
	//glRotatef(90-(tilt*180)/3.1415926f ,1,0,0);
	//glTranslatef(0,0,-90);
	//glTranslatef(screen_pick[4]-screen_pick[2],screen_pick[5]-screen_pick[1],0);
	float z3 = sqrtf((radius*radius) -pow((screen_pick[6]-cx),2) -pow((screen_pick[7]-cy),2)  );
	float z2= -((screen_pick[4]-screen_pick[2])*screen_pick[6] +(screen_pick[5]-screen_pick[3])*screen_pick[7] )/z3;
	float axis[3] ={screen_pick[4]-screen_pick[2],screen_pick[5]-screen_pick[3],z2};

                float nx = ((screen_pick[2] -screen_pick[7])*(0+z3));
                float ny = ((0-z3)*(screen_pick[1] +screen_pick[6]));
                float nz = ((screen_pick[1] -screen_pick[6])*(screen_pick[2] +screen_pick[7]));



	vlist[count] = (Vertex *) malloc (sizeof (Vertex));
	vlist[count]->x = cx-axis[0];//(screen_pick[4]-screen_pick[2]);
	vlist[count]->y= cy-axis[1];//(screen_pick[5]-screen_pick[1]);
	vlist[count]->z = cz-axis[2];//z2;


        ++count;
	//glBegin(GL_LINE_LOOP);
	for(ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
                vlist[count+ii] = (Vertex *) malloc (sizeof (Vertex));
		/*float x = r * cosf(theta);//calculate the x component
		float y = r * sinf(theta);//calculate the y component
                float z=0;*/
               float x = cx+r*(u1[0]*cosf(theta)+u2[0]*sinf(theta));
                float y= cy+r*(u1[1]*cosf(theta)+u2[1]*sinf(theta));
                float z = cz+r*(u1[2]*cosf(theta)+u2[2]*sinf(theta));
               //float z= 0;
		//glVertex3f(x + cx, y + cy,0);//output vertex
		//vlist[ii]->x = x + cx,y + cy,0);
		vlist[ii+count]->x = x-axis[0];//(screen_pick[4]-screen_pick[2]);
		vlist[ii+count]->y = y-axis[1];//(screen_pick[5]-screen_pick[1]);
		vlist[ii+count]->z = z-axis[2];//z2;
		printf("x %f  y %f  z %f\n",x,y,z);
		//glVertex3f(x,y,z);//output vertex

	}
	//glEnd();

write_file(vlist,CYLINDER);

//glFlush();
	//glutSwapBuffers();
}

void computeCylinder(int* screen_pick){

        //float cx,cy,radius;
        origin[0]=screen_pick[0];
        origin[1]=screen_pick[1];
        origin[2]=0;
for(int i = 0;i<8;i++)
                printf("Screen[%d] : %d\n",i,screen_pick[i]);

        for (int j= 3; j>=0;j--){
                screen_pick[2*j] -= screen_pick[0];
                screen_pick[2*j+1] -= screen_pick[1];
                printf("%d %d\n",screen_pick[2*j],screen_pick[2*j+1]);
        }
        printf("Cylinder picked Coordinates\n");
for(int i = 0;i<8;i++)
                printf("Screen[%d] : %d\n",i,screen_pick[i]);

        cx = (screen_pick[2]-screen_pick[0])/2;
        cy = (screen_pick[3]-screen_pick[1])/2;
        printf ("Centre %f %f %f\n",cx,cy,cz);

        //radius = sqrtf(cx*cx+cy*cy);
        radius = fabs(cx);
        float minor = sqrtf(pow(screen_pick[6]-cx,2)+pow(screen_pick[7]-cy,2));
        float tilt =asinf(minor/radius);
        float z3 = sqrtf(2*(cx*screen_pick[6]+cy*screen_pick[7]) - screen_pick[6]*screen_pick[6]);
        z3 = sqrtf((radius*radius) -pow((screen_pick[6]-cx),2) -pow((screen_pick[7]-cy),2)  );
         printf("Z3 = %f  Minor = %f",z3,minor);
         //u1={cx,cy,0};
         //u2={screen_pick[6]-cx,screen_pick[7]-cy,z3};

        // u1 = {cx/radius,cy/radius,0};
        u1[0] = cx;
        u1[1] = cy;
        u1[2] = 0;
         u2[0]=screen_pick[6]-cx;
         u2[1]=screen_pick[7]-cy;
         u2[2]=z3;
        printf(" Centre %f %f  Radius %f \n",cx,cy,radius);
        printf("U2 %f %f %f\n",u2[0],u2[1],u2[2]);
float mag = sqrtf(cx*cx+cy*cy);
        for(int i =0; i<3;i++){
                u1[i]=u1[i]/mag;
                printf("U1 normalised %f \n",u1[i]);
        }
        mag = sqrtf(pow(u2[0],2)+ pow(u2[1],2)+ pow(u2[2],2));
        printf("mag u2 %f\n",mag);
        for(int i =0; i<3;i++){
                u2[i]=u2[i]/mag;
                printf("U2 normalised %f \n",u2[i]);
        }

        cz=0;
        DrawCircle(cx,cy,cz,radius,16,u1,u2,tilt);
        show_mesh=1;
        glutPostRedisplay();
}

void setShaders() {

	char *vs = NULL,*fs = NULL,*fs2 = NULL;

	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);



	vs = textFileRead("F:\\gui\\bunny.vert");
	fs = textFileRead("F:\\gui\\bunny.frag");


	const char * ff = fs;

	const char * vv = vs;

	glShaderSource(v, 1, &vv,NULL);
	glShaderSource(f, 1, &ff,NULL);
	//glShaderSource(f2, 1, &ff2,NULL);

	free(vs);free(fs);

	glCompileShader(v);
	glCompileShader(f);


	p = glCreateProgram();
	glAttachShader(p,f);
	glAttachShader(p,v);

	glLinkProgram(p);
	glUseProgram(p);
}


/*void perVertexNormal(){
int i,j,k,count=0;
float norm[100],mag,nx,ny,nz;



vnorms = (float*)malloc(vertices*3*sizeof(float));



for(j =0; j<vertices ;j++){
        for(i=0; i< faces; i++){

                for(k=0;k<flist[i]->nverts;k++){
                        if(flist[i]->verts[k] == j){
                                vnorms[3*j]+=face_normals[3*i];
                               // printf(" N: %f\n",face_normals[3*i]);
                                vnorms[3*j+1]+=face_normals[3*i+1];
                                vnorms[3*j+2]+=face_normals[3*i+2];
                        }
                }
                count =0;
        }
        float mag = sqrtf(vnorms[3*j]*vnorms[3*j]+vnorms[3*j+1]*vnorms[3*j+1]+vnorms[3*j+2]*vnorms[3*j+2]);
        vnorms[3*j]/=mag;
        vnorms[3*j+1]/=mag;
        vnorms[3*j+2]/=mag;
        //printf("vnorms %f\n ",vnorms[3*j]);
      /*  for(i =0; i<count;i++){
                nx+=norm[3*i];
                ny+=norm[3*i+1];
                nz+=norm[3*i+2];
        }
        mag = sqrtf(nx*nx+ny*ny+nz*nz);
        perVertexNormals[3*j]= nx/mag;
        perVertexNormals[3*j+1]= ny/mag;
        perVertexNormals[3*j+2]= nz/mag;
}
//printf("%f",perVertexNormals[1]);
}

/*void scale(int key, int x, int y){
        //printf("%d",key);
if(key == GLUT_KEY_UP){
        x_rot+=delta_rot;
       // printf("%f",x_rot);
       doRotation(delta_rot,0,0,1);}
else if( key == GLUT_KEY_DOWN){
         x_rot-=delta_rot;
       doRotation(-1*delta_rot,1,0,0);}
else if (key == GLUT_KEY_LEFT)
   {         y_rot-=delta_rot;
       doRotation(-1*delta_rot,0,1,0);}

else if(key == GLUT_KEY_RIGHT);
        {
         y_rot+=delta_rot;
       doRotation(delta_rot,0,1,0);}
glutPostRedisplay();
}
*/
Vertex* computeNormal(int face ){
        Vertex normal ={0.0,0.0,0.0};
        int i,n;
        float x,y,z;
        n=flist[face]->nverts;
        for(i=0; i<n ;i++){
                Vertex next= *(vlist[flist[face]->verts[i]]);
                Vertex current= *(vlist[flist[face]->verts[(i+1)%n]]);
                //printf("Normal %f ",current.x);
                normal.x += ((current.y -next.y)*(current.z+next.z));
                normal.y += ((current.z -next.z)*(current.x+next.x));
                normal.z += ((current.x -next.x)*(current.y+next.y));

        }
        float mag=sqrtf(pow(normal.x,2)+pow(normal.y,2)+pow(normal.z,2));
       x =normal.x/=mag;  flist[face]->nx=x;
        y =normal.y/=mag; flist[face]->ny=y;
       z =normal.z/=mag;  flist[face]->nz=z;

        return &normal;
}

void computeLightVector(){
float lv[3],lvlength;
int i;

light_list = (Vertex **) malloc (sizeof (Vertex*) *vertices);
for (i = 0; i < vertices; i++) {
      light_list[i] = (Vertex *) malloc (sizeof (Vertex));
      lv[0] = pos_light2[0] -vlist[i]->x;
      lv[1] = pos_light2[1] -vlist[i]->y;
      lv[2] = pos_light2[2] -vlist[i]->z;

      lvlength = sqrt(lv[0]*lv[0] + lv[1]*lv[1] + lv[2]*lv[2]);
      light_list[i]->x = lv[0] / lvlength;
      light_list[i]->y = lv[1] / lvlength;
      light_list[i]->z = lv[2] / lvlength;
        //printf("%f %f %f\n",light_list[i]->x,light_list[i]->y,light_list[i]->z);
  }
}

void read(){
PlyFile *plyFile;
PlyElement **elems;
PlyProperty *property,**ele_prop;
FILE *fp;

PlyProperty vert_props[] = {
  {"x", Float32, Float32, offsetof(Vertex,x), 0, 0, 0, 0},
  {"y", Float32, Float32, offsetof(Vertex,y), 0, 0, 0, 0},
  {"z", Float32, Float32, offsetof(Vertex,z), 0, 0, 0, 0}
};

/*PlyProperty face_props[] = {
  {"vertex_indices",Uint8 , Int32, offsetof(Face,verts), 1, Uint8, Uint8,offsetof(Face,nverts)}
};*/

PlyProperty face_props[] = {
  {"vertex_indices",Uint8 , Int32, offsetof(Face,verts), 1, Uint8, Uint8,offsetof(Face,nverts)}
};
float arr;
int numOfElements,nprops,i,k,j;
char *ele_name;
char **elements;

    fp = fopen(name,"r");
    plyFile = read_ply(fp);

    for(i=0; i< plyFile->num_elem_types; i++){
       elems = plyFile->elems;
       ele_name = elems[i]->name;
       numOfElements=elems[i]->num;

       cout<<ele_name<< " "<<elems[i]->num<<"\n";
       nprops = elems[i]->nprops;
       cout<<"Number of prop"<<" "<<nprops<<"\n";
       ele_prop = elems[i]->props;
       //cout<<ele_prop[0]->name;

        if(equal_strings ("vertex", ele_name)){
                vertices=elems[i]->num;
                vlist = (Vertex **) malloc (sizeof (Vertex *) * elems[i]->num);

                ply_get_property (plyFile, ele_name, &vert_props[0]);
                ply_get_property (plyFile, ele_name, &vert_props[1]);
                ply_get_property (plyFile, ele_name, &vert_props[2]);

                for (j = 0; j < numOfElements; j++) {
                        vlist[j] = (Vertex *) malloc (sizeof (Vertex));
                        ply_get_element (plyFile, (void *) vlist[j]);
               // printf ("vertex: %g %g %g\n", vlist[j]->x, vlist[j]->y, vlist[j]->z);
               }
       }

        if (equal_strings ("face", ele_name)) {
                flist = (Face **) malloc (sizeof (Face *) * elems[i]->num);
                ply_get_property (plyFile, ele_name, &face_props[0]);
                faces = elems[i]->num;
                for (j = 0; j < elems[i]->num; j++) {
                        flist[j] = (Face *) malloc (sizeof (Face));
                        ply_get_element (plyFile, (void *) flist[j]);
                 }
        }

}
face_normals = (float*)malloc(sizeof(float*)*3*faces);

}

void convertVertexToList(){
        int i;
        float mx,Mx,my,My,mz,Mz,xmid,ymid,zmid;
        mx=Mx=my=My=mz=Mz=0;
        list = (float*)malloc(sizeof(float)*vertices*3);

for(i =0; i<vertices;i++){
list[3*i] = vlist[i]->x;
list[3*i+1] = vlist[i]->y;
list[3*i+2] = vlist[i]->z;
/*if(vlist[i]->x > Mx) Mx = vlist[i]->x;
if(vlist[i]->x < mx) mx = vlist[i]->x;

if(vlist[i]->y > My) My = vlist[i]->y;
if(vlist[i]->y < my) my= vlist[i]->y;

if(vlist[i]->y > Mz) Mz = vlist[i]->z;
if(vlist[i]->y < mz) mz= vlist[i]->z;*/
}
/*xmid = (Mx-mx)/2;
ymid =(My-my)/2;
zmid = (Mz-mz)/2;

glutPostRedisplay();*/
}


void disp(){
int j,l;
int *arr,vert,k,v1,v2,v3,v4;
float col,v[3],x,y,z;
Vertex* normal;

  // to generate the vertex array from the structure

glClearColor(0,0,0,1);
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glMatrixMode( GL_PROJECTION );
glLoadIdentity();
glEnable(GL_DEPTH_TEST);
//glOrtho(-400.0,400.0,-400.0,400.0,-1500,1500); /*Use this for the hand.ply */

glOrtho(m_left,m_right,m_bottom,m_top,m_near,m_far);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
// STUFF :)
glColor3f(1,1,1);
	glPushMatrix();
		glMultMatrixf( lights_rotation );
        glLightfv(GL_LIGHT0, GL_POSITION, pos_light1);
    glPopMatrix();

glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
if(tex1_enabled)
        glEnable( GL_TEXTURE_2D );
glBindTexture(GL_TEXTURE_2D,cube);
glPushMatrix();
	//glTranslatef( -22.0,-22,0);
	//glTranslatef(-317 ,-191, -1400); // P4
	glTranslatef(-400 ,-400, -1400);
	//glTranslatef(-24.000000 ,-103.000000, -1400);
	glBegin(GL_QUADS);

		glTexCoord2d(0,0);
		glVertex3f(0,0,0);

		glTexCoord2d(0,1);
		glVertex3f(0,im_height,0);

		glTexCoord2d(1,1);
		glVertex3f(im_width,im_height,0);

		glTexCoord2d(1,0);
		glVertex3f(im_width,0,0);

	glEnd();

glPopMatrix();
glDisable(GL_TEXTURE_2D);

//DrawCircle(0,0,100,16);
glTranslatef( obj_pos[0], obj_pos[1], obj_pos[2] );
glMultMatrixf( view_rotate );
glScalef( scale, scale, scale );

 if( show_mesh){
         float scale_x = (m_right-m_left)/view_width;
         float scale_y = (m_top-m_bottom)/view_height;
         //printf("Scale x %f  Scale y %f \n",scale_x,scale_y);
         //printf(" Origin: %f %f\n",origin[0],origin[1]);
         //printf("New Origin %f %f \n",-800+(origin[0]*scale_x)/2,-800+(origin[1]*scale_y)/2);
         glTranslatef(-800+(origin[0]*scale_x),-800+(origin[1]*scale_y),0);
         glScalef(scale_x,scale_y,1);
         //glPushMatrix();
         //glRotatef(90,1,0,0);

		//DrawCircle(cx,cy,cz,radius,16,u1,u2,tilt);
		//glPopMatrix();
          //glScalef( 1.54738, 1.4035, 1 );
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

	glBegin(GL_LINES);
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(400,0,0);
		glColor3f(0,1,0);
		glVertex3f(0,0,0);
		glVertex3f(0,400,0);

		glColor3f(0,0,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,1500);
	glEnd();


	glColor3f(1,1,1);

glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
//glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//glBindTexture(GL_TEXTURE_2D,texture);
//printf("Faces = %d\n", faces);
	for(j =0; j<faces;j++){
		//printf("Num Verts = %d\n", flist[j]->nverts );
		if(flist[j]->nverts >0){
			if(!flag ){
				//normal= computeNormal(j);                // Normal computation per surface
				//float narray[3]={normal->x,normal->y,normal->z};
				/*face_normals[3*j]=narray[0];
				face_normals[3*j+1]=narray[1];
				face_normals[3*j+2]=narray[2];*/
				//glNormal3fv(narray);
				//glNormal3fv(narray);
                                if(radio_option ==0){
                                        glBegin(GL_QUADS);
                                        v4 = (flist[j]->verts[3]);
                                        glVertex3f(vlist[v4]->x,vlist[v4]->y,vlist[v4]->z);
                                }
                                else
                                        glBegin(GL_TRIANGLES);
				//
				v1 = (flist[j]->verts[0]);
				v2 = (flist[j]->verts[1]);
				v3 = (flist[j]->verts[2]);


				//printf("Faces %d %d %d %d",v1,v2,v3,v4);

				glVertex3f(vlist[v1]->x,vlist[v1]->y,vlist[v1]->z);
				glVertex3f(vlist[v2]->x,vlist[v2]->y,vlist[v2]->z);
				glVertex3f(vlist[v3]->x,vlist[v3]->y,vlist[v3]->z);
				//
			    //printf("Faces: %d %d %d %d %f\n",v1, v2,v3,vlist[]);

				// glTexCoord2d(0,0);
				/*    glVertex3f(list[v1],list[v1+1],list[v1+2]);

				//  glTexCoord2d(0,1);
				glVertex3f(list[v2],list[v2+1],list[v2+2]);

				//    glTexCoord2d(1,1);
				glVertex3f(list[v3],list[v3+1],list[v3+2]);
			 //
			 //  glTexCoord2d(1,0);
				glVertex3f(list[v4],list[v4+1],list[v4+2]);*/


           }
			else{
                                        glDisable(GL_LIGHT0); // To detect the change in per vertex normal computation
                                        glEnableClientState(GL_VERTEX_ARRAY);
					glEnableClientState(GL_NORMAL_ARRAY);
					glNormalPointer(GL_FLOAT,0,vnorms);
					glVertexPointer(3,GL_FLOAT,0,list);
					glDrawElements(GL_POLYGON,(flist[j]->nverts),GL_UNSIGNED_INT,flist[j]->verts);
					glDisableClientState(GL_VERTEX_ARRAY);
					glDisableClientState(GL_NORMAL_ARRAY);
                }


    }
    else
		printf("Number of vertices in face list is zero");}

	glEnd();
	glFlush();
 }


        glutSwapBuffers();

}


void computeCuboid( int* screen_pick,int w,int h){

        float z1,z2,z3;
        //for(int j=0; j<8;j++)
                //printf("Original: %d \n",screen_pick[j]);
        origin[0]=screen_pick[0];
        origin[1]=screen_pick[1];
        origin[2]=0;

        for (int j= 1; j< 4;j++){
                screen_pick[2*j]-=screen_pick[0];
                screen_pick[2*j+1]-=screen_pick[1];
        }

          //for(int j=0; j<8;j++)
               // printf("sub: %d \n",screen_pick[j]);


        screen_pick++;screen_pick++;

    for(int j=0; j<6;j++)
                printf("sub: %d \n",screen_pick[j]);

        float A = -(screen_pick[0]*screen_pick[2] + screen_pick[1] * screen_pick[3] );
        float B = -(screen_pick[2]*screen_pick[4] + screen_pick[3] * screen_pick[5] );
        float C = -(screen_pick[4]*screen_pick[0] + screen_pick[5] * screen_pick[1] );

        if( A*B*C == 0){
        printf("Div by Zero err");
        exit(0);
        }
        z1 = sqrtf((A*C)/B);
        z2 = sqrtf((A*B)/C);
        z3 = sqrtf((C*B)/A);

        printf("Z1 %f  Z2 %f Z3 %f\n",z1,z2,z3);

 cx = screen_pick[0]/2;
 cy = screen_pick[1]/2;
 cz = z1/2;

//distance = screen_pick[3]-screen_pick[1];

u1[0]=screen_pick[0];
u1[1]=screen_pick[1];
u1[2]=z1;

u2[0] = screen_pick[4];
u2[1] = screen_pick[5];
u2[2] = z3;

printf("Cylinder end points\n");
for(int k =0;k<3;k++)
        printf("%f   ",u1[k]);

float mag=sqrtf(pow(u1[0],2)+ pow(u1[1],2)+ pow(u1[2],2));
 radius = u1[0]/2;
 printf("\nU1 U2\n");
for(int i =0; i<3;i++){
                u1[i]=u1[i]/mag;
                printf("U1 %f\n ",u1[i]);
}
mag = sqrtf(pow(u2[0],2)+ pow(u2[1],2)+ pow(u2[2],2));

tilt = asinf(u2[1]/radius);
printf("Tilt %f",tilt);
for(int i =0; i<3;i++){
                u2[i]=u2[i]/mag;
                  printf("U2 %f \n",u2[i]);
}
//tilt = asinf()
//DrawCircle(cx,cy,cz,radius,16,u1,u2,0);
float points[8][3],*temp;

points[0][0]=0;
points[0][1]=0;
points[0][2]=0;

points[1][0]=screen_pick[0];
points[1][1]=screen_pick[1];
points[1][2]=z1;

points[2][0]=screen_pick[2];
points[2][1]=screen_pick[3];
points[2][2]=z2;

points[3][0]=screen_pick[4];
points[3][1]=screen_pick[5];
points[3][2]=z3;

temp =resultant(points[1],points[2]);
points[4][0] = temp[0];
points[4][1] = temp[1];
points[4][2] = temp[2];

temp=resultant(points[2],points[3]);
points[5][0]  = temp[0];
points[5][1]  = temp[1];
points[5][2]  = temp[2];

temp=resultant(points[3],points[1]);
points[6][0]  = temp[0];
points[6][1]  = temp[1];
points[6][2]  = temp[2];

temp = resultant(temp,points[2]);
points[7][0]  = temp[0];
points[7][1]  = temp[1];
points[7][2]  = temp[2];
//points[7] ={points[5][0]+points[1][0],points[5][1],points[5][2]};

FILE *out = fopen("F:\\2DTO3D\\out.txt","w+");
 vlist = (Vertex **) malloc (sizeof (Vertex *) * 8);
for (int i =0;i<8;i++){
int order [8]= {1,0,2,4,6,3,5,7};
fprintf(out,"%f %f %f\n",points[order[i]][0],points[order[i]][1],points[order[i]][2]);
vlist[i] = (Vertex *) malloc (sizeof (Vertex));
vlist[i]->x = points[order[i]][0];
vlist[i]->y = points[order[i]][1];
vlist[i]->z = points[order[i]][2];

}
fclose(out);

write_file(vlist,CUBE);
show_mesh=1;
//read();
//convertVertexToList();
glutPostRedisplay();

}
float* resultant(float * a, float*b){
float res[3];
for (int i=0;i<3;i++){
        res[i]=a[i]+b[i];
        printf("%f  = %f + %f\n",res[i],a[i],b[i] );
}
return res;
}


void write_file( Vertex** vlist, int object){
//
//printf("Printing Vlist in write\n");
//for (int k=0;k<34;k++)
 //       printf(" %d %f %f %f\n",k,vlist[k]->x,vlist[k]->y,vlist[k]->z);

char * filename = "F:\\2DTO3D\\model.ply";
FILE *fp = fopen("F:\\2DTO3D\\model.ply","w+");
int nelems = 2;
char * v= "vertex";
char* f ="face";
int n_faces=6,n_vertices=8,face_type=4;

int cube_faces[6][4]={{0,1,2,3} ,{5 ,4, 7, 6 },{6,2, 1, 5},{3, 7, 4, 0},{7, 3, 2, 6},{5, 1, 0, 4}};
PlyElement **elems;
PlyProperty *property,**ele_prop;

char **elem_names = (char**) calloc(2,sizeof(char*));
elem_names[0]=v;
elem_names[1]=f;
int file_type = PLY_ASCII;

if(object == CYLINDER){
n_faces=64;
n_vertices=34;
face_type=3;// Triangle faces
printf("Cylinder object  got to write\n");
}
faces=n_faces;
printf("In write\n");
PlyProperty vert_props[] = {
  {"x", Float32, Float32, offsetof(Vertex,x), 0, 0, 0, 0},
  {"y", Float32, Float32, offsetof(Vertex,y), 0, 0, 0, 0},
  {"z", Float32, Float32, offsetof(Vertex,z), 0, 0, 0, 0}
};

PlyProperty face_props[] =
  {"vertex_indices",Int32 , Int32, offsetof(Face,verts), 1, Uint8, Uint8,offsetof(Face,nverts)};

PlyFile *model =write_ply ( fp,  nelems, elem_names,  file_type );
if(model != NULL){
        model =open_for_writing_ply (filename,  nelems, elem_names,file_type );
        element_layout_ply ( model, elem_names[0], n_vertices, 3,&vert_props[0] );
        element_layout_ply ( model, elem_names[1], n_faces, 1,&face_props[0] );
//printf("prop elements %d\n", model->elems[0]->nprops);
        //ply_describe_property ( model, elem_names[0],  &vert_props[0]);
        //ply_describe_property ( model, elem_names[0],  &vert_props[1]);
        //ply_describe_property ( model, elem_names[0],  &vert_props[2]);
        //ply_describe_property ( model, elem_names[1],  &face_props[0]);

        element_count_ply ( model, elem_names[0], n_vertices);
        element_count_ply ( model, elem_names[1], n_faces);

        header_complete_ply(model);

        //elems=model->elems
        for(int j=0;j<n_vertices;j++)
        {put_element_setup_ply(model, elem_names[0]);
        put_element_ply(model, (void*)vlist[j]);
        }

        printf("Num faces %d\n",n_faces);
         flist = (Face **) malloc (sizeof (Face *) * n_faces);

if(object == CUBE){
         for( int j = 0;j <n_faces;j++){

                flist[j] = (Face *) malloc (sizeof (Face));
                flist[j]->nverts=face_type;
                flist[j]->verts = (int*)malloc(sizeof(int)*flist[j]->nverts);

                for(int k = 0; k< flist[j]->nverts; k++){
                        flist[j]->verts[k]=cube_faces[j][k];
                }
                  put_element_setup_ply(model, elem_names[1]);
                put_element_ply(model, (void*)flist[j]);
         }
}

else{
int idx =0;
         for( int j = 0;j <16;j++,idx++){

                //for(int i =0; i<16;i++){
                 flist[idx] = (Face *) malloc (sizeof (Face));
                flist[idx]->nverts=face_type;
                flist[idx]->verts = (int*)malloc(sizeof(int)*flist[idx]->nverts);

                flist[idx]->verts[0]=0;
                flist[idx]->verts[1]=(j+1)%17;
                flist[idx]->verts[2]=(j+2)%17==0?1:(j+2)%17;

                //}
                put_element_setup_ply(model, elem_names[1]);
                put_element_ply(model, (void*)flist[idx]);
        }
printf("idx %d\n",idx);
 for( int j = 17;j <33;j++,idx++){

                //for(int i =0; i<16;i++){
                cout<<"J "<<j<<endl;
                 flist[idx] = (Face *) malloc (sizeof (Face));
                flist[idx]->nverts=face_type;
                flist[idx]->verts = (int*)malloc(sizeof(int)*flist[idx]->nverts);

                flist[idx]->verts[0]=17;
                flist[idx]->verts[1]=(j+1)%34==17?18:(j+1)%34;
                flist[idx]->verts[2]=(j+2)%34==0?18:(j+2)%34;

                //}
                put_element_setup_ply(model, elem_names[1]);
                put_element_ply(model, (void*)flist[idx]);
        }

   int v1=1,v2=17;
   printf("idx %d\n",idx);
 for( int j = 33;j <=64;j+=2,v1++,idx+=2){

                //for(int i =0; i<16;i++){
                 flist[idx] = (Face *) malloc (sizeof (Face));
                flist[idx]->nverts=face_type;
                flist[idx]->verts = (int*)malloc(sizeof(int)*flist[idx]->nverts);
  //v1 =1
                flist[idx]->verts[0]=v1;
                flist[idx]->verts[1]=v1+v2+1==34?18:v1+v2+1;
                flist[idx]->verts[2]=v1+1==17?1:v1+1;
                put_element_setup_ply(model, elem_names[1]);
                put_element_ply(model, (void*)flist[idx]);

                 flist[idx+1] = (Face *) malloc (sizeof (Face));
                flist[idx+1]->nverts=face_type;
                flist[idx+1]->verts = (int*)malloc(sizeof(int)*flist[idx]->nverts);
                flist[idx+1]->verts[0]=v1;
                flist[idx+1]->verts[1]=(v1+v2);
                flist[idx+1]->verts[2]=(v1+v2+1)==34?18: (v1+v2+1);

                put_element_setup_ply(model, elem_names[1]);
                put_element_ply(model, (void*)flist[idx+1]);
        }
}
//printf("idx %d\n",idx);
}

else
        printf("Model file null");

close_ply(model);
//fclose(fp);
}


void getImageDimensions(char *filename,int &width, int &height){

FILE *image;
int size, i = 0;
unsigned char *data;

image =fopen(filename,"rb");  // open JPEG image file
if(!image){
   printf("Unable to open image \n");
}
fseek(image,  0,  SEEK_END);
size = ftell(image);
fseek(image,  0,  SEEK_SET);
data = (unsigned char *)malloc(size);
fread(data, 1, size, image);
/* verify valid JPEG header */
if(data[i] == 0xFF && data[i + 1] == 0xD8 && data[i + 2] == 0xFF && data[i + 3] == 0xE0) {
     i += 4;
     /* Check for null terminated JFIF */
     if(data[i + 2] == 'J' && data[i + 3] == 'F' && data[i + 4] == 'I' && data[i + 5] == 'F' && data[i + 6] == 0x00) {
         while(i < size) {
             i++;
             if(data[i] == 0xFF){
                 if(data[i+1] == 0xC0) {
                     height = data[i + 5]*256 + data[i + 6];
                     width = data[i + 7]*256 + data[i + 8];
                     break;
                 }
             }
         }
     }
 }
 fclose(image);
 printf("In func %d %d\n",width,height);
}



