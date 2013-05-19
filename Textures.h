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

#ifndef TEXTURES_H
#define TEXTURES_H

#include <iostream>
#include <string.h>
#include <stdio.h>
#include "GL/glut.h"

#include "Shared.h"
#include "GL_Utils.h"
#include "MainScene.hpp"
#include "VolumeSharedData.h"
#include "DisplayList.hpp"

namespace Texture
{
    void Init();
}

/// Initalizing the tetxure for each context
void Texture::Init()
{
    // Clearing color buffer
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // Generating texture ID and binding it to the GPU
    glGenTextures(1, &_volumeTexID);
    glBindTexture(GL_TEXTURE_3D, _volumeTexID);

    // Adjusting the texture parameters
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // For automatic texture coordinate generation
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);

    // Allocating the texture on the GPU
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA,
                 _volumeWidth, _volumeHeight, _volumeDepth, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, _RGBAVolumeData);

    // Enable texturing
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_TEXTURE_GEN_R);

    // Setting the blending function & enabling blending
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    // Creating the display  list


     // Rendering the diaply list of the rectangles
     if (glutGetWindow() == view1)
              SetDisplayListDistance(0.0);
     else
              SetDisplayList();
}

#endif // TEXTURES_H
