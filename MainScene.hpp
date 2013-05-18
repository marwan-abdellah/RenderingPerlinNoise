#ifndef MAINSCENE_HPP
#define MAINSCENE_HPP

#include "Shared.h"
#include "GL_Utils.h"

/// Prototypes
void mainDisplay(void);

/// Scene Data
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

#endif // MAINSCENE_HPP
