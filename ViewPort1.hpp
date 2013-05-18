#ifndef VIEW_PORT_1_HPP
#define VIEW_PORT_1_HPP

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "GL/glut.h"

#include "Shared.h"
#include "GL_Utils.h"
#include "MainScene.hpp"

namespace ViewPort1
{
void Display();
void Keyboard(unsigned char fKey, int fX, int fY);
void RegisterCallBacks();
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
    switch(fKey)
    {
    case 'Q':
        std::cout << "Hellooo";
        exit(0);
        break;
    default:
        break;
    }


    glutPostRedisplay();
}

//void OpenGL::MouseGL(int fButton, int fState, int fX, int fY)
//{
//    if(fState == GLUT_DOWN)
//    {
//        if(fButton == GLUT_LEFT_BUTTON)
//        {
//            INFO("1");
//        }
//        else if(fButton == GLUT_MIDDLE_BUTTON)
//        {
//            INFO("12");
//        }
//        else if(fButton == GLUT_RIGHT_BUTTON)
//        {
//            printf("13");
//        }
//    }
//    else
//    {
//        //alternate code
//    }

//    /* @ Reslice & redisplay */
//    glutPostRedisplay();
//}

//void OpenGL::MouseMotionGL(int iX, int iY)
//{
//    // Dummy
//    if (iX | iY) {}

//    glutPostRedisplay();
//}

//void OpenGL::RegisterGLCallBacks()
//{
//    /* Registering OpenGL context callbacks*/
//    INFO("Registerng OpenGL context callbacks");

//    glutDisplayFunc(DisplayGL);
//    glutKeyboardFunc(KeyboardGL);
//    glutReshapeFunc(ReshapeGL);
//    glutIdleFunc(IdleGL);
//    glutMouseFunc(MouseGL);
//    glutMotionFunc(MouseMotionGL);

//    INFO("Registerng OpenGL context callbacks DONE");
//}

#endif // VIEW_PORT_1_HPP
