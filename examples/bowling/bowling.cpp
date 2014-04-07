 	
#include <GL/glut.h>
#include <math.h>
#include<stdio.h>

void drawHeli();
void draw_track();
void draw_dumbels();
GLfloat angle = 0.0, ball_prog=0.0, tx=0;
int ballno=5, start=0, showtarget=1, redPin=0, ballcolor=0, winorlose=0, win=0;

GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0}; 
GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0}; 
GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0}; 
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; 
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0}; 
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; 
GLfloat blankMaterial[] = {0.0, 0.0, 0.0}; 
GLfloat mShininess[] = {128}; 
GLdouble viewer[]= {0.0, 0.0, 180.0};
void draw_ball();
void draw_pin();
GLfloat myx=0.0, myy=-11.0, myz=40.0;
GLfloat fall_angle[10]={0.0};
int rotate=0;
GLfloat fallof=0.0;
GLfloat fallof1=1.0;

bool diffuse = true;
bool emissive = true;
bool specular = false;

void init (void) {
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}

void light (void) {
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
}

void set_material(int m)
{
	if(m==0)
	{
		float materialGrey[]={0.8,0.8,0.8},materialWhite[]={0.2,0.2,0.2};
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materialGrey);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,materialWhite);
	}

	else
	{	float materialColours[]={1,0,0};
		float materialLightBr[]={0.5,0.5,0.1};
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materialColours);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,materialLightBr);
	}

}

void setBallColour()
{
	float materialColours[][3]={{1,1,1},{1,0.5,0.1411}, {0.7490,0.2431,1}};
		float materialLightBr[]={0.5,0.5,0.1};
		glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materialColours[ballcolor]);
		glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,materialLightBr);

}



void drawText(char *string,float x,float y,float z) 
{  
char *c;
glRasterPos3f(x, y,z);
for (c=string; *c != '\0'; c++) 
{
glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
}
}



void display (void) {
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
	gluLookAt(viewer[0],viewer[1],viewer[2],myx,myy,myz,0,1,0);
    light();
     
	
	if(winorlose){
	glPushMatrix();
	glColor4f(1.0,1.0,1.0,1.0);
	glDisable(GL_LIGHTING);
	if(win)
	drawText("You WON!", -5,0,0);
	else
	drawText("You LOSE!", -5,0,0);

	glEnable(GL_LIGHTING);
	glPopMatrix();
	}
	else
	{
	setBallColour();
	
	draw_ball();

	
	
	

	glColor3f(1,0.5,0.1);
	draw_track();

	set_material(0);

	glTranslatef(0.0, 0.0, -80.0);
	draw_dumbels();
	glTranslatef(0.0, 0.0, 80.0);

	}
    glutSwapBuffers();
   // angle ++;
}
void draw_pin()
{
	double clip[]={0.0,-1.0,0.0,10.0};
	glPushMatrix();
	glTranslatef(0.0,15.0,0.0);
	glEnable(GL_CLIP_PLANE0);
	glClipPlane(GL_CLIP_PLANE0, clip);
	glScalef(1.0, 5.0, 1.0);
	
	glutSolidSphere(3.0, 16, 16);

	glTranslatef(-10.0, 0.0, 0.0);

		glDisable(GL_CLIP_PLANE0);
		glScalef(1.0,1.3/5.0,1.0);
	glTranslatef(10.0,10.0,0.0);
glutSolidSphere(3.0,16,16);
		glPopMatrix();
}








void draw_dumbels(){
	int i;
	glTranslatef(-40.0,-15.0,0.0);
	

	for(i=0;i<10;i++)
	{
		glPushMatrix();

		 if(i==redPin)
			 set_material(1);
		glRotatef(fall_angle[i], 1.0, 0.0, 0.0);
		draw_pin();
		glPopMatrix();
		glTranslatef(10,0,0);
		 set_material(0);
	}

	
	
}

void changeRed(int m)
{

	if(ball_prog<1.0)
	{
		redPin=(++redPin%10);
		glutTimerFunc(1000,changeRed,0);
	}


}

