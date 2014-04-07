 #include <stdlib.h>	
#include <GL/glut.h>
#include <math.h>


void display();

GLfloat angle = 0.0;
GLfloat tail_angle=0.0;
GLfloat lip_angle=20.0;
GLfloat twoModel[]={GL_TRUE};

GLfloat redDiffuseMaterial[] = {1.0, 0.0, 0.0}; 
GLfloat whiteSpecularMaterial[] = {1.0, 1.0, 1.0}; 
GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0}; 
GLfloat whiteSpecularLight[] = {1.0, 1.0, 1.0}; 
GLfloat blackAmbientLight[] = {0.0, 0.0, 0.0}; 
GLfloat whiteDiffuseLight[] = {1.0, 1.0, 1.0}; 
GLfloat blankMaterial[] = {0.0, 0.0, 0.0}; 
GLfloat mShininess[] = {128}; 

GLfloat ast_pos[50][3];



void renderCylinder(float x1, float y1, float z1, float x2,float y2, float z2, float radius1,float radius2,int subdivisions,GLUquadricObj *quadric)
{


float vx = x2-x1;
float vy = y2-y1;
float vz = z2-z1;

//handle the degenerate case of z1 == z2 with an approximation
if(vz == 0)
    vz = .0001;

float v = sqrt( vx*vx + vy*vy + vz*vz );
float ax = 57.2957795*acos( vz/v );
if ( vz < 0.0 )
    ax = -ax;
float rx = -vy*vz;
float ry = vx*vz;
glPushMatrix();

//draw the cylinder body
glTranslatef( x1,y1,z1 );
glRotatef(ax, rx, ry, 0.0);
gluQuadricOrientation(quadric,GLU_OUTSIDE);
gluCylinder(quadric, radius1, radius2, v, subdivisions, 1);

//draw the first cap
gluQuadricOrientation(quadric,GLU_INSIDE);
gluDisk( quadric, 0.0, radius1, subdivisions, 1);
glTranslatef( 0,0,v );

//draw the second cap
gluQuadricOrientation(quadric,GLU_OUTSIDE);
gluDisk( quadric, 0.0, radius2, subdivisions, 1);
glPopMatrix();

}
void renderCylinder_convenient(float x1, float y1, float z1, float x2,float y2, float z2, float radius1, float radius2,int subdivisions)
{
//the same quadric can be re-used for drawing many cylinders




GLUquadricObj *quadric=gluNewQuadric();
gluQuadricNormals(quadric, GLU_SMOOTH);
renderCylinder(x1,y1,z1,x2,y2,z2,radius1,radius2,subdivisions,quadric);
gluDeleteQuadric(quadric);
}


GLfloat myx=0.0, myy=0.0, myz=-20.0, rotation=0.0;
int rotate=0;

bool diffuse = false;
bool emissive = false;
bool specular = false;

void init (void) {
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_LIGHTING);
    glEnable (GL_LIGHT0);
}

void light (void) {
	
	glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, twoModel);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteSpecularLight);
    glLightfv(GL_LIGHT0, GL_AMBIENT, blackAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteDiffuseLight);
}


