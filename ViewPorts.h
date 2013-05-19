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

#ifndef VIEWPORTS_H
#define VIEWPORTS_H

namespace ViewPort1
{
void Display();
void Keyboard(unsigned char fKey, int fX, int fY);
void RegisterCallBacks();
void UpdateScene();
void Idle();
void Reshape(int volumeWidth, int volumeHeight);
}

namespace ViewPort2
{
void Display();
void Keyboard(unsigned char fKey, int fX, int fY);
void RegisterCallBacks();
void UpdateScene();
void Idle();
void Reshape(int volumeWidth, int volumeHeight);
}

namespace ViewPort3
{
void Display();
void Keyboard(unsigned char fKey, int fX, int fY);
void RegisterCallBacks();
void UpdateScene();
void Idle();
void ReDisplay();
void Reshape(int volumeWidth, int volumeHeight);
void glutMotion(int x, int y);
void glutMouse(int button, int state, int x, int y);
}

namespace ViewPort4
{
void Display();
void Keyboard(unsigned char fKey, int fX, int fY);
void RegisterCallBacks();
void UpdateScene();
void Idle();
void Reshape(int volumeWidth, int volumeHeight);
}

namespace ViewPorts
{
void UpdateAll();
}

/// Updating the scenes
void ViewPorts::UpdateAll()
{
    Volume::UpdateVolume();
    ViewPort1::Display();
    ViewPort2::Display();
    ViewPort3::Display();
    ViewPort4::Display();
}

#endif // VIEWPORTS_H
