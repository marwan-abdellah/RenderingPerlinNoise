#ifndef VIEW_PORT_1_HPP
#define VIEW_PORT_1_HPP

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

namespace ViewPort1
{
void Display();
void Keyboard(unsigned char fKey, int fX, int fY);
void RegisterCallBacks();
void UpdateScene();
}

void ViewPort1::RegisterCallBacks()
{
    glutDisplayFunc(ViewPort1::Display);
    glutKeyboardFunc(ViewPort1::Keyboard);
}

/// Display Viewport 1
void ViewPort1::Display()
{
    // Reset viewport
    ResetViewport();

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPushMatrix();
    gluLookAt(0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    DrawScene();
    glPopMatrix();
    glutSwapBuffers();
}

void ViewPort1::Keyboard(unsigned char fKey, int fX, int fY)
{
    switch (fKey)
    {
        case 'q':
            _rValueTF -= 0.05;
//            INFO("R : " + ITS(_rValueTF));
            std::cout << "Hwllo";
            ViewPort1::UpdateScene();
            break;
        case 'Q':
            _rValueTF += 0.05;
//            INFO("R : " + ITS(_rValueTF));
            ViewPort1::UpdateScene();
            break;
        case 'w':
            _gValueTF -= 0.05;
//            INFO("G : " + ITS(_gValueTF));
            ViewPort1::UpdateScene();
            break;
        case 'W':
            _gValueTF += 0.05;
//            INFO("G : " + ITS(_gValueTF));
            ViewPort1::UpdateScene();
            break;
        case 'e':
            _bValueTF -= 0.05;
//            INFO("B : " + ITS(_bValueTF));
            ViewPort1::UpdateScene();
            break;
        case 'E':
            _bValueTF += 0.05;
//            INFO("B : " + ITS(_bValueTF));
           ViewPort1::UpdateScene();
            break;
        case 'r':
            _aValueTF -= 0.05;
//            INFO("A : " + ITS(_aValueTF));
            ViewPort1::UpdateScene();
            break;
        case 'R':
            _aValueTF += 0.05;
//            INFO("A : " + ITS(_aValueTF));
            ViewPort1::UpdateScene();
            break;
        case 't':
            _desityThresholdTF -= 1;
//            INFO("A : " + ITS(_desityThresholdTF));
            ViewPort1::UpdateScene();
            break;
        case 'T':
            _desityThresholdTF += 1;
//            INFO("A : " + ITS(_desityThresholdTF));
            ViewPort1::UpdateScene();
            break;
        case 'a':
            xRotation += 10.0;
            xRotation = (xRotation >= 360.0) ? 0.0 : xRotation;
//            INFO("X-axis rotation : " + ITS(xRotation));
            break;
        case 'A':
            xRotation -= 10.0;
            xRotation = (xRotation < 0.0) ? 360.0 : xRotation;
//            INFO("X-axis rotation : " + ITS(xRotation));
            break;
        case 'halfDistance':
            yRotation += 10.0;
            yRotation = (yRotation >= 360.0) ? 0.0 : yRotation;
//            INFO("Y-axis rotation : " + ITS(yRotation));
            break;
        case 'S':
            yRotation -= 10.0;
            yRotation = (yRotation < 0.0) ? 360.0 : yRotation;
//            INFO("Y-axis rotation : " + ITS(yRotation));
            break;
        case 'd':
            zRotation += 10.0;
            zRotation = (zRotation >= 360.0) ? 0.0 : zRotation;
//            INFO("Z-axis rotation : " + ITS(zRotation));
            break;
        case 'D':
            zRotation -= 10.0;
            zRotation = (zRotation < 0.0) ? 360.0 : zRotation;
//            INFO("Z-axis rotation : " + ITS(zRotation));
            break;
        case 'z':
            scaleFactor *= 0.9;
//            INFO("ZoomFactor: " + ITS(scaleFactor));
            break;
        case 'Z':
            scaleFactor *= 1.1;
//            INFO("ZoomFactor: " + ITS(scaleFactor));
            break;
        case 'x':
            sliceArmDistance -= 0.05;
//            INFO("sliceArmDistance : " + ITS(sliceArmDistance));
            SetDisplayList();
            break;
        case 'X':
            sliceArmDistance += 0.05;
//            INFO("sliceArmDistance : " + ITS(sliceArmDistance));
            SetDisplayList();
            break;
        case 'c':
            numSlices -= 1;
//            INFO("numSlices : " + ITS(numSlices));
            SetDisplayList();
            break;
        case 'C':
            numSlices += 1;
//            INFO("numSlices : " + ITS(numSlices));
            SetDisplayList();
            break;
        case 'O':
            presSize += 0.05;
            Display();
            break;
        case 'o':
            presSize -= 0.05;
            Display();
            break;
        case ' ':
            rotateState = !rotateState;
            break;
        case 'h':
            //PrintHelp();
            break;
        case 27:
            delete [] _RGBAVolumeData;
            exit(0);
            break;
    }


    glutPostRedisplay();
}

void ViewPort1::UpdateScene()
{
    //Volume VoluUpdateVolume();
    ViewPort1::Display();
}

#endif // VIEW_PORT_1_HPP