void draw_wings()
{
	GLUquadricObj *quadric=gluNewQuadric();
	gluQuadricNormals(quadric, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(0,0,14);
	glRotatef(90.0,1,0,0);
	glRotatef(90.0,0,0,1);
	glScalef(0.8,3.0,1.0);
	
	gluDisk(quadric,0.0, 5.0, 32.0, 1);


	glPopMatrix();

}

void draw_exhaust()
{
	glPushMatrix();
	

	glRotatef(70,0,0,1);
	glTranslatef(0.0,4.5,0.0);
	renderCylinder_convenient(0,0,10,0,0,18,1,1,16);
	renderCylinder_convenient(0,0,18,0,0,19,1,0.6,16);
	glTranslatef(0.0,-4.5,0.0);
	glRotatef(40,0,0,1);
	glTranslatef(0.0,4.5,0.0);
	renderCylinder_convenient(0,0,10,0,0,18,1,1,16);
	renderCylinder_convenient(0,0,18,0,0,19,1,0.6,16);
	glTranslatef(0.0,-4.5,0.0);
	glRotatef(140,0,0,1);
	glTranslatef(0.0,4.5,0.0);
	renderCylinder_convenient(0,0,10,0,0,18,1,1,16);
	renderCylinder_convenient(0,0,18,0,0,19,1,0.6,16);
	glTranslatef(0.0,-4.5,0.0);
	glRotatef(40,0,0,1);
	glTranslatef(0.0,4.5,0.0);
	renderCylinder_convenient(0,0,10,0,0,18,1,1,16);
	renderCylinder_convenient(0,0,18,0,0,19,1,0.6,16);

	glPopMatrix();

}


void draw_cannon()
{

		glPushMatrix();


	glRotatef(70,0,0,1);
	glTranslatef(0.0,14,0.0);
	renderCylinder_convenient(0,0,11.5,0,0,16.5,1,1,16);
	renderCylinder_convenient(0,0,5.5,0,0,11.5,0.6,0.6,16);
	glTranslatef(0.0,-14,0.0);
	glRotatef(40,0,0,1);
	glTranslatef(0.0,14,0.0);
	renderCylinder_convenient(0,0,11.5,0,0,16.5,1,1,16);
	renderCylinder_convenient(0,0,5.5,0,0,11.5,0.6,0.6,16);
	glTranslatef(0.0,-14,0.0);
	glRotatef(140,0,0,1);
	glTranslatef(0.0,14,0.0);
	renderCylinder_convenient(0,0,11.5,0,0,16.5,1,1,16);
	renderCylinder_convenient(0,0,5.5,0,0,11.5,0.6,0.6,16);
	glTranslatef(0.0,-14,0.0);
	glRotatef(40,0,0,1);
	glTranslatef(0.0,14,0.0);
	renderCylinder_convenient(0,0,11.5,0,0,16.5,1,1,16);
	renderCylinder_convenient(0,0,5.5,0,0,11.5,0.6,0.6,16);
	glTranslatef(0.0,-14,0.0);

	glPopMatrix();


}


void draw_xwing_vehicle()
{

	renderCylinder_convenient(0,0,-10,0,0,10,2,4,8);
	renderCylinder_convenient(0,0,10,0,0,18,4,4,8);
	glPushMatrix();
	glTranslatef(0,0,-10);
	renderCylinder_convenient(0,0,-4,0,0,0,0,2,8);
	glPopMatrix();


	glPushMatrix();
	glRotatef(20,0,0,1);
	draw_wings();
	glRotatef(-40,0,0,1);
	draw_wings();
	glPopMatrix();

	draw_exhaust();
	draw_cannon();

}


void display_stars()
{

	int i;
	glDisable(GL_LIGHTING);

	glTranslatef(0,0,-100);

		glColor3f(1,1,1);
		glBegin(GL_POINTS);
		for(i=0;i<1000;i++)
		{

			glVertex3f(rand()%600,rand()%600,rand()%600);
			glVertex3f(-rand()%600,rand()%600,rand()%600);
			glVertex3f(-rand()%600,-rand()%600,rand()%600);
			glVertex3f(rand()%600,-rand()%600,rand()%600);
			glVertex3f(rand()%600,rand()%600,-rand()%600);
			glVertex3f(-rand()%600,rand()%600,-rand()%600);
			glVertex3f(-rand()%600,-rand()%600,-rand()%600);
			glVertex3f(rand()%600,-rand()%600,-rand()%600);



		}
		glEnd();


	glEnable(GL_LIGHTING);



}


void init_asteroids()
{


	int i;
	for(i=0;i<50;i++)
	{
		if(i%2==0)
		ast_pos[i][0]=rand()%300;
		else
		ast_pos[i][0]=-rand()%300;

		if(i%3==0)
		ast_pos[i][1]=rand()%300;
		else
		ast_pos[i][1]=-rand()%300;
	


		ast_pos[i][2]=-500+(rand()%500);
	}


}

void idle(int x)
{

	int i;
	for(i=0;i<50;i++)
	ast_pos[i][2]+=1;
	glutTimerFunc(200,idle,0);
	display();
}


void draw_asteroids()
{

	int i;

	for(i=0;i<50;i++)
	{
		glPushMatrix();
		glTranslatef(ast_pos[i][0], ast_pos[i][1], ast_pos[i][2]);
		glutSolidSphere(8, 5,5);
		glPopMatrix();


		

	}


}



void display (void) {
    glClearColor (0.0,0.0,0.0,0.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	gluLookAt(0.0,2.0,10.0,myx,myy,myz,0.0,1.0,0.0);
    light();


	glTranslatef(myx, myy, myz);
	glRotatef(rotation, 0.0, 1.0, 0.0);
	
	draw_xwing_vehicle();
	glTranslatef(-myx, -myy, -myz);

	draw_asteroids();

	glRotatef(-rotation, 0.0, 1.0, 0.0);


	display_stars();

	


 

	
	

	

    glutSwapBuffers();

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
	display();

	

}






int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("A basic OpenGL Window");
    init ();
	init_asteroids();
    glutDisplayFunc (display);
    //glutIdleFunc (idle);
	glutTimerFunc(200,idle,0);
    glutKeyboardFunc (keyboard);
    glutReshapeFunc (reshape);
    glutMainLoop ();
    return 0;
} 