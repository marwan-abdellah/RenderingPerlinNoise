#ifndef VOLUMESHAREDDATA_H
#define VOLUMESHAREDDATA_H

#define X_AXIS                  0
#define Y_AXIS                  1
#define Z_AXIS                  2

/* enumerations for the mouse buttons */
enum {
    UP = 1,
    DOWN,
};

/* vector */
typedef float vec3_t[3];

#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

int _volumeWidth;
int _volumeHeight;
int _volumeDepth;
int _volNumVoxels;

GLubyte* _lumVolumeData;
GLubyte* _RGBAVolumeData;

// Transfer function parameters
float _rValueTF = 1.0;   // R
float _gValueTF = 1.0;   // G
float _bValueTF = 1.0;   // B
float _aValueTF = 1.0;   // A

// Density threshold value
int _desityThresholdTF = 60;

int _setBoundingBox = 0;

// Texture ID
GLuint volumeTexID;

// Display list
GLuint listName;

float xRotation         = 0.0;
float yRotation         = 0.0;
float zRotation         = 0.0;

bool rotateState = 0;

// Slice XY half distance
float sliceArmDistance = 0.5;

// Total number of slices
int numSlices = 256;



// Orthographic projection parameter
GLfloat presSize = 1.0;


float scaleFactor       = 0.5;
float _scaleW1  = 0.5;
float _scaleW2  = 0.5;
float _scaleW3  = 0.5;
float _scaleW4  = 0.5;


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



/* old position of the mouse */
int oldX = -13;
int oldY = -13;

/* mouse state, UP or DOWN */
int mState = UP;

/* current axis of rotation */
int axisRot = X_AXIS;

/* amount to rotate about axis */
float rotate = 0.0f;

/* vector which describes the axis to rotate about */
vec3_t axis = {1.0, 0.0, 0.0};

/* global rotation, for use with the mouse */
vec3_t gRot = {45,0,45};

int _desityThresholdTF = 0;


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
