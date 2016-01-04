#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<string.h>

int Wx=500,Wy=500;
const int sceneLength = 6;
float myx=10.0, myy=250.0;
float offset = 50.0;
float jump_value = 100;
int jump_started = 0;
float jump_angle = 0.0;
float jump_progress = 0.0;
float speed = 0.05;
float obstacleSquareSize = Wy/10.0;
int levelOne[] = {3, 4, 5, 6 , 4, 3, 7, 8, 9, 6};
int levelLength = 10;
float obstacleWidth = 100.0;
float obstacleGap = 250.0;
int birdSize = 50.0;
float skyR = 0.5294;
float gravity = 0.20;
float obstacleSpace = 2.0;
int crashes = 0;
int crash_started = 0;
char crashText[100];
int gameEnd = 0;


void DrawCircle(float cx, float cy, float r, int num_segments) 
{ 
	glBegin(GL_POLYGON); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta) + birdSize/2;//calculate the x component 
		float y = r * sinf(theta) + birdSize/2;//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	} 
	glEnd(); 
	glPushMatrix();
	glTranslatef(birdSize/1.4, birdSize/2, 0);

	glColor3f(1,1,0);
	glBegin(GL_POLYGON);
 	glVertex2f(0,0);
 	glVertex2f(0,5);
 	glVertex2f(15,0);
 	glVertex2f(0,-5);
 	glVertex2f(0,5);
 	glEnd();

 	glPopMatrix();

 	glPushMatrix();
 	glTranslatef(0, 5, 0);
 	glColor3f(1,1,1);
 		glBegin(GL_POLYGON); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r/5 * cosf(theta) + birdSize/2;//calculate the x component 
		float y = r/5 * sinf(theta) + birdSize/2;//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	} 
	glEnd(); 

	glColor3f(0,0,0);
 		glBegin(GL_POLYGON); 
	for(int ii = 0; ii < num_segments; ii++) 
	{ 
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r/8 * cosf(theta) + birdSize/2;//calculate the x component 
		float y = r/8 * sinf(theta) + birdSize/2;//calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	} 
	glEnd(); 
	glPopMatrix();

}

void drawText(char *string,float x,float y,float z) 
{  
char *c;
glRasterPos3f(x, y,z);
for (c=string; *c != '\0'; c++) 
{
	if(*c=='\n')
	glRasterPos3f(x, y-0.05,z);
	else
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *c);
}
}


void drawBird() {
	glColor3f(1.0,0.0,0.0);
// glBegin(GL_POLYGON);
// glVertex2f(0.0, 0.0);
// glVertex2f(0.0, 50.0);
// glVertex2f(50.0, 50.0);
// glVertex2f(50.0, 0.0);
// glEnd();
	DrawCircle(0,0,20.0, 32);
}

void drawSky(){
	glColor3f(skyR,0.8078,0.9803);
glBegin(GL_POLYGON);
 glVertex2f(0,0);
 glVertex2f(0,500);
 glVertex2f(500*sceneLength,500);
 glVertex2f(500*sceneLength,0);
 glEnd();
}

int collisionDetector(int i, float x, float y, float offset_x)
{
	int ip1 = (levelOne[i]+obstacleSpace)>10?10:(levelOne[i]+obstacleSpace);
int im1 = (levelOne[i]-obstacleSpace)>0?(levelOne[i]-obstacleSpace):0;


	float leftBottomX = x;
	float leftBottomY = y;

	float leftTopX = x;
	float leftTopY = y+birdSize;

	float rightTopX = x+birdSize;
	float rightTopY = y+birdSize;

	float rightBottomX = x+birdSize;
	float rightBottomY = y;

	float BottomObstacleX = offset_x;
	float BottomObstacleY = im1*obstacleSquareSize;

	float TopObstacleX = offset_x;
	float TopObstacleY = ip1*obstacleSquareSize;

	if(leftBottomY < 0) return 1;
	if(rightBottomX > BottomObstacleX && leftBottomX<BottomObstacleX+obstacleWidth && rightBottomY < BottomObstacleY) return 1;
	// printf("%f %f %f %f ",rightBottomX ,BottomObstacleX ,leftBottomX, BottomObstacleX+obstacleWidth);
	if(rightTopX > TopObstacleX && leftTopX < TopObstacleX+obstacleWidth && rightTopY > TopObstacleY) return 1;
	
	return 0;




	
}


