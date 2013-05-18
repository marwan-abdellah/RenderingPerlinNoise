#ifndef MAINSCENE_HPP
#define MAINSCENE_HPP

#include "Shared.h"
#include "GL_Utils.h"
#include "VolumeSharedData.h"
#include "Utils.h"
#include "DisplayList.hpp"


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

void DrawScene2()
{

    glColor3f(0.7, 0.7, 0.7);

    // Enabling 3D texturing
    glEnable(GL_TEXTURE_3D);

    // Update texture and upload it to the GPU
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_3D, volumeTexID);

    glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0,
                    _volumeWidth, _volumeHeight, _volumeDepth, GL_RGBA, GL_UNSIGNED_BYTE, _RGBAVolumeData);


    // Cleraing color buffers
    glClear(GL_COLOR_BUFFER_BIT);

    // Clip planes
    static GLdouble eqx0[4] = { 1.0, 0.0, 0.0, 0.0};
    static GLdouble eqx1[4] = {-1.0, 0.0, 0.0, 1.0};
    static GLdouble eqy0[4] = {0.0,  1.0, 0.0, 0.0};
    static GLdouble eqy1[4] = {0.0, -1.0, 0.0, 1.0};
    static GLdouble eqz0[4] = {0.0, 0.0,  1.0, 0.0};
    static GLdouble eqz1[4] = {0.0, 0.0, -1.0, 1.0};

    // Define equations for automatic texture coordinate generation
    static GLfloat x[] = {1.0, 0.0, 0.0, 0.0};
    static GLfloat y[] = {0.0, 1.0, 0.0, 0.0};
    static GLfloat z[] = {0.0, 0.0, 1.0, 0.0};

    // Adjusting the matrix state
    glPushMatrix ();

    // Scaling
    float scaleFactor;
    if (glutGetWindow() == view1)
        scaleFactor = _scaleW1;
    else if (glutGetWindow() == view2)
        scaleFactor = _scaleW2;
    else if (glutGetWindow() == view3)
        scaleFactor = _scaleW3;
    else
        scaleFactor = _scaleW4;


    glScalef(scaleFactor, scaleFactor, scaleFactor);

    glPushMatrix ();

    // Transform the viewing direction
    glRotatef(-zRotation, 0.0, 0.0, 1.0);
    glRotatef(-yRotation, 0.0, 1.0, 0.0);
    glRotatef(-xRotation, 1.0, 0.0, 0.0);

    // center the cube
    glTranslatef(-0.5, -0.5, -0.5);

    // Take a copy of the model view matrix now shove it in to the GPU
    // buffer for later use in automatic texture coord generation.
    glTexGenfv(GL_S, GL_EYE_PLANE, x);
    glTexGenfv(GL_T, GL_EYE_PLANE, y);
    glTexGenfv(GL_R, GL_EYE_PLANE, z);

    glClipPlane(GL_CLIP_PLANE0, eqx0);
    glClipPlane(GL_CLIP_PLANE1, eqx1);

    glClipPlane(GL_CLIP_PLANE2, eqy0);
    glClipPlane(GL_CLIP_PLANE3, eqy1);

    glClipPlane(GL_CLIP_PLANE4, eqz0);
    glClipPlane(GL_CLIP_PLANE5, eqz1);

    glPopMatrix ();

    // Enable clip planes
    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);
    glEnable(GL_CLIP_PLANE2);
    glEnable(GL_CLIP_PLANE3);
    glEnable(GL_CLIP_PLANE4);
    glEnable(GL_CLIP_PLANE5);

    // Rendering the diaply list of the rectangles
    glCallList(listName);

    glPopMatrix ();

    // Swap the buffers
    glutSwapBuffers();

    // Disabling texturing
    glDisable(GL_TEXTURE_3D);
}

#endif // MAINSCENE_HPP
