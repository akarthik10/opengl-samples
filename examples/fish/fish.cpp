
#include <stdlib.h> 	
#include <GL/glut.h>
#include <math.h>


void drawBody();

GLfloat angle = 0.0;
GLfloat tail_angle=0.0;
GLfloat lip_angle=20.0;
GLfloat twoModel[]={GL_TRUE};
int color=0;


GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; 
GLfloat whiteSpecularMaterial[]={1,1,1};
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0}; 
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; 
GLfloat mShininess[] = {128}; 


GLfloat bubba[25][4];
GLfloat myx=0.0, myy=0.0, myz=-20.0, rotation=0.0, rotor_angle=0.0, heli_tilt=0.0;
int rotate=0;

bool diffuse = false;
bool emissive = false;
bool specular = false;

void initBubbles()
{
	int i;
	for(i=0;i<25;i++)
	{
		bubba[i][0]=rand()%5;
		bubba[i][1]=rand()%30;
		bubba[i][2]=rand()%30;
		bubba[i][3]=rand()%30;
	}
}

void init (void) {
	
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
initBubbles();
	
	


}



void light (void) {
	
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, twoModel);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);

	float materialColours[][3]={{1,0.6,0.3}, {0.2,0.2,0.2}, {0.6,0.6,0.6}, {0.75,0.164,0.164},{0.601,0.19,1.0}, {1,1,0}};
	float materialLightBr[]={0.2,0.2,0.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materialColours[color]);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,materialLightBr);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,whiteSpecularMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
       

}


void draw_bg()
{

	glDisable(GL_LIGHTING);
	glColor3f(0.733,1,1);
	glBegin(GL_POLYGON);
	glVertex3f(-1000,300,-250);
	glVertex3f(1000,300,-250);
	glColor3f(0.2274,.3725,0.8039);
	glVertex3f(1000,-300,-250);
	glVertex3f(-1000,-300,-250);
	glEnd();
	glEnable(GL_LIGHTING);



}

void draw_bubble()
{
	int r;

	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		float bubbleColour[]={0.733,0.8,1,0.5};
	float materialLightBr[]={0.2,0.2,0.0};
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,bubbleColour);
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,materialLightBr);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,whiteSpecularMaterial);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
		//glColor4f(0,0,1,1);

	for(r=0;r<20;r++)
	{
		if(r<5)
		{
	glPushMatrix();
	glTranslatef(bubba[r][1],bubba[r][2],-20);
	glutSolidSphere(0.5,12,12);
	glPopMatrix();
		}

		if(r>=5&&r<10)
		{
	glPushMatrix();
	glTranslatef(bubba[r][1],-bubba[r][2],-20);
	glutSolidSphere(0.5,12,12);
	glPopMatrix();
		}

		if(r>=10&&r<15)
		{
	glPushMatrix();
	glTranslatef(-bubba[r][1],bubba[r][2],-20);
	glutSolidSphere(0.5,12,12);
	glPopMatrix();
		}

		if(r>=15&&r<20)
		{
	glPushMatrix();
	glTranslatef(-bubba[r][1],-bubba[r][2],-20);
	glutSolidSphere(0.5,12,12);
	glPopMatrix();
		}


	}

		glDisable(GL_BLEND);


}