void drawObstacle(int i)
{
	glColor3f(0.0,1.0,0.0);

int ip1 = (levelOne[i]+obstacleSpace)>10?10:(levelOne[i]+obstacleSpace);
int im1 = (levelOne[i]-obstacleSpace)>0?(levelOne[i]-obstacleSpace):0;

glBegin(GL_POLYGON);
glVertex2f(0.0, 0.0);
glVertex2f(0.0, im1*obstacleSquareSize);
glVertex2f(obstacleWidth, im1*obstacleSquareSize);
glVertex2f(obstacleWidth, 0.0);
glEnd();

glColor3f(1.0,1.0,0.0);
glBegin(GL_POLYGON);
glVertex2f(0.0,ip1*obstacleSquareSize);
glVertex2f(0.0, Wy);
glVertex2f(obstacleWidth, Wy);
glVertex2f(obstacleWidth, ip1*obstacleSquareSize);
glEnd();


}
void init()
{
glClearColor(1.0,1.0,1.0,1.0);
glColor3f(1.0,0.0,0.0);
glPointSize(5.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0+myx-offset,Wx+myx-offset,0.0,Wy);
glutPostRedisplay();
}

char* itoa(int i, char b[]){
    char const digit[] = "0123456789";
    char* p = b;
    if(i<0){
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return b;
}


void display(void)
{
init();
glClear(GL_COLOR_BUFFER_BIT);




drawSky();

if(gameEnd) {
	glPushMatrix();
glTranslatef(myx+150,250,0);
glColor3f(1.0,0.0,0.0);



drawText(  "Game Over", 5,5,0);
drawText(  "You crashed", 5,25,0);
drawText(  itoa(crashes, crashText), 120,25,0);
drawText(  " times", 130,25,0);
glPopMatrix();
glFlush();
	return;
}

glPushMatrix();
if(jump_started) {
	jump_angle += 0.005;
	jump_progress=sin(jump_angle)*jump_value;
	if(jump_angle*180/3.14>90) {
		myy+=jump_progress;
		jump_started = 0;
		jump_progress = 0;
		jump_angle = 0;
	}
}
glTranslatef(myx,myy+jump_progress,0.0);
drawBird();
glPopMatrix();

float obstacleCursor = 100;
int c=0;
for(int i=0; i<levelLength; i++){
	glPushMatrix();
glTranslatef(obstacleCursor,0,0);
drawObstacle(i);
if(!c){
c=collisionDetector(i, myx, myy+jump_progress, obstacleCursor);

}

glPopMatrix();

obstacleCursor+=obstacleGap;
}

if(c) {skyR = 1.0; crash_started = 1; } else {skyR = 0.5294; if(crash_started) {crash_started = 0; crashes++; printf("\n%d\n", crashes);}}
	


if(myx>2500) gameEnd=1;  


glPushMatrix();
glTranslatef(myx,50,0);
glColor3f(1.0,0.0,0.0);



drawText(  itoa(crashes, crashText), 5,5,0);
glPopMatrix();

glFlush();
}

void idle() {
	myx+=speed;
	if(!jump_started)
	myy-=gravity;
	glutPostRedisplay();
}


void processNormalKeys(unsigned char key, int x, int y) {

	if (key == 32){
		if(jump_started) {
			myy+=jump_progress;
			jump_angle=0;
			jump_progress=0;
		}
		jump_started = 1;
	} 
}


int main(int argc,char **argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(Wx,Wy);
glutInitWindowPosition(0,0);
glutCreateWindow("Flappy Bird");
glutDisplayFunc(display);
glutIdleFunc(idle);
glutKeyboardFunc(processNormalKeys);
init();
glutMainLoop();
}
