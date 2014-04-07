#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>

static int m=0,M=0,v=0,V=0,E=0,e=0,r=0,R=0,j=0,J=0,s=0,S=0,U=0,u=0,n=0,N=0,X=0,z=0,B=0,b=0,c=0;
static GLint axis=2;
GLfloat viewer[3]={0.0,10.0,2.0};
GLfloat diffuseMaterial[4]={0.5,0.5,0.5,1.0};


void myinit(void)
{
 glClearColor(0.0,0.0,0.0,0.0);
 glShadeModel(GL_SMOOTH);
 glEnable(GL_DEPTH_TEST);
 GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
 GLfloat light_position[]={1.0,1.0,1.0,1.0};
 GLfloat shiny[]={25.0f};
 glMaterialfv(GL_FRONT,GL_DIFFUSE,diffuseMaterial);
 glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
 glMaterialfv(GL_FRONT,GL_SHININESS,shiny);
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);
 glLightfv(GL_LIGHT0,GL_POSITION,light_position);
 glColorMaterial(GL_FRONT,GL_DIFFUSE);
 glEnable(GL_COLOR_MATERIAL);
}

void display_stars()
{

	int i;
	glDisable(GL_LIGHTING);

	//glTranslatef(0,0,-100);

		glColor3f(1,1,1);
		glBegin(GL_POINTS);
		for(i=0;i<1000;i++)
		{

			glVertex3f(rand()%40,rand()%40,rand()%40);
			glVertex3f(-rand()%40,rand()%40,rand()%40);
			glVertex3f(-rand()%40,-rand()%40,rand()%40);
			glVertex3f(rand()%40,-rand()%40,rand()%40);
			glVertex3f(rand()%40,rand()%40,-rand()%40);
			glVertex3f(-rand()%40,rand()%40,-rand()%40);
			glVertex3f(-rand()%40,-rand()%40,-rand()%40);
			glVertex3f(rand()%40,-rand()%40,-rand()%40);



		}
		glEnd();


	glEnable(GL_LIGHTING);



}


