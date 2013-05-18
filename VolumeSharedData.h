#ifndef VOLUMESHAREDDATA_H
#define VOLUMESHAREDDATA_H

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
float scaleFactor       = 0.5;
char rotateState = 0;

// Slice XY half distance
float sliceArmDistance = 0.5;

// Total number of slices
int numSlices = 256;

// Orthographic projection parameter
GLfloat presSize = 1.0;


#endif // VOLUMESHAREDDATA_H
