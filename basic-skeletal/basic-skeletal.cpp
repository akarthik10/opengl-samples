
#include <stdlib.h> 	
#include <GL/glut.h>
#include <math.h>

void display (void) {

    glClearColor (1.0,1.0,1.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	glutSwapBuffers();

}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard (unsigned char key, int x, int y)
{

}


void idle()
{
	
}


int main () {
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Window Name");
    glutDisplayFunc (display);
    glutReshapeFunc (reshape);
    glEnable(GL_DEPTH_TEST);
    glutIdleFunc (idle);
    glutKeyboardFunc (keyboard);
    
    glutMainLoop ();
    return 0;
} 