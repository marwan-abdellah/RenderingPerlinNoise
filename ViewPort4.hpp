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

#ifndef VIEWPORT4_HPP
#define VIEWPORT4_HPP

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
#include "ViewPorts.h"

using namespace std;

void ViewPort4::RegisterCallBacks()
{
    glutDisplayFunc(ViewPort4::Display);
    glutKeyboardFunc(ViewPort4::Keyboard);
    glutIdleFunc(ViewPort4::Idle);
}

void ViewPort4::Idle()
{

    int currentWindow = glutGetWindow();
      glutSetWindow(window);
      glutPostRedisplay();
      glutSetWindow(view4);
      glutPostRedisplay();
      glutSetWindow(currentWindow);
}

void ViewPort4::Display()
{
    glutSetWindow(view4);
    DrawScene();
}

void ViewPort4::Keyboard(unsigned char fKey, int fX, int fY)
{
    switch (fKey)
    {
    case ' ':   /// Toggle slicing
        VP4::_slicingMode = !VP4::_slicingMode;
        SetDisplayListDistance(VP4::_sliceIndex);
        break;
    case '[':   /// +ve slicing
        VP4::_sliceIndex -= 1;
        SetDisplayListDistance(VP4::_sliceIndex);
        break;
    case ']':   /// -ve slicing
        VP4::_sliceIndex += 1;
        SetDisplayListDistance(VP4::_sliceIndex);
        break;

    case '1':   /// Front
        VP4::_xRot = 0;
        VP4::_yRot = 0;
        VP4::_zRot = 0;
        break;
    case '2':   /// Back
        VP4::_xRot = 180;
        VP4::_yRot = 0;
        VP4::_zRot = 0;
        break;
    case '3':   /// Top
        VP4::_xRot = -180;
        VP4::_yRot = 0;
        VP4::_zRot = 0;
    case '4':   /// Bottom
        VP4::_xRot = -90;
        VP4::_yRot = 0;
        VP4::_zRot = 0;
        break;
    case '5':   /// Left side
        VP4::_xRot = 0;
        VP4::_yRot = -90;
        VP4::_zRot = 0;
        break;
    case '6':   /// Right side
        VP4::_xRot = 0;
        VP4::_yRot = 90;
        VP4::_zRot = 0;
        break;

    case 'a':   /// X +ve rotation
        VP4::_xRot += 10.0;
        VP4::_xRot = (VP4::_xRot >= 360.0) ? 0.0 : VP4::_xRot;
        break;
    case 'A':   /// X -ve rotation
        VP4::_xRot -= 10.0;
        VP4::_xRot = (VP4::_xRot < 0.0) ? 360.0 : VP4::_xRot;
        break;
    case 's':   /// Y +ve rotation
        VP4::_yRot += 10.0;
        VP4::_yRot = (VP4::_yRot < 0.0) ? 360.0 : VP4::_yRot;
        break;
    case 'S':   /// Y -ve rotation
        VP4::_yRot -= 10.0;
        VP4::_yRot = (VP4::_yRot < 0.0) ? 360.0 : VP4::_yRot;
        break;
    case 'd':   /// Z +ve rotation
        VP4::_zRot += 10.0;
        VP4::_zRot = (VP4::_zRot >= 360.0) ? 0.0 : VP4::_zRot;
        break;
    case 'D':   /// Z -ve rotation
        VP4::_zRot -= 10.0;
        VP4::_zRot = (VP4::_zRot < 0.0) ? 360.0 : VP4::_zRot;
        break;

    case 'z':   /// +ve scaling
        VP4::_scale *= 0.9;
        break;
    case 'Z':   /// -ve scaling
        VP4::_scale *= 1.1;
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

void ViewPort4::UpdateScene()
{
    glutSetWindow(view3);
    glutPostRedisplay();
}

void ViewPort4::Reshape(int volumeWidth, int volumeHeight)
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

#endif // VIEWPORT4_HPP
