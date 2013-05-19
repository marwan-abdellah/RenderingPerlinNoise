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

#ifndef DISPLAYLIST_HPP
#define DISPLAYLIST_HPP

#include <iostream>
#include <math.h>
#include <GL/glut.h>

#include "Utils.h"
#include "VolumeSharedData.h"

void SetDisplayList(void)
{
    // Distance
    float dist;
    int i;

    // Number of half slice
    int nHSlices = 1.3 * (sqrt(float(_volumeWidth * _volumeWidth +
                                     _volumeHeight * _volumeHeight +
                                     _volumeDepth * _volumeDepth)))/4.0;

    // Number of slices (including the central one)
    int nSlices = 2 * nHSlices + 1;

    // Number of elements (verticies)
    int nElements = nSlices*4;

    // Total number of points
    GLfloat *vPoints    = new GLfloat [3 * nElements];
    GLfloat *ptr        = vPoints;
    float dDist         = (sqrt(3.0) / nSlices);
    float halfDistance  = sliceArmDistance;


    for (i = -nHSlices; i <= nHSlices; i++)
    {
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
    int nHSlices = 1.3 * (sqrt(float(_volumeWidth * _volumeWidth +
                                     _volumeHeight * _volumeHeight +
                                     _volumeDepth * _volumeDepth)))/4.0;

    // Number of slices (including the central one)
    int nSlices      = 2 * nHSlices + 1;

    int nElements;
    // Number of elements (verticies)
    if (VP1::_slicingMode)
        nElements   = 4;
    else
        nElements   = 4 * nSlices;

    // Total number of points
    GLfloat *vPoints    = new GLfloat [3 * nElements];
    GLfloat *ptr        = vPoints;
    float dDist         = (sqrt(3.0) / nSlices);
    float halfDistance  = sliceArmDistance;

    if (VP1::_slicingMode)
    {
        {
            dist     = distance * dDist;

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
    }
    else
    {
        for (i = -nHSlices; i <= nHSlices; i++)
        {
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
    }


    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vPoints);
    VP1::listName = glGenLists(1);
    glNewList(VP1::listName, GL_COMPILE);
    glDrawArrays(GL_QUADS, 0, nElements);
    glEndList();
    delete [] vPoints;
}

#endif // DISPLAYLIST_HPP