void display (void) {

    glClearColor (0.0,0.0,1.0,0.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	gluLookAt(0.0,2.0,10.0,myx,myy,myz,0.0,1.0,0.0);
    light();

	glPushMatrix();
	glTranslatef(myx, myy, myz);
	glRotatef(rotation, 0.0, 1.0, 0.0);
	glTranslatef(-myx, -myy, -myz);


    glTranslatef(myx,myy,myz);

	
	
	drawBody();
	glPopMatrix();
	draw_bg();

	
	draw_bubble();
    glutSwapBuffers();

}

void draw_mouth()
{

	glPushMatrix();

	glTranslatef(0.0, -1.0, 0.0);
	glRotatef(90.0, 1.0,0.0,0.0);
	
	glRotatef(25.0*sin(lip_angle),0.0,1.0,0.0);
	glutSolidTorus(0.5,0.8,12,12);
	glRotatef(-50.0*sin(lip_angle),0.0,1.0,0.0);
	glutSolidTorus(0.5,0.8,12,12);

	glPopMatrix();
}

void draw_fins1()
{
	int i;
	glPushMatrix();

	twoModel[0]=GL_FALSE;
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, twoModel);

	glRotatef(-fabs(sin(tail_angle))*20, 0,1,0);

	glBegin(GL_POLYGON);

	glVertex3f(0.0,0.5,0.0);
	glVertex3f(3.5,2.0,0.0);
	glVertex3f(4.5,0.0,0.0);
	glVertex3f(3.5,-2.0,0.0);
	glVertex3f(0.0,-0.5,0.0);
	glVertex3f(0.0,0.5,0.0);

	glEnd();

	glDisable(GL_LIGHTING);
	GLfloat tx=3.5,ty=2.0;
	glLineWidth(2.0);
		glColor3f(0.0,0.0,0.0);

		for(i=0;i<8;i++)
		{
			glBegin(GL_LINES);
			if(i<4)
			glVertex3f(0.0,0.5-(0.125*i),0.0);
			else
			glVertex3f(0.0,-(0.125*(i-4)),0.0);
			glVertex3f(tx,ty,0.0);

			ty-=0.5;
			if(i<4)
			tx+=0.25;
			else
			tx-=0.25;
			glEnd();
		}
	glEnable(GL_LIGHTING);

	twoModel[0]=GL_TRUE;
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, twoModel);
	glPopMatrix();

}
void draw_fins2()
{
	int i;
	glPushMatrix();

	twoModel[0]=GL_FALSE;
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, twoModel);

	glRotatef(fabs(sin(tail_angle))*20, 0,1,0);

	glBegin(GL_POLYGON);

	glVertex3f(0.0,0.5,0.0);
	glVertex3f(3.5,2.0,0.0);
	glVertex3f(4.5,0.0,0.0);
	glVertex3f(3.5,-2.0,0.0);
	glVertex3f(0.0,-0.5,0.0);
	glVertex3f(0.0,0.5,0.0);

	glEnd();

	glDisable(GL_LIGHTING);
	GLfloat tx=3.5,ty=2.0;
	glLineWidth(2.0);
		glColor3f(0.0,0.0,0.0);

		for(i=0;i<8;i++)
		{
			glBegin(GL_LINES);
			if(i<4)
			glVertex3f(0.0,0.5-(0.125*i),0.0);
			else
			glVertex3f(0.0,-(0.125*(i-4)),0.0);
			glVertex3f(tx,ty,0.0);

			ty-=0.5;
			if(i<4)
			tx+=0.25;
			else
			tx-=0.25;
			glEnd();
		}
	glEnable(GL_LIGHTING);

	twoModel[0]=GL_TRUE;
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, twoModel);
	glPopMatrix();

}
void draw_eye1()
{
	glPushMatrix();

	  	glutSolidTorus(0.2,0.4,12,12);
	glPopMatrix();


}
void draw_eye2()
{
	glPushMatrix();

	  	glutSolidTorus(0.2,0.4,12,12);
	glPopMatrix();


}

void draw_tail()
{
	int i;
	glPushMatrix();
		
		glRotatef(sin(tail_angle)*20.0, 0.0, 1.0, 0.0);
	
		
		
		glBegin(GL_POLYGON);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(8.0, 6.0, 0.0);
		glVertex3f(6.0,0.0,0.0);
		glVertex3f(8.0,-6.0,0.0);
		glVertex3f(0.0,0.0,0.0);
		glEnd();
	
		glDisable(GL_LIGHTING);
		glLineWidth(2.0);
		glColor3f(0.0,0.0,0.0);
		GLfloat tx=8.0,ty=6.0;

		for(i=0;i<12;i++)
		{
			glBegin(GL_LINES);

			glVertex3f(0.0,0.0,0.0);
			glVertex3f(tx,ty,0.0);

			ty--;
			if(i<6)
			tx-=0.33;
			else
			tx+=0.33;
			glEnd();
		}
		glEnable(GL_LIGHTING);

	glPopMatrix();

}


