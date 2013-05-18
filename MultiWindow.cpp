#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <GL/gl.h>

int window2 = 0, window = 0, width = 400, height = 400;

void display(void)
{
    glClearColor(0.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    printf("display1\n");
    glFlush();
}

void display2(void)
{
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    printf("display2\n");
    glFlush();
}

void reshape (int w, int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    // Initialization stuff
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(width, height);

    // Make Main outer window
    window = glutCreateWindow("Window 1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // Create First subwindow
    window2 = glutCreateWindow("Window 2");
    glutDisplayFunc(display2);
    glutReshapeFunc(reshape);

    // Enter Glut Main Loop and wait for events
    glutMainLoop();
    return 0;
}
