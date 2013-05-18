#include "GL/glut.h"
#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;


// Gap between the different viewports
#define GAP  10

GLuint sub_width = 256, sub_height = 256;

GLuint window;
GLuint view1, view2, view3, view4;
GLuint screenWidth;
GLuint screenHeight;

void mainDisplay(void);
void mainReshape(int width,  int height);
void setfont(char* name, int size);
void drawstr(GLuint x, GLuint y, const char* format, int length);
GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_10;

void View1Display();
void View2Display();
void View3Display();
void View4Display();

void ResetViewport();

///
int main(int argc, char** argv)
{
    // GLUT initialization
    glutInit(&argc, argv);

    // getting the screen resolution to adjust the rest of the application accordinglly
    screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    cout << "SCREEN_WIDTH : " << screenWidth << endl;
    cout << "SCREEN_HEIGHT : " << screenHeight << endl;

    // GLUT mode settings, RGB, depth buffer, double buffering
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    // Center the window in the middle of the screen
    int windowPosX = (screenWidth / 2) - (screenWidth / 4);
    int windowPosY = (screenHeight / 2) - (screenHeight / 4);

    // Initial window position
    glutInitWindowPosition(windowPosX, windowPosY);

    // Make square widgets
    if (screenWidth != screenHeight)
    {
        if (screenWidth < screenHeight)
            screenHeight = screenWidth;
        else
            screenWidth = screenHeight;
    }

    // Window size inclusing the gaps
    glutInitWindowSize(screenWidth, screenHeight);

    // Main window creation
    window = glutCreateWindow("MultiViewPort Window (multi Widgets)");

    // Main window callback function
    glutReshapeFunc(mainReshape);
    glutDisplayFunc(mainDisplay);

    // Calculating the viewports dimensions
    float viewportWidth = screenWidth / 4;
    float viewportHeight = screenHeight / 4;

    // View 1 viewport
    view1 = glutCreateSubWindow(window, GAP, GAP,
                                viewportWidth, viewportHeight);
    glutDisplayFunc(View1Display);

    // View 2 viewport
    view2 = glutCreateSubWindow(window, GAP + viewportWidth + GAP,
                                GAP, viewportWidth, viewportHeight);
    glutDisplayFunc(View2Display);

    // View 3 viewport
    view3 = glutCreateSubWindow(window, GAP+viewportWidth+GAP,
                                GAP + viewportHeight + GAP, viewportWidth, viewportHeight);
    glutDisplayFunc(View3Display);

    // View 4 viewport
    view4 = glutCreateSubWindow(window, GAP + viewportWidth + GAP,
                                GAP + viewportHeight + GAP, viewportWidth, viewportHeight);
    glutDisplayFunc(View4Display);

    /// MAIN LOOP ! Should be multi-threaded
    glutMainLoop();

    return 0;
}

///
void mainDisplay(void)
{
    // Background Color
    glClearColor(0.8, 0.8, 0.8, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Font color and style
    glColor3ub(0, 0, 0);
    setfont("helvetica", 12);

    // Window 1 name
    string str = "Window 1";
    drawstr(GAP, GAP-5, str.c_str(), str.length());

    // Window 2 name
    str = "Window 2";
    drawstr(GAP + sub_width+GAP, GAP - 5, str.c_str(), str.length());

    // Window 3 name
    str = "Window 3";
    drawstr(GAP, GAP + sub_height + GAP - 5, str.c_str(), str.length());

    // Window 4 name
    str = "Window 4";
    drawstr(GAP + sub_width + GAP, GAP + sub_height + GAP - 5, str.c_str(), str.length());

    /// BUFFER SWAPPING ! Double buffering
    glutSwapBuffers();
}


///
void mainReshape(int width,  int height)
{
    // Main view setting
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    sub_width = (width-GAP*3)/2.0;
    sub_height = (height-GAP*3)/2.0;

    //view1 Display
    glutSetWindow(view1);
    glutPositionWindow(GAP, GAP);
    glutReshapeWindow(sub_width, sub_height);

    //view2 Display
    glutSetWindow(view2);
    glutPositionWindow(GAP+sub_width+GAP, GAP);
    glutReshapeWindow(sub_width, sub_height);

    //view3 Display
    glutSetWindow(view3);
    glutPositionWindow(GAP, GAP+sub_height+GAP);
    glutReshapeWindow(sub_width, sub_height);


    //view4 Display
    glutSetWindow(view4);
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
