#ifndef SHARED_H
#define SHARED_H

#include "GL/glut.h"
#include <iostream>
#include <string.h>
#include <stdio.h>

// Gap between the different viewports
#define GAP  20

GLuint subWinWidth;
GLuint subWinHeight;
GLuint window;
GLuint view1, view2, view3, view4;
GLuint screenWidth;
GLuint screenHeight;

// Font
GLvoid *fontStyleGL = GLUT_BITMAP_TIMES_ROMAN_10;

#endif // SHARED_H
