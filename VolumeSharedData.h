#ifndef VOLUMESHAREDDATA_H
#define VOLUMESHAREDDATA_H

#include <GL/glut.h>
#include <iostream>
#include <string.h>
#include <stdio.h>

int _volumeWidth;
int _volumeHeight;
int _volumeDepth;

GLubyte* _lumVolumeData;
GLubyte* _RGBAVolumeData;

int _setBoundingBox = 0;

#endif // VOLUMESHAREDDATA_H
