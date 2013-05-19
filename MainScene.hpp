#ifndef MAINSCENE_HPP
#define MAINSCENE_HPP

#include "Shared.h"
#include "GL_Utils.h"
#include "VolumeSharedData.h"
#include "Utils.h"
#include "DisplayList.hpp"

/// Rendering volume
/*********************************************************************
 * Copyright © 2011-2012,
 * Marwan Abdellah: <abdellah.marwan@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 ********************************************************************/

void DrawScene()
{

    // Enabling 3D texturing
    glEnable(GL_TEXTURE_3D);

    // Update texture and upload it to the GPU
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBindTexture(GL_TEXTURE_3D, _volumeTexID);

    glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0,
                    _volumeWidth, _volumeHeight, _volumeDepth,
                    GL_RGBA, GL_UNSIGNED_BYTE, _RGBAVolumeData);

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
        scaleFactor = VP1::_scale;
    else if (glutGetWindow() == view2)
        scaleFactor = VP2::_scale;
    else if (glutGetWindow() == view3)
        scaleFactor = VP3::_scale;
    else
        scaleFactor = VP4::_scale;

    glScalef(scaleFactor, scaleFactor, scaleFactor);

    glPushMatrix ();

    // Transform the viewing direction
    if (glutGetWindow() == view1)
    {
        glRotatef(VP1::_xRot, 0.0, 0.0, 1.0);
        glRotatef(VP1::_yRot, 0.0, 1.0, 0.0);
        glRotatef(VP1::_zRot, 1.0, 0.0, 0.0);
    }
    else if (glutGetWindow() == view2)
    {
        glRotatef(VP2::_xRot, 0.0, 0.0, 1.0);
        glRotatef(VP2::_yRot, 0.0, 1.0, 0.0);
        glRotatef(VP2::_zRot, 1.0, 0.0, 0.0);
    }
    else if (glutGetWindow() == view3)
    {
        glRotatef(VP3::gRot[0], 0.0, 0.0, 1.0);
        glRotatef(VP3::gRot[1], 0.0, 1.0, 0.0);
        glRotatef(VP3::gRot[2], 1.0, 0.0, 0.0);
    }
    else
    {
        glRotatef(VP4::_xRot, 0.0, 0.0, 1.0);
        glRotatef(VP4::_yRot, 0.0, 1.0, 0.0);
        glRotatef(VP4::_zRot, 1.0, 0.0, 0.0);
    }

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
    if (glutGetWindow() == view1)
        glCallList(VP1::listName);

    else
        glCallList(listName);

    glPopMatrix ();

    // Swap the buffers
    glutSwapBuffers();

    // Disabling texturing
    glDisable(GL_TEXTURE_3D);
}

#endif // MAINSCENE_HPP
