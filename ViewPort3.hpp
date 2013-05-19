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

#ifndef VIEWPORT3_HPP
#define VIEWPORT3_HPP

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

void clamp (vec3_t v)
{
    int i;

    for (i = 0; i < 3; i ++)
        if (v[i] > 360 || v[i] < -360)
            v[i] = 0.0f;
}

void ViewPort3::RegisterCallBacks()
{
    glutDisplayFunc(ViewPort3::Display);
    glutKeyboardFunc(ViewPort3::Keyboard);
    glutIdleFunc(ViewPort3::Idle);
    glutMotionFunc (ViewPort3::glutMotion);
    glutMouseFunc (ViewPort3::glutMouse);
}

void ViewPort3::Idle()
{
    int currentWindow = glutGetWindow();
    glutSetWindow(window);
    glutPostRedisplay();
    glutSetWindow(view3);
    glutPostRedisplay();
    glutSetWindow(currentWindow);
}

void ViewPort3::Display()
{
    glutSetWindow(view3);
    ResetViewport();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(10, 1.0, 3.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    DrawScene();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glutSwapBuffers();

    glutPostRedisplay();
}

void ViewPort3::glutMotion(int x, int y)
{
    if (VP3::mState == DOWN)
    {
        VP3::gRot[0] -= ((VP3::oldY - y) * 180.0f) / 100.0f;
        VP3::gRot[1] -= ((VP3::oldX - x) * 180.0f) / 100.0f;
        clamp (VP3::gRot);
        glutPostRedisplay ();
    }
    VP3::oldX = x;
    VP3::oldY = y;
}

void ViewPort3::glutMouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        switch(button)
        {
        case GLUT_LEFT_BUTTON:
        case GLUT_RIGHT_BUTTON:
            VP3::mState = DOWN;
            VP3::oldX = x;
            VP3::oldY = y;
            break;
        }
    }
    else if (state == GLUT_UP)
        VP3::mState = UP;
}

void ViewPort3::Keyboard(unsigned char fKey, int fX, int fY)
{
    switch (fKey)
    {
    case '1':   /// Front
        VP3::_xRot = 0;
        VP3::_yRot = 0;
        VP3::_zRot = 0;
        break;
    case '2':   /// Back
        VP3::_xRot = 180;
        VP3::_yRot = 0;
        VP3::_zRot = 0;
        break;
    case '3':   /// Top
        VP3::_xRot = -180;
        VP3::_yRot = 0;
        VP3::_zRot = 0;
    case '4':   /// Bottom
        VP3::_xRot = -90;
        VP3::_yRot = 0;
        VP3::_zRot = 0;
        break;
    case '5':   /// Left side
        VP3::_xRot = 0;
        VP3::_yRot = -90;
        VP3::_zRot = 0;
        break;
    case '6':   /// Right side
        VP3::_xRot = 0;
        VP3::_yRot = 90;
        VP3::_zRot = 0;
        break;

    case 'a':   /// X +ve rotation
        VP3::_xRot += 10.0;
        VP3::_xRot = (VP3::_xRot >= 360.0) ? 0.0 : VP3::_xRot;
        break;
    case 'A':   /// X -ve rotation
        VP3::_xRot -= 10.0;
        VP3::_xRot = (VP3::_xRot < 0.0) ? 360.0 : VP3::_xRot;
        break;
    case 's':   /// Y +ve rotation
        VP3::_yRot += 10.0;
        VP3::_yRot = (VP3::_yRot < 0.0) ? 360.0 : VP3::_yRot;
        break;
    case 'S':   /// Y -ve rotation
        VP3::_yRot -= 10.0;
        VP3::_yRot = (VP3::_yRot < 0.0) ? 360.0 : VP3::_yRot;
        break;
    case 'd':   /// Z +ve rotation
        VP3::_zRot += 10.0;
        VP3::_zRot = (VP3::_zRot >= 360.0) ? 0.0 : VP3::_zRot;
        break;
    case 'D':   /// Z -ve rotation
        VP3::_zRot -= 10.0;
        VP3::_zRot = (VP3::_zRot < 0.0) ? 360.0 : VP3::_zRot;
        break;

    case 'z':   /// +ve scaling
        VP3::_scale *= 0.9;
        break;
    case 'Z':   /// -ve scaling
        VP3::_scale *= 1.1;
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

void ViewPort3::UpdateScene()
{
    ViewPorts::UpdateAll();
    glutSetWindow(view3);
    glutPostRedisplay();
}

#endif // VIEWPORT3_HPP