void display(void)
{
 GLfloat postition[]={0.0,0.0,1.5,1.0};
 glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
 glColor3f(1.0,0.5,0.0);
 glPushMatrix();
 glRotatef((GLfloat)z,1.0,1.0,1.0);
 
 glDisable(GL_LIGHTING);
 glutSolidSphere(0.8,40,16);
 glPopMatrix();
 glPushMatrix();
 
 glDisable(GL_LIGHTING);
 glEnable(GL_LIGHTING);
 glColor3f(1.5,0.5,0.0);
 glutSolidTorus(0.2,0.9,6,20);
 glPopMatrix();
 glPushMatrix();
 glRotatef((GLfloat)M,0.0,1.0,0.0);
 glTranslatef(1.5,0.0,0.0);
 glRotatef((GLfloat)m,0.0,1.0,0.0);
 glColor3f(1.0,0.0,0.0);
 glutSolidSphere(0.2,20,8);
 glPopMatrix();
 glPushMatrix();
 glRotatef((GLfloat)V,0.0,1.0,0.0);
 glTranslatef(2.0,0.0,1.0);
 glRotatef((GLfloat)v,0.0,1.0,0.0);
 glColor3f(7.5,9.5,1.0);
 glutSolidSphere(0.2,20,8);
 glPopMatrix();
 glPushMatrix();
 glRotatef((GLfloat)E,0.0,1.0,0.0);
 glTranslatef(3.5,0.0,0.0);
 glRotatef((GLfloat)e,0.0,1.0,0.0);
 glColor3f(0.1,6.5,2.0);
 glutSolidSphere(0.2,20,8);
 glRotatef((GLfloat)X,0.0,1.0,0.0);
 glTranslatef(0.3,0.2,0.0);
 glColor3f(4.3,3.5,8.0);
 glutSolidSphere(0.1,20,14);
 glPopMatrix();
 glPushMatrix();
 glRotatef((GLfloat)R,0.0,1.0,0.0);
 glTranslatef(5.0,0.0,3.0);
 glRotatef((GLfloat)r,0.0,1.0,0.0);
 glColor3f(1.0,2.0,0.0);
 glutSolidSphere(0.2,20,8);
 glPopMatrix();
 glPushMatrix();
 glRotatef((GLfloat)J,0.0,1.0,0.0);
 glTranslatef(-2.5,0.0,1.0);
 glRotatef((GLfloat)j,0.0,1.0,0.0);
 glColor3f(0.9,0.7,0.3);
 glutSolidSphere(0.2,20,8);
 glPopMatrix();
 glPushMatrix();
 glRotatef((GLfloat)S,0.0,1.0,0.0);
 glTranslatef(-5.0,0.0,0.0);
// gluLookAt(0.0,10.0,2.0,1.0,0.0,0.0,0.0,1.0,0.0);
 glRotatef((GLfloat)s,0.0,0.0,5.0);
 glColor3f(4.5,0.5,0.0);
 glutSolidSphere(0.5,20,16);
 int i=0;
 glBegin(GL_QUAD_STRIP);
 for(i=0;i<=360;i++)
 {
   glVertex3f(sin(i*3.1416/180)*0.5,cos(i*3.1416/180)*0.5,0);
   glVertex3f(sin(i*3.1416/180)*0.7,cos(i*3.1416/180)*0.7,0);
 }
 glEnd();
 glPopMatrix();
 glPushMatrix();
 glRotatef((GLfloat)U,0.0,1.0,0.0);
 glTranslatef(-6.5,0.0,0.0);
 //gluLookAt(10.0,0.0,0.0,0.0,0.0,0.0,0.0,10.0,1.0);
 glRotatef((GLfloat)u,0.0,0.0,5.0);
 glColor3f(1.2,0.0,0.2);
 glutSolidSphere(0.5,20,16);
 glBegin(GL_QUAD_STRIP);
 for(i=0;i<=360;i++)
 {
  glVertex3f(sin(i*3.1416/180)*0.5,cos(i*3.1416/180)*0.5,0);
  glVertex3f(sin(i*3.1416/180)*0.7,cos(i*3.1416/180)*0.7,0);
 }
glEnd();
glPopMatrix();
glPushMatrix();
glRotatef((GLfloat)N,0.0,1.0,0.0);
glTranslatef(-8.0,0.0,0.0);
glRotatef((GLfloat)n,0.0,1.0,0.0);
glColor3f(1.0,2.0,0.0);
glutSolidSphere(0.4,20,8);
glPopMatrix();
glPushMatrix();
glRotatef((GLfloat)M,0.0,1.0,0.0);
glTranslatef(1.5,0.0,0.0);
glRotatef((GLfloat)m,0.0,1.0,0.0);
glColor3f(1.0,0.0,0.0);
glutSolidSphere(0.2,20,8);
glPopMatrix();
glPushMatrix();
glRotatef((GLfloat)c,6.0,-14.0,-6.0);
glTranslatef(5.0,3.0,-1.0);
glScalef(0.60,0.0,2.5);
glColor3f(7.5,9.5,2.0);
glutSolidSphere(0.2,12,6);
glPopMatrix();
glPushMatrix();

glTranslatef(0,0,-8);
glScalef(0.3,0.3,0.3);
glutSolidSphere(0.1, 16,16);

glTranslatef(7,-9,14);

glutSolidSphere(0.1, 16,16);

glTranslatef(-8,11,6);

glutSolidSphere(0.1, 16,16);

glTranslatef(15,14,-14);

glutSolidSphere(0.1, 16,16);

glTranslatef(.20,.36,.9);

glutSolidSphere(0.1, 16,16);

glPopMatrix();

display_stars();
glutSwapBuffers();
}
void reshape(int w,int h)
{
 glViewport(0,0,(GLsizei)w,(GLsizei)h);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(60.0,(GLfloat)w/(GLfloat)h,1.0,20.0);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(0,0,10,1.0,0.0,0.0,0.0,1.0,0.0);
}

void special(int key,int x,int y)
{

	if(key==GLUT_KEY_LEFT) viewer[2]++;
	if(key==GLUT_KEY_RIGHT) viewer[2]--;
	if(key==GLUT_KEY_UP) viewer[0]++;
	if(key==GLUT_KEY_DOWN) viewer[0]--;

	display();



}

