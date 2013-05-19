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

#ifndef VIEWPORT2_HPP
#define VIEWPORT2_HPP

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "GL/glut.h"

#include "Shared.h"
#include "GL_Utils.h"
#include "MainScene.hpp"
#include "VolumeSharedData.h"
#include "DisplayList.hpp"
#include "MainScene.hpp"
#include "ReadVolume.hpp"

#include "ViewPorts.h"

using namespace std;
namespace ViewPort2
{
void Display();
void Keyboard(unsigned char fKey, int fX, int fY);
void RegisterCallBacks();
void UpdateScene();
void Idle();
void Reshape(int volumeWidth, int volumeHeight);
}

void ViewPort2::RegisterCallBacks()
{
    glutDisplayFunc(ViewPort2::Display);
    glutKeyboardFunc(ViewPort2::Keyboard);
    glutIdleFunc(ViewPort2::Idle);
    glutReshapeFunc(ViewPort2::Reshape);

}

void ViewPort2::Idle()
{

    int currentWindow = glutGetWindow();
      glutSetWindow(window);
      glutPostRedisplay();
      glutSetWindow(view2);
      glutPostRedisplay();
      glutSetWindow(currentWindow);
}

/// Display Viewport 1
void ViewPort2::Display()
{

    glutSetWindow(view2);
    glClear(GL_COLOR_BUFFER_BIT);
    DrawScene();
    glFlush();
    glutSwapBuffers();


}

void ViewPort2::Keyboard(unsigned char fKey, int fX, int fY)
{
    switch (fKey)
    {
    case ' ':   /// Toggle slicing
        VP2::_slicingMode = !VP2::_slicingMode;
        SetDisplayListDistance(VP2::_sliceIndex);
        break;
    case '[':   /// +ve slicing
        VP2::_sliceIndex -= 1;
        SetDisplayListDistance(VP2::_sliceIndex);
        break;
    case ']':   /// -ve slicing
        VP2::_sliceIndex += 1;
        SetDisplayListDistance(VP2::_sliceIndex);
        break;

    case '1':   /// Front
        VP2::_xRot = 0;
        VP2::_yRot = 0;
        VP2::_zRot = 0;
        break;
    case '2':   /// Back
        VP2::_xRot = 180;
        VP2::_yRot = 0;
        VP2::_zRot = 0;
        break;
    case '3':   /// Top
        VP2::_xRot = -180;
        VP2::_yRot = 0;
        VP2::_zRot = 0;
    case '4':   /// Bottom
        VP2::_xRot = -90;
        VP2::_yRot = 0;
        VP2::_zRot = 0;
        break;
    case '5':   /// Left side
        VP2::_xRot = 0;
        VP2::_yRot = -90;
        VP2::_zRot = 0;
        break;
    case '6':   /// Right side
        VP2::_xRot = 0;
        VP2::_yRot = 90;
        VP2::_zRot = 0;
        break;

    case 'a':   /// X +ve rotation
        VP2::_xRot += 10.0;
        VP2::_xRot = (VP2::_xRot >= 360.0) ? 0.0 : VP2::_xRot;
        break;
    case 'A':   /// X -ve rotation
        VP2::_xRot -= 10.0;
        VP2::_xRot = (VP2::_xRot < 0.0) ? 360.0 : VP2::_xRot;
        break;
    case 's':   /// Y +ve rotation
        VP2::_yRot += 10.0;
        VP2::_yRot = (VP2::_yRot < 0.0) ? 360.0 : VP2::_yRot;
        break;
    case 'S':   /// Y -ve rotation
        VP2::_yRot -= 10.0;
        VP2::_yRot = (VP2::_yRot < 0.0) ? 360.0 : VP2::_yRot;
        break;
    case 'd':   /// Z +ve rotation
        VP2::_zRot += 10.0;
        VP2::_zRot = (VP2::_zRot >= 360.0) ? 0.0 : VP2::_zRot;
        break;
    case 'D':   /// Z -ve rotation
        VP2::_zRot -= 10.0;
        VP2::_zRot = (VP2::_zRot < 0.0) ? 360.0 : VP2::_zRot;
        break;

    case 'z':   /// +ve scaling
        VP2::_scale *= 0.9;
        break;
    case 'Z':   /// -ve scaling
        VP2::_scale *= 1.1;
        break;

    case 'q':   /// R transfer function
        _rValueTF -= 0.05;
        ViewPorts::UpdateAll();
        break;
    case 'Q':   /// R transfer function
        _rValueTF += 0.05;
        ViewPorts::UpdateAll();
        break;
    case 'w':   /// G transfer function
        _gValueTF -= 0.05;
        ViewPorts::UpdateAll();
        break;
    case 'W':   /// G transfer function
        _gValueTF += 0.05;
        ViewPorts::UpdateAll();
        break;
    case 'e':   /// B transfer function
        _bValueTF -= 0.05;
        ViewPorts::UpdateAll();
        break;
    case 'E':   /// B transfer function
        _bValueTF += 0.05;
        ViewPorts::UpdateAll();
        break;
    case 'r':   /// A transfer function
        _aValueTF -= 0.05;
        ViewPorts::UpdateAll();
        break;
    case 'R':   /// A transfer function
        _aValueTF += 0.05;
        ViewPorts::UpdateAll();
        break;

    case 't':   /// Threshold
        _desityThresholdTF -= 1;
        ViewPorts::UpdateAll();
        break;
    case 'T':   /// Threshold
        _desityThresholdTF += 1;
        ViewPorts::UpdateAll();
        break;
    case 27:
        delete [] _RGBAVolumeData;
        exit(0);
        break;
    }

    // Redisplay = glutPostRedisplay()
    DrawScene();
}

void ViewPort2::UpdateScene()
{
    //Volume VoluUpdateVolume();
    ViewPort2::Display();
}

void ViewPort2::Reshape(int volumeWidth, int volumeHeight)
{
   glViewport(0, 0, (GLsizei) volumeWidth, (GLsizei) volumeHeight);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   presSize = 1.0;
   GLfloat aspect = (GLfloat) volumeHeight/(GLfloat) volumeWidth;
   glOrtho(-presSize, presSize, -presSize * aspect, presSize * aspect, -presSize, presSize);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

#endif // VIEWPORT2_HPP
