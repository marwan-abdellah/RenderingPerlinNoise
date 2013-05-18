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
#include "ReadVolume.hpp"

using namespace std;
namespace ViewPort1
{
void Display();
void Keyboard(unsigned char fKey, int fX, int fY);
void RegisterCallBacks();
void UpdateScene();
void Idle();
void Reshape(int volumeWidth, int volumeHeight);
}

void ViewPort1::RegisterCallBacks()
{
    glutDisplayFunc(ViewPort1::Display);
    glutKeyboardFunc(ViewPort1::Keyboard);
    glutIdleFunc(ViewPort1::Idle);
    glutReshapeFunc(ViewPort1::Reshape);
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

/// Display Viewport 1
void ViewPort1::Display()
{

    glutSetWindow(view1);

    // Reset viewport
    //ResetViewport();
    cout << "d1 \n";
    //    glClear(GL_COLOR_BUFFER_BIT);

    //    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //    glColor3f(1.0, 1.0, 1.0);
    //    glMatrixMode(GL_PROJECTION);
    //    glPushMatrix();
    //    glLoadIdentity();
    //    gluPerspective(30, 1.0, 3.0, 50.0);
    //    glMatrixMode(GL_MODELVIEW);
    //    glPushMatrix();
    //    gluLookAt(0, 0, -4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    //    DrawScene2();
    //    glPopMatrix();
    //    glMatrixMode(GL_PROJECTION);
    //    glPopMatrix();


    // Reset viewport
    //ResetViewport();
    glClear(GL_COLOR_BUFFER_BIT);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


    DrawScene2();
    glFlush();
    glutSwapBuffers();

}

void ViewPort1::Keyboard(unsigned char fKey, int fX, int fY)
{
    switch (fKey)
    {
    case ' ':   /// Toggle slicing
        VP1::_slicingMode = !VP1::_slicingMode;
        SetDisplayListDistance(VP1::_sliceIndex);
        ViewPort1::UpdateScene();
        break;
    case '[':   /// +ve slicing
        VP1::_sliceIndex -= 1;
        SetDisplayListDistance(VP1::_sliceIndex);
        ViewPort1::UpdateScene();
        break;
    case ']':   /// -ve slicing
        VP1::_sliceIndex += 1;
        SetDisplayListDistance(VP1::_sliceIndex);
        ViewPort1::UpdateScene();
        break;

    case '1':   /// Front
        VP1::_xRot = 0;
        VP1::_yRot = 0;
        VP1::_zRot = 0;
        ViewPort1::UpdateScene();
        break;
    case '2':   /// Back
        VP1::_xRot = 180;
        VP1::_yRot = 0;
        VP1::_zRot = 0;
        ViewPort1::UpdateScene();
        break;
    case '3':   /// Top
        VP1::_xRot = -180;
        VP1::_yRot = 0;
        VP1::_zRot = 0;
        ViewPort1::UpdateScene();
    case '4':   /// Bottom
        VP1::_xRot = -90;
        VP1::_yRot = 0;
        VP1::_zRot = 0;
        ViewPort1::UpdateScene();
        break;
    case '5':   /// Left side
        VP1::_xRot = 0;
        VP1::_yRot = -90;
        VP1::_zRot = 0;
        ViewPort1::UpdateScene();
        break;
    case '6':   /// Right side
        VP1::_xRot = 0;
        VP1::_yRot = 90;
        VP1::_zRot = 0;
        ViewPort1::UpdateScene();
        break;

    case 'a':   /// X +ve rotation
        VP1::_xRot += 10.0;
        VP1::_xRot = (VP1::_xRot >= 360.0) ? 0.0 : VP1::_xRot;
        ViewPort1::UpdateScene();
        break;
    case 'A':   /// X -ve rotation
        VP1::_xRot -= 10.0;
        VP1::_xRot = (VP1::_xRot < 0.0) ? 360.0 : VP1::_xRot;
        ViewPort1::UpdateScene();
        break;
    case 's':   /// Y +ve rotation
        VP1::_yRot += 10.0;
        VP1::_yRot = (VP1::_yRot < 0.0) ? 360.0 : VP1::_yRot;
        ViewPort1::UpdateScene();
        break;
    case 'S':   /// Y -ve rotation
        VP1::_yRot -= 10.0;
        VP1::_yRot = (VP1::_yRot < 0.0) ? 360.0 : VP1::_yRot;
        ViewPort1::UpdateScene();
        break;
    case 'd':   /// Z +ve rotation
        VP1::_zRot += 10.0;
        VP1::_zRot = (VP1::_zRot >= 360.0) ? 0.0 : VP1::_zRot;
        ViewPort1::UpdateScene();
        break;
    case 'D':   /// Z -ve rotation
        VP1::_zRot -= 10.0;
        VP1::_zRot = (VP1::_zRot < 0.0) ? 360.0 : VP1::_zRot;
        ViewPort1::UpdateScene();
        break;












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

    case 'z':
        VP1::_scale *= 0.9;
        //            INFO("ZoomFactor: " + ITS(scaleFactor));
        break;
    case 'Z':
        VP1::_scale *= 1.1;
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

    case 'O':
        presSize += 0.05;
        Display();
        break;
    case 'o':
        presSize -= 0.05;
        Display();
        break;
    case '*':
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
    Volume::UpdateVolume();
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

#endif // VIEW_PORT_1_HPP