void draw_ball()
{
	glPushMatrix();
	//draw_track();
	tx=-40+10*ballno;
	myx=tx*ball_prog;
	myy=-12;
	myz=150-230*ball_prog;
	glTranslatef(myx,myy,myz);
	glutSolidSphere(5.0, 32, 32);
	
	glTranslatef(-myx,-myy,-myz);
	glPopMatrix();

	if(showtarget)
	{
	glDisable(GL_LIGHTING);
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
		glVertex3f((-40+10*ballno),-10,-80);
		glVertex3f(0.0,-10,150);
		glEnd();
	glEnable(GL_LIGHTING);
	}
}


void draw_track()
{
	glDisable(GL_LIGHTING);
	glPushMatrix();
	glNormal3f(0,1,0);
	glTranslatef(0,-18,0);
	glScalef(25,0.1,100);
	glutSolidCube(10);

	
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0,-300);

	glScalef(25,50,0.1);

	glColor3f(1,1,0);
	glutSolidCube(10);
	glPopMatrix();

	glColor3f(0,1,0);
	glPushMatrix();
	glTranslatef(100,0,0);
	glScalef(0.1,50,100);
	glutSolidCube(10);
	glPopMatrix();

	glColor3f(0,0,1);
	glPushMatrix();
	glTranslatef(-100,0,0);
	glScalef(0.1,50,100);
	glutSolidCube(10);
	glPopMatrix();




/*	glBegin(GL_QUADS);
	glVertex3f(-50,-16,-50);
	glVertex3f(50,-16,-50);
	glVertex3f(-50,-16,50);
	glVertex3f(50,-16,50);
	glEnable(GL_LIGHTING);
	 for(float i = -50; i <= 50; i += 10)

    {
		
        glBegin(GL_LINES);               
            glVertex3f(-50, -16, i);                   
            glVertex3f(50, -16, i);
            glVertex3f(i, -16,-50);                           
            glVertex3f(i, -16, 50);
		
        glEnd();
    }
	
	//glLineWidth(5.0);
	//glColor3f(1.0,1.0,1.0);
//	glBegin(GL_LINES);
//	glVertex3f(5.0, 0.0, 0.0);
//	glVertex3f(5.0, 0.0, 30.0);

//	glVertex3f(-5.0, 0.0, 0.0);
//	glVertex3f(-5.0, 0.0, 30.0);
//	glEnd();
//	glFlush();
//	glEnable(GL_LIGHTING);*/


//	glColor4f(0.0,0.0,1.0,0.0);
 
	glEnable(GL_LIGHTING);
	glPopMatrix();
	
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
	if(key=='8') viewer[2]++;
	if(key=='2') viewer[2]--;
	if(key=='7') viewer[1]++;
	if(key=='9') viewer[1]--;
	if(key=='4') viewer[0]--;
	if(key=='6') viewer[0]++;
	if(key=='1') {ballno=(--ballno)%10;}//viewer[1]--;
	if(key=='3') {ballno=(++ballno)%10;}//viewer[1]++;
	if(key=='f') fallof++;
	if(key=='s') start=(start==0)?1:0;
	if(key=='r') {fall_angle[ballno]=0.0; start=0; myx=0.0;myy=-10.0;myz=-40.0; ball_prog=0.0;showtarget=1;glutTimerFunc(1000,changeRed,0);winorlose=0;}
	if(key=='b') redPin=(++redPin%10);
	if(key=='c') ballcolor=(++ballcolor%5);
	display();
	
}


void idle()
{

	/*if(myz<=-40 && fallof<90)
	{
		fallof+=0.1;
	}*/
	if(start)
	{
		showtarget=0;
	ball_prog+=0.005;
	if(ball_prog>1.0)
	{
		start=0;
		fall_angle[ballno]=-90.0;
		if(ballno==redPin)
		{
			printf("YOU WIN\n");
			win=1;
		}
		else
		{
			printf("YOU LOSE\n");
			win=0;
		}
		winorlose=1;
		
	}
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
	glEnable(GL_DEPTH_TEST);
    glutDisplayFunc (display);
    glutIdleFunc (idle);
    glutKeyboardFunc (keyboard);
    glutReshapeFunc (reshape);
	glutTimerFunc(1000,changeRed,0);
    glutMainLoop ();
    return 0;
} 