void draw_dfin()
{	
	int i;
	glPushMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glNormal3f(-1.0,0.0,-1.0);
		glBegin(GL_POLYGON);

		glVertex3f(-4.0,0.0,0.0);
		glVertex3f(-2.0,3.5,0.0);
		glVertex3f(4.0,3.0,0.0);
		glVertex3f(8.0,0.0,0.0);
		glVertex3f(6.0,-3,0.0);


		glEnd();




glDisable(GL_LIGHTING);
		glLineWidth(2.0);
		glColor3f(0.0,0.0,0.0);
		GLfloat tx=-2.0,ty=3.5;

		for(i=0;i<12;i++)
		{
			glBegin(GL_LINES);

			glVertex3f(-4.0+0.2*i,0.0,0.0);
			glVertex3f(tx,ty,0.0);
			glEnd();

			tx+=0.5;
			ty-=0.041;
			
		}

		tx=4.0,ty=3.0;

		for(i=0;i<9;i++)
		{
			glBegin(GL_LINES);

			glVertex3f(-1.0,0.0,0.0);
			glVertex3f(tx,ty,0.0);
			glEnd();

			tx+=0.5;
			ty-=0.375;
			
		}

		glEnable(GL_LIGHTING);



	glPopMatrix();

}

void draw_dfin1()
{	
	int i;
	glPushMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glNormal3f(-1.0,0.0,-1.0);
		glBegin(GL_POLYGON);

		glVertex3f(-4.0,0.0,0.0);
	
		glVertex3f(4.0,3.0,0.0);
		glVertex3f(8.0,0.0,0.0);
		glVertex3f(6.0,-3,0.0);


		glEnd();




glDisable(GL_LIGHTING);
		glLineWidth(2.0);
		glColor3f(0.0,0.0,0.0);
		GLfloat tx=4.0,ty=3.0;


		tx=8.0,ty=0.0;

		for(i=0;i<7;i++)
		{
			glBegin(GL_LINES);

			glVertex3f(-1.0,0.0,0.0);
			glVertex3f(tx,ty,0.0);
			glEnd();

			tx-=0.4;
			ty-=0.5;
			
		}

		glEnable(GL_LIGHTING);



	glPopMatrix();

}

void draw_gills()
{

	glPushMatrix();

	glutSolidTorus(0.2,1.25+(sin(tail_angle)*0.25),12,12);

	glPopMatrix();


}


void draw_dfin2()
{	
	int i;
	glPushMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glNormal3f(1.0,0.0,1.0);

		glBegin(GL_POLYGON);

		glVertex3f(-6.0,0.0,0.0);
		glVertex3f(-7.0,-3.0,0.0);
		glVertex3f(-3.0,-4.0,0.0);
		glVertex3f(-5.0,-2.0,0.0);
		glVertex3f(-1.0,0.0,0.0);


		glEnd();




glDisable(GL_LIGHTING);
		glLineWidth(2.0);
		glColor3f(0.0,0.0,0.0);



		GLfloat tx=-6.5,ty=-3.0;

		for(i=0;i<8;i++)
		{
			glBegin(GL_LINES);

			glVertex3f(-6.0+(0.2*i),-1.0,0.0);
			glVertex3f(tx,ty,0.0);
			glEnd();

			tx+=0.4;
			ty-=0.1;
			
		}

		glEnable(GL_LIGHTING);



	glPopMatrix();

}

void draw_body1()
{
	  glPushMatrix();

	 glScalef(1.0, 1.0, 0.5);
      glutSolidSphere(3.0, 32, 32);
     glScalef(1/2.0, 1/2.0, 1/1.0);



	  glPopMatrix();

}

