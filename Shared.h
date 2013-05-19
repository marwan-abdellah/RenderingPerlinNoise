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
