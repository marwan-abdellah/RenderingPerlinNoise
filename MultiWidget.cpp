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

#include "GL/glut.h"
#include <iostream>
#include <string.h>
#include <stdio.h>

#include "Shared.h"
#include "MainScene.hpp"

#include "ViewPort1.hpp"
#include "ViewPort2.hpp"
#include "ViewPort3.hpp"
#include "ViewPort4.hpp"

#include "Utils.h"
#include "VolumeSharedData.h"
#include "ReadVolume.hpp"
#include "DisplayList.hpp"
#include "Textures.h"
#include "CreateSphere.hpp"

#include "CreateNoiseVolume.hpp"

using namespace std;

/// Prototypes
void mainReshape(int width,  int height);
void mainDisplay(void);

/// Main
int main(int argc, char** argv)
{
    // Read Volume
    // Volume::ReadVolume("/home/abdellah/Software/Datasets/CTData/CTData");
    // _lumVolumeData = CreateBigSphere(256, 256, 256);


   _volumeWidth = 256;
   _volumeHeight = 256;
   _volumeDepth = 256;
   _volNumVoxels = _volumeWidth * _volumeHeight * _volumeDepth;

   INFO("Creating noise");
    _lumVolumeData = CreateNoiseVolume(_volumeWidth, _volumeHeight, _volumeDepth);
    INFO("Boise creation done ");

    // Allocating the RGBA image
    _RGBAVolumeData = (GLubyte*) malloc (sizeof(GLubyte) * _volNumVoxels * 4);

     Volume::UpdateVolume();

    // GLUT initialization
    glutInit(&argc, argv);

    // getting the screen resolution to adjust the rest of the application accordinglly
    screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    cout << "SCREEN_WIDTH : " << screenWidth << endl;
    cout << "SCREEN_HEIGHT : " << screenHeight << endl;

    // GLUT mode settings, RGB, depth buffer, double buffering
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    // Center the window in the middle of the screen
    int windowPosX = (screenWidth / 2) - (screenWidth / 4);
    int windowPosY = (screenHeight / 2) - (screenHeight / 4);

    // Initial window position
    glutInitWindowPosition(windowPosX, windowPosY);

    // Make square widgets
    if (screenWidth != screenHeight)
    {
        if (screenWidth < screenHeight)
            screenHeight = screenWidth;
        else
            screenWidth = screenHeight;
    }

    // Window size inclusing the gaps
    glutInitWindowSize(screenWidth, screenHeight);

    // Main window creation
    window = glutCreateWindow("MultiViewPort Window (multi Widgets)");

    // Main window callback function
    glutReshapeFunc(mainReshape);
    glutDisplayFunc(mainDisplay);

    // Calculating the viewports dimensions
    const float viewportWidth = screenWidth / 4;
    const float viewportHeight = screenHeight / 4;

    subWinWidth = viewportWidth;
    subWinHeight = viewportHeight;

    // View 1
    view1 = glutCreateSubWindow(window, GAP, GAP,
                                viewportWidth, viewportHeight);
    ViewPort1::RegisterCallBacks();
    Texture::Init();


    // View 2
    view2 = glutCreateSubWindow(window, GAP + viewportWidth + GAP,
                                GAP, viewportWidth, viewportHeight);
    ViewPort2::RegisterCallBacks();
    Texture::Init();

    // View 3
    view3 = glutCreateSubWindow(window, GAP+viewportWidth+GAP,
                                GAP + viewportHeight + GAP,
                                viewportWidth, viewportHeight);
    ViewPort3::RegisterCallBacks();
    Texture::Init();

     // View 4
    view4 = glutCreateSubWindow(window, GAP + viewportWidth + GAP,
                                GAP + viewportHeight + GAP,
                                viewportWidth, viewportHeight);
    ViewPort4::RegisterCallBacks();
    Texture::Init();

    /// MAIN LOOP ! Should be multi-threaded
    glutMainLoop();

    return 0;
}

/// Main widget display
void mainDisplay(void)
{
    // Background Color
    glClearColor(0.8, 0.8, 0.8, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Font color and style
    glColor3ub(0, 0, 0);
    SetFontParams("helvetica", 12);

    // Window 1 name
    string str = "Window 1";
    DrawString(GAP, GAP-5, str.c_str(), str.length());

    // Window 2 name
    str = "Window 2";
    DrawString(GAP + subWinWidth+GAP, GAP - 5, str.c_str(), str.length());

    // Window 3 name
    str = "Window 3";
    DrawString(GAP, GAP + subWinHeight + GAP - 5, str.c_str(), str.length());

    // Window 4 name
    str = "Window 4";
    DrawString(GAP + subWinWidth + GAP, GAP + subWinHeight + GAP - 5, str.c_str(), str.length());

    /// BUFFER SWAPPING ! Double buffering
    glutSwapBuffers();
}

/// Main widget reshaping
void mainReshape(int width,  int height)
{
    // Main view setting
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, width, height, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    subWinWidth = (width - GAP * 3) / 2.0;
    subWinHeight = (height - GAP * 3) / 2.0;

    //view1 Display
    glutSetWindow(view1);
    glutPositionWindow(GAP, GAP);
    glutReshapeWindow(subWinWidth, subWinHeight);

    //view2 Display
    glutSetWindow(view2);
    glutPositionWindow(GAP + subWinWidth + GAP, GAP);
    glutReshapeWindow(subWinWidth, subWinHeight);

    //view3 Display
    glutSetWindow(view3);
    glutPositionWindow(GAP, GAP + subWinHeight + GAP);
    glutReshapeWindow(subWinWidth, subWinHeight);


    //view4 Display
    glutSetWindow(view4);
    glutPositionWindow(GAP + subWinWidth + GAP, GAP + subWinHeight + GAP);
    glutReshapeWindow(subWinWidth, subWinHeight);
    // glutReshapeWindow(subWinWidth + GAP + subWinWidth, subWinHeight);
}