void keyboard(unsigned char key,int x,int y)
{
 switch(key)
 {
   case 'z':z=(z+50)%360;
            glutPostRedisplay();
            break;
   case 'm':m=(m+3)%360;
            glutPostRedisplay();
            break;
   case 'M':M=(M+12)%360;
            glutPostRedisplay();
            break;
   case 'v':v=(v+2)%360;
            glutPostRedisplay();
            break;
   case 'V':V=(V+10)%360;
            glutPostRedisplay();
            break;
   case 'e':e=(e+5)%360;
            glutPostRedisplay();
            break;
   case 'E':E=(E+8)%360;
            glutPostRedisplay();
            break;
   case 'r':r=(r+6)%360;
            glutPostRedisplay();
            break;
   case 'R':R=(R+6)%360;
            glutPostRedisplay();
            break;
   case 'j':j=(j+10)%360;
            glutPostRedisplay();
            break;
   case 'J':J=(J+4)%360;
            glutPostRedisplay();
            break;
   case 's':s=(s+9)%360;
            glutPostRedisplay();
            break;
   case 'S':S=(S+3)%360;
            glutPostRedisplay();
            break;
   case 'u':u=(u+8)%360;
            glutPostRedisplay();
            break;
   case 'U':U=(U+2)%360;
            glutPostRedisplay();
            break;
   case 'n':n=(n+7)%360;
            glutPostRedisplay();
            break; 
    case 'N':N=(N+1)%360;
            glutPostRedisplay();
            break;
   case 'b':b=(b+10)%360;
            glutPostRedisplay();
            break;
   case 'c':c=(c+1)%360;
            //b=(b+10)%360;
            glutPostRedisplay();
            break;
   case 'X':X=(X+5)%360;
            glutPostRedisplay();
            break;
 case 'a':z=(z+50)%360;
          b=(b+10)%360;
          m=(m+3)%360;
          v=(v+2)%360; 
          e=(e+5)%360;
          r=(r+6)%360;
          j=(j+10)%360;
          s=(s+9)%360;
          u=(u+8)%360;
          n=(n+7)%360; 
          c=(c+1)%360;
          glutPostRedisplay();
          break;

case 'A':z=(z+50)%360;
          b=(b+10)%360;
          M=(M+12)%360;
          V=(V+10)%360;
          E=(E+8)%360;
          R=(R+6)%360;
          J=(J+4)%360;
          S=(S+3)%360;
          U=(U+2)%360;
          N=(N+1)%360;
          c=(c+1)%360;
          glutPostRedisplay();
          break;
case 'B':z=(z+50)%360;
          b=(b+10)%360;
          c=(c+1)%360;
          m=(m+3)%360;
          M=(M+12)%360;
          v=(v+2)%360;
          V=(V+10)%360;
          e=(e+5)%360;
          E=(E+8)%360;
          r=(r+6)%360;
          R=(R+6)%360;
          j=(j+10)%360;
          J=(J+4)%360;
          s=(s+9)%360;
          S=(S+3)%360;
          u=(u+8)%360;
          U=(U+2)%360;
          n=(n+7)%360;
          N=(N+1)%360;
          glutPostRedisplay();
          break;

case 'q':exit(0);
       break;
default:break;
}
}

void mouse(int btn,int state,int x,int y)
{
 if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
 {
          z=(z+50)%360;
          b=(b+10)%360;
          c=(c+1)%360;
          m=(m+3)%360;
          M=(M+12)%360;
          v=(v+2)%360;
          V=(V+10)%360;
          e=(e+5)%360;
          E=(E+8)%360;
          r=(r+6)%360;
          R=(R+6)%360;
          j=(j+10)%360;
          J=(J+4)%360;
          s=(s+9)%360;
          S=(S+3)%360;
          u=(u+8)%360;
          U=(U+2)%360;
          n=(n+7)%360;
          N=(N+1)%360;
          glutPostRedisplay();
 }

 if(btn==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
 {
            
         z=(z-50)%360;
          b=(b-10)%360;
          c=(c-1)%360;
          m=(m-3)%360;
          M=(M-12)%360;
          v=(v-2)%360;
          V=(V-10)%360;
          e=(e-5)%360;
          E=(E-8)%360;
          r=(r-6)%360;
          R=(R-6)%360;
          j=(j-10)%360;
          J=(J-4)%360;
          s=(s-9)%360;
          S=(S-3)%360;
          u=(u-8)%360;
          U=(U-2)%360;
          n=(n-7)%360;
          N=(N-1)%360;
          glutPostRedisplay();
 }     
}


int main()
{

 printf(" press 'M' for rotation and 'm' for revolution of mercury \n"); 
 printf(" press 'V' for rotation and 'v' for revolution of venus \n");         
 printf(" press 'E' for rotation and 'e' for revolution of earth \n"); 
 printf(" press 'R' for rotation and 'r' for revolution of mars \n");        
 printf(" press 'J' for rotation and 'j' for revolution of jupitor \n");
 printf(" press 'S' for rotation and 's' for revolution of saturn \n");
 printf(" press 'U' for rotation and 'u' for revolution of uranus \n");         
 printf(" press 'N' for rotation and 'n' for revolution of neptune \n");         
 printf(" press 'c' for movement of comet \n");
 printf(" press 'b' for blinking of stars \n");
 printf(" press 'a' for rotation of all planets \n");
 printf(" press 'A' for revolution of all planets \n");
 printf(" press 'B' for both rotation and revolution of planets \n");
 glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
 glutInitWindowSize(500,500);
 glutInitWindowPosition(100,100);
 glutCreateWindow("SOLAR SYSTEM ");
 myinit();
 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutKeyboardFunc(keyboard);
 glutSpecialFunc(special);
 glutMouseFunc(mouse);
 glEnable(GL_DEPTH_TEST);
 glutMainLoop();
 return 0;
}         
          