void drawBody() 
{
	
   glPushMatrix();


   

   


   glScalef(2.0, 1.25, 0.5);
   glutSolidSphere(5.0, 32, 32);
   glScalef(1/2.0, 1/1.25, 1/0.5);


	glTranslatef(8.5, 0.0, 0.0);
	draw_tail();
	glTranslatef(-8.5, 0.0, 0.0);

	glTranslatef(-9.0, 0.0, 0.0);
	draw_mouth();
	glTranslatef(9.0, 0.0, 0.0);

	glTranslatef(-6.0, -1.0, 2.5);
	draw_fins1();
	glTranslatef(6.0, 1.0, -2.5);
	


	glTranslatef(0.0,5.0,0.0);
	draw_dfin();
	glTranslatef(0.0,-5.0,0.0);

	glTranslatef(-6.0, -1.0, -2.5);
    draw_fins2();
	glTranslatef(6.0, 1.0, 2.5);


	float eyeColour[3]={0.1,0.1,0.1};
	float materialLightBr[]={0.2,0.2,0.0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,eyeColour);
	//eye
	glTranslatef(-7.0,2.0,1.75);
	draw_eye1();
	glTranslatef(7.0,-2.0,-1.75);

	glTranslatef(-7.0,2.0,-1.75);
	draw_eye2();
	glTranslatef(7.0,-2.0,1.75);

	//eye
	light();

	glTranslatef(0.0,-5.0,0.0);
	draw_dfin1();
	glTranslatef(0.0,5.0,0.0);

		glTranslatef(0.0,-3.0,0.0);
	draw_dfin2();
	glTranslatef(0.0,3.0,0.0);

	glTranslatef(8.0,0.0,0.0);
	draw_body1();
	glTranslatef(-8.0,0.0,0.0);

	glPushMatrix();
	glTranslatef(-7.0,-1.5,2);
	glRotatef(35,0,0,1);
	glTranslatef(7.0,1.5,-2);
	double eqn[]={0,-1,0,-2};
	glClipPlane(GL_CLIP_PLANE0, eqn);
	glEnable(GL_CLIP_PLANE0);
	glTranslatef(-7.0,-1.5,2);
	draw_gills();
	glTranslatef(7.0,1.5,-2);
	glDisable(GL_CLIP_PLANE0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-7.0,-1.5,-2);
	glRotatef(35,0,0,1);
	glTranslatef(7.0,1.5,2);
	glClipPlane(GL_CLIP_PLANE0, eqn);
	glEnable(GL_CLIP_PLANE0);
	glTranslatef(-7.0,-1.5,-2);
	draw_gills();
	glTranslatef(7.0,1.5,2);
	glDisable(GL_CLIP_PLANE0);
	glPopMatrix();


	glPopMatrix();

	
}

void change_fish_color(int action)
{

	color=action-1;
}

void handle_menu(int action)
{

	if(action==1) initBubbles();

}
	


void addMenu()
{


	int submenu1 = glutCreateMenu(change_fish_color);
	glutAddMenuEntry("Color1",1);
	glutAddMenuEntry("Col2",2);
	glutAddMenuEntry("Col3",3);
	glutAddMenuEntry("Col4",4);
	glutAddMenuEntry("Col5",5);
	glutAddMenuEntry("Col6",6);

	glutCreateMenu(handle_menu);
	glutAddSubMenu("Fish Color",submenu1);
	glutAddMenuEntry("Generate Bubbles",1);
	glutAttachMenu(GLUT_RIGHT_BUTTON);

}


void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y) {
    
    
    
    
   

	if(key=='x') myx++;
	if(key=='X') myx--;
	if(key=='y') myy++;
	if(key=='Y') myy--;
	if(key=='z') myz++;
	if(key=='Z') myz--;
	if(key=='r') rotation++;
	if(key=='R') rotation--;
	if(key=='a') rotate=!rotate;
	if(key=='h') heli_tilt++;
	if(key=='H') heli_tilt--;
	if(key=='1') tail_angle++;
	if(key=='3') tail_angle--;
	if(key=='k') color=(++color)%6;
	if(key=='b') initBubbles();

}


void idle()
{
	int i;
	
	tail_angle+=0.005;
	lip_angle+=0.005;
	for(i=0;i<20;i++)
	{

		if(i<5) bubba[i][2]+=0.01;
		

		if(i>=5&&i<10) bubba[i][2]-=0.01;
		

		if(i>=10&&i<15) bubba[i][2]+=0.01;
		

		if(i>=15&&i<20) bubba[i][2]-=0.01;
		
	}
	display();
}


int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");
    init ();
    glutDisplayFunc (display);
    glutIdleFunc (idle);
    glutKeyboardFunc (keyboard);
    glutReshapeFunc (reshape);
	addMenu();
    glutMainLoop ();
    return 0;
} 