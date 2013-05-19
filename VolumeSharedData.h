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

#ifndef VOLUMESHAREDDATA_H
#define VOLUMESHAREDDATA_H

#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

/// Axis rotation
#define X_AXIS                  0
#define Y_AXIS                  1
#define Z_AXIS                  2

/// Mouse buttons
enum { UP = 1, DOWN };

/// Vector
typedef float vec3_t[3];

/// Volume dimensions
int _volumeWidth;
int _volumeHeight;
int _volumeDepth;
int _volNumVoxels;

/// Volume data
GLubyte* _lumVolumeData;
GLubyte* _RGBAVolumeData;

/// Transfer function parameters
float _rValueTF = 1.0;   /// R
float _gValueTF = 1.0;   /// G
float _bValueTF = 1.0;   /// B
float _aValueTF = 1.0;   /// A

/// Density threshold value
int _desityThresholdTF = 60;

/// Bounding box
int _setBoundingBox = 0;

/// Texture ID
GLuint _volumeTexID;

/// Display list
GLuint listName;

/// Slice XY half distance
float sliceArmDistance = 0.5;

/// Orthographic projection parameter
GLfloat presSize = 1.0;

/// Viewport 1 globals
namespace VP1
{
    float _scale = 2.0f;
    float _xRot = 0.0f;
    float _yRot = 0.0f;
    float _zRot = 0.0;
    float _rValueTF = 1.0;
    float _gValueTF = 1.0;
    float _bValueTF = 1.0;
    float _aValueTF = 1.0;
    bool _slicingMode = true;
    int _sliceIndex = 0;
    GLuint listName;
    int _desityThresholdTF = 0;
}

/// Viewport 2 globals
namespace VP2
{
    float _scale = 2.0f;
    float _xRot = 0.0f;
    float _yRot = 0.0f;
    float _zRot = 0.0;
    float _rValueTF = 1.0;
    float _gValueTF = 1.0;
    float _bValueTF = 1.0;
    float _aValueTF = 1.0;
    bool _slicingMode = true;
    int _sliceIndex = 0;
    GLuint listName;
    int _desityThresholdTF = 0;
}

/// Viewport 3 globals
namespace VP3
{
    float _scale = 1.0f;
    float _xRot = 45.0f;
    float _yRot = 0.0f;
    float _zRot = 0.0;
    float _rValueTF = 1.0;
    float _gValueTF = 1.0;
    float _bValueTF = 1.0;
    float _aValueTF = 1.0;
    int _desityThresholdTF = 0;

    // Old position
    int oldX = -13;
    int oldY = -13;

    // Mouse state
    int mState = UP;

    // Current axis
    int axisRot = X_AXIS;

    // Amount to rotate about axis
    float rotate = 0.0f;

    // Rotation axis
    vec3_t axis = {1.0, 0.0, 0.0};

    // Global rotation
    vec3_t gRot = {45,0,45};
}

/// Viewport 4 globals
namespace VP4
{
    float _scale = 2.0f;
    float _xRot = 0.0f;
    float _yRot = 0.0f;
    float _zRot = 0.0;
    float _rValueTF = 1.0;
    float _gValueTF = 1.0;
    float _bValueTF = 1.0;
    float _aValueTF = 1.0;
    bool _slicingMode = true;
    int _sliceIndex = 0;
    GLuint listName;
    int _desityThresholdTF = 0;
}

#endif // VOLUMESHAREDDATA_H
