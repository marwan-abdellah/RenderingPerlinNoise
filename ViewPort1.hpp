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

#ifndef VIEWPORT1_HPP
#define VIEWPORT1_HPP

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
#include "CreateNoiseVolume.hpp"

using namespace std;
namespace ViewPort1
{
void Display();
void Keyboard(unsigned char fKey, int fX, int fY);
void RegisterCallBacks();
void UpdateScene();
void Idle();
void Reshape(int volumeWidth, int volumeHeight);
void glutMouse(int button, int state, int x, int y);
}

void ViewPort1::RegisterCallBacks()
{
    glutDisplayFunc(ViewPort1::Display);
    glutKeyboardFunc(ViewPort1::Keyboard);
    glutIdleFunc(ViewPort1::Idle);
    glutReshapeFunc(ViewPort1::Reshape);
    glutMouseFunc(ViewPort1::glutMouse);
}

void ViewPort1::Idle()
{

    int currentWindow = glutGetWindow();
    glutSetWindow(window);
    glutPostRedisplay();
    glutSetWindow(view1);
    glutPostRedisplay();
    glutSetWindow(currentWindow);
}

void ViewPort1::Display()
{

    glutSetWindow(view1);
    glClear(GL_COLOR_BUFFER_BIT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    DrawScene();
    glFlush();
    glutSwapBuffers();

}

void ViewPort1::glutMouse(int button, int state, int x, int y)
{
    if (state == GLUT_UP )
    {
        if ( button == GLUT_WHEEL_UP  && VP1::_slicingMode)
        {
            VP1::_sliceIndex += 1;
            SetDisplayListDistance(VP1::_sliceIndex);
        }
        else if( button == GLUT_WHEEL_DOWN && VP1::_slicingMode)
        {
            VP1::_sliceIndex -= 1;
            SetDisplayListDistance(VP1::_sliceIndex);
        }
    }

    DrawScene();
}

void ViewPort1::Keyboard(unsigned char fKey, int fX, int fY)
{
    switch (fKey)
    {
    case ' ':   /// Toggle slicing
        VP1::_slicingMode = !VP1::_slicingMode;
        SetDisplayListDistance(VP1::_sliceIndex);
        break;
    case '[':   /// +ve slicing
        VP1::_sliceIndex -= 1;
        SetDisplayListDistance(VP1::_sliceIndex);
        break;
    case ']':   /// -ve slicing
        VP1::_sliceIndex += 1;
        SetDisplayListDistance(VP1::_sliceIndex);
        break;

    case '1':   /// Front
        VP1::_xRot = 0;
        VP1::_yRot = 0;
        VP1::_zRot = 0;
        break;
    case '2':   /// Back
        VP1::_xRot = 180;
        VP1::_yRot = 0;
        VP1::_zRot = 0;
        break;
    case '3':   /// Top
        VP1::_xRot = -180;
        VP1::_yRot = 0;
        VP1::_zRot = 0;
    case '4':   /// Bottom
        VP1::_xRot = -90;
        VP1::_yRot = 0;
        VP1::_zRot = 0;
        break;
    case '5':   /// Left side
        VP1::_xRot = 0;
        VP1::_yRot = -90;
        VP1::_zRot = 0;
        break;
    case '6':   /// Right side
        VP1::_xRot = 0;
        VP1::_yRot = 90;
        VP1::_zRot = 0;
        break;

    case 'a':   /// X +ve rotation
        VP1::_xRot += 10.0;
        VP1::_xRot = (VP1::_xRot >= 360.0) ? 0.0 : VP1::_xRot;
        break;
    case 'A':   /// X -ve rotation
        VP1::_xRot -= 10.0;
        VP1::_xRot = (VP1::_xRot < 0.0) ? 360.0 : VP1::_xRot;
        break;
    case 's':   /// Y +ve rotation
        VP1::_yRot += 10.0;
        VP1::_yRot = (VP1::_yRot < 0.0) ? 360.0 : VP1::_yRot;
        break;
    case 'S':   /// Y -ve rotation
        VP1::_yRot -= 10.0;
        VP1::_yRot = (VP1::_yRot < 0.0) ? 360.0 : VP1::_yRot;
        break;
    case 'd':   /// Z +ve rotation
        VP1::_zRot += 10.0;
        VP1::_zRot = (VP1::_zRot >= 360.0) ? 0.0 : VP1::_zRot;
        break;
    case 'D':   /// Z -ve rotation
        VP1::_zRot -= 10.0;
        VP1::_zRot = (VP1::_zRot < 0.0) ? 360.0 : VP1::_zRot;
        break;

    case 'z':   /// +ve scaling
        VP1::_scale *= 0.9;
        break;
    case 'Z':   /// -ve scaling
        VP1::_scale *= 1.1;
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

    case 'v':   /// Noise
        _octaves -= 1;
        std::cout << "Octave " << _octaves << std::endl;
        UpdateNoise();
        Volume::UpdateVolume() ;
        ViewPorts::UpdateAll();
        break;
    case 'V':   /// Noise
        _octaves += 1;
        std::cout << "Octave " << _octaves << std::endl;
        UpdateNoise();
        Volume::UpdateVolume() ;
        ViewPorts::UpdateAll();
        break;

    case 'b':   /// Noise
        _persistence -= 1;
        std::cout << "Persistance " << _persistence << std::endl;
        UpdateNoise();
        Volume::UpdateVolume() ;
        ViewPorts::UpdateAll();
        break;
    case 'B':   /// Noise
        _persistence += 1;
        UpdateNoise();
        Volume::UpdateVolume() ;
        ViewPorts::UpdateAll();
        std::cout << "Persistance " << _persistence << std::endl;
        break;

    case 'n':   /// Noise
        _scale -= 0.05;
        std::cout << "Scale " << _scale << std::endl;
        UpdateNoise();
        Volume::UpdateVolume() ;
        ViewPorts::UpdateAll();
        break;
    case 'N':   /// Noise
        _scale += 0.05;
        std::cout << "Scale " << _scale << std::endl;
        UpdateNoise();
        Volume::UpdateVolume() ;
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

void ViewPort1::UpdateScene()
{
    ViewPorts::UpdateAll();
    ViewPort1::Display();
}

void ViewPort1::Reshape(int volumeWidth, int volumeHeight)
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

#endif // VIEWPORT1_HPP
