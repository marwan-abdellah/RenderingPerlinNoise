#ifndef DISPLAYLIST_HPP
#define DISPLAYLIST_HPP

#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "Utils.h"
#include "VolumeSharedData.h"

void SetDisplayList(void)
{
    // Distance
    float dist;
    int i;

    // Number of half slice
    int nHSlices     = 1.3 * numSlices / 4;
    // int nHSlices = 1.3 * (sqrt(float(iWidth*iWidth + iHeight*iHeight + iDepth*iDepth)))/4.0;

    // Number of slices (including the central one)
    int nSlices      = 2 * nHSlices + 1;

    // Number of lements (verticies)
    int nElements    = nSlices*4;

    // Total number of points
    GLfloat *vPoints    = new GLfloat [3 * nElements];
    GLfloat *ptr        = vPoints;
    float dDist         = (sqrt(3.0) / nSlices);
    float halfDistance  = sliceArmDistance;


    for (i = -nHSlices; i <= nHSlices; i++)
    {
        // Sampling
        dist     = i * dDist;

        *(ptr++) = -halfDistance;
        *(ptr++) = -halfDistance;
        *(ptr++) =  dist;

        *(ptr++) =  halfDistance;
        *(ptr++) = -halfDistance;
        *(ptr++) =  dist;

        *(ptr++) =  halfDistance;
        *(ptr++) =  halfDistance;
        *(ptr++) =  dist;

        *(ptr++) = -halfDistance;
        *(ptr++) =  halfDistance;
        *(ptr++) =  dist;
    }

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vPoints);
    listName = glGenLists(1);
    glNewList(listName, GL_COMPILE);
    glDrawArrays(GL_QUADS, 0, nElements);
    glEndList();
    delete [] vPoints;
}

void SetDisplayListDistance(float distance)
{
    // Distance
    float dist;
    int i;

    // Number of half slice
    // int nHSlices     = 1.3 * numSlices /4;
    int nHSlices = 1.3 * (sqrt(float(_volumeWidth * _volumeWidth+
                                     _volumeHeight * _volumeHeight+ _volumeDepth * _volumeDepth)))/4.0;

    // Number of slices (including the central one)
    int nSlices      = 2 * nHSlices + 1;

    // Number of lements (verticies)
    int nElements    = 4;

    // Total number of points
    GLfloat *vPoints    = new GLfloat [3 * nElements];
    GLfloat *ptr        = vPoints;
    float dDist         = (sqrt(3.0) / nSlices);
    float halfDistance  = sliceArmDistance;


//for (i = -nHSlices; i <= nHSlices; i++)
    i = (int) distance;
  //  std::cout << "nHSlices " << nHSlices <<std::endl;
    //std::cout << "Distance " << i <<std::endl;
    {
        // Sampling
        dist     = i * dDist;

        *(ptr++) = -halfDistance;
        *(ptr++) = -halfDistance;
        *(ptr++) =  dist;

        *(ptr++) =  halfDistance;
        *(ptr++) = -halfDistance;
        *(ptr++) =  dist;

        *(ptr++) =  halfDistance;
        *(ptr++) =  halfDistance;
        *(ptr++) =  dist;

        *(ptr++) = -halfDistance;
        *(ptr++) =  halfDistance;
        *(ptr++) =  dist;
    }
    // std::cout << "dist " << dist <<std::endl;

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vPoints);
    VP1::listName = glGenLists(1);
    glNewList(VP1::listName, GL_COMPILE);
    glDrawArrays(GL_QUADS, 0, nElements);
    glEndList();
    delete [] vPoints;
}

#endif // DISPLAYLIST_HPP
