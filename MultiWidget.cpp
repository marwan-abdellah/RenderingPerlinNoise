#include "GL/glut.h"
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;


#define GAP  25             /* gap between subwindows */
GLuint window, View1, View2, View3, View4;
GLuint sub_width = 256, sub_height = 256;

void main_display(void);
void main_reshape(int width,  int height);
void setfont(char* name, int size);
void drawstr(GLuint x, GLuint y, const char* format, int length);
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_10;

void View1Display();
void View2Display();
void View3Display();
void View4Display();

void ResetViewport();

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    //Mode Setting
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    //window size (+gap size)
    glutInitWindowSize(512+GAP*3, 512+GAP*3);
    //Initial position
    glutInitWindowPosition(50, 50);



    //Main Window
    window = glutCreateWindow("ViewPort Test");
    //Main Window callback function
    glutReshapeFunc(main_reshape);
    glutDisplayFunc(main_display);

    //World Window and Display
    View1 = glutCreateSubWindow(window, GAP, GAP, 256, 256);
    glutDisplayFunc(View1Display);

    //screen Window and Display
    View2 = glutCreateSubWindow(window, GAP+256+GAP, GAP, 256, 256);
    glutDisplayFunc(View2Display);

    //command Window and Display
    View3 = glutCreateSubWindow(window, GAP+256+GAP, GAP+256+GAP, 256, 256);
    glutDisplayFunc(View3Display);

    View4 = glutCreateSubWindow(window, GAP+256+GAP, GAP+256+GAP, 256, 256);
    glutDisplayFunc(View4Display);


    glutMainLoop();

    return 0;
}

void main_display(void)
{
    //Background Color
    glClearColor(0.8, 0.8, 0.8, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //font color and style
    glColor3ub(0, 0, 0);
    setfont("helvetica", 12);

    //1st window name
    string str = "View1";
    drawstr(GAP, GAP-5, str.c_str(), str.length());

    //2st window name
    str = "View2";
    drawstr(GAP+sub_width+GAP, GAP-5, str.c_str(), str.length());

    //3st widnow name
    str = "View3";
    drawstr(GAP, GAP+sub_height+GAP-5, str.c_str(), str.length());

    //4st widnow name
    str = "View4";
    drawstr(GAP+sub_width+GAP, GAP+sub_height+GAP-5, str.c_str(), str.length());

    //last
    glutSwapBuffers();
}


//Background Window Setting
void main_reshape(int width,  int height)
{
    //main view setting
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    sub_width = (width-GAP*3)/2.0;
    sub_height = (height-GAP*3)/2.0;

    //View1 Display
    glutSetWindow(View1);
    glutPositionWindow(GAP, GAP);
    glutReshapeWindow(sub_width, sub_height);

    //View2 Display
    glutSetWindow(View2);
    glutPositionWindow(GAP+sub_width+GAP, GAP);
    glutReshapeWindow(sub_width, sub_height);

    //View3 Display
    glutSetWindow(View3);
    glutPositionWindow(GAP, GAP+sub_height+GAP);
    glutReshapeWindow(sub_width, sub_height);


    //View4 Display
    glutSetWindow(View4);
    glutPositionWindow(GAP+sub_width+GAP, GAP+sub_height+GAP);
    glutReshapeWindow(sub_width, sub_height);
    //glutReshapeWindow(sub_width+GAP+sub_width, sub_height);
}

//Font setting
void setfont(char* name, int size)
{
    font_style = GLUT_BITMAP_HELVETICA_10;
    if (strcmp(name, "helvetica") == 0) {
        if (size == 12)
            font_style = GLUT_BITMAP_HELVETICA_12;
        else if (size == 18)
            font_style = GLUT_BITMAP_HELVETICA_18;
    } else if (strcmp(name, "times roman") == 0) {
        font_style = GLUT_BITMAP_TIMES_ROMAN_10;
        if (size == 24)
            font_style = GLUT_BITMAP_TIMES_ROMAN_24;
    } else if (strcmp(name, "8x13") == 0) {
        font_style = GLUT_BITMAP_8_BY_13;
    } else if (strcmp(name, "9x15") == 0) {
        font_style = GLUT_BITMAP_9_BY_15;
    }
}

//String Draw
void drawstr(GLuint x, GLuint y, const char* format, int length)
{
    glRasterPos2i(x, y);
    for(int i=0; i<length; ++i)
        glutBitmapCharacter(font_style, *(format+i) );
}


//Display Teapot
void DrawScene()
{

    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    //glTranslatef(0.0, -1.0, 0.0);

    glBegin(GL_QUADS);
    glVertex3f(2.0, 0.0, 2.0);
    glVertex3f(2.0, 0.0, -2.0);
    glVertex3f(-2.0, 0.0, -2.0);
    glVertex3f(-2.0, 0.0, 2.0);
    glEnd();

    glPopMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.5);
    glutWireTeapot(1.0);
    glPopMatrix();

}

//View1Display
void View1Display(){


    //viewport rest;
    ResetViewport();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    DrawScene();
    glPopMatrix();
    glutSwapBuffers();
}

//View2Display
void View2Display(){

    //viewport rest;
    ResetViewport();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    gluLookAt(1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    DrawScene();
    glPopMatrix();
    glutSwapBuffers();
}

//View3Display
void View3Display(){

    //viewport rest;
    ResetViewport();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    gluLookAt(0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
    DrawScene();
    glPopMatrix();
    glutSwapBuffers();
}


//View4Display
void View4Display(){

    //viewport rest;
    ResetViewport();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(30, 1.0, 3.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    DrawScene();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}


void ResetViewport()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
