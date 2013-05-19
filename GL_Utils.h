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

#ifndef GL_UTILS_H
#define GL_UTILS_H

#include "Shared.h"
#include "GL_Utils.h"

# define GLUT_WHEEL_UP 3
# define GLUT_WHEEL_DOWN 4

/// Prototypes
void SetFontParams(char* name, int size);
void DrawString(GLuint x, GLuint y, const char* format, int length);
void ResetViewport();

/// Font setting
void SetFontParams(char* name, int size)
{
    fontStyleGL = GLUT_BITMAP_HELVETICA_10;
    if (strcmp(name, "helvetica") == 0)
    {
        if (size == 12)
            fontStyleGL = GLUT_BITMAP_HELVETICA_12;
        else if (size == 18)
            fontStyleGL = GLUT_BITMAP_HELVETICA_18;
    }
    else if (strcmp(name, "times roman") == 0)
    {
        fontStyleGL = GLUT_BITMAP_TIMES_ROMAN_10;
        if (size == 24)
            fontStyleGL = GLUT_BITMAP_TIMES_ROMAN_24;
    }
    else if (strcmp(name, "8x13") == 0)
        fontStyleGL = GLUT_BITMAP_8_BY_13;
    else if (strcmp(name, "9x15") == 0)
        fontStyleGL = GLUT_BITMAP_9_BY_15;
}

/// String Draw
void DrawString(GLuint x, GLuint y, const char* format, int length)
{
    glRasterPos2i(x, y);
    for(int i=0; i<length; ++i)
        glutBitmapCharacter(fontStyleGL, *(format+i) );
}

/// Reset a single viewport
void ResetViewport()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, 0.5, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

#endif // GL_UTILS_H
