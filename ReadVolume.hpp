#ifndef READVOLUME_HPP
#define READVOLUME_HPP

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>

#include "Shared.h"
#include "GL_Utils.h"
#include "Utils.h"
#include "VolumeSharedData.h"

using namespace std;

namespace Volume
{
void ReadHeader(char *prefix, int &volWidth, int &volHeight, int &volDepth);
void UpdateVolume();
void ReadVolume(char *prefix);
}

void Volume::ReadHeader(char *prefix,
                        int &volWidth,
                        int &volHeight,
                        int &volDepth)
{
    INFO("Reading the volume header");

    char hdrFile[300];
    ifstream inputFileStream;

    // Adding the ".hdr" prefix to the dataset path
    sprintf(hdrFile, "%s.hdr", prefix);

    // Open the eader hdrFile to read the dataset dimensions
    inputFileStream.open(hdrFile, std::ios::in);

    // Checking the openning of the file
    if (inputFileStream.fail())
    {
        INFO("Could not open the HDR file");
        INFO("Exiting");
        EXIT(0);
    }

    // Reading the dimensions
    inputFileStream >> volWidth;
    inputFileStream >> volHeight;
    inputFileStream >> volDepth;

    // Closing the ".hdr" file
    inputFileStream.close();

    INFO("Reading the volume header Done");
}

void Volume::UpdateVolume()
{
    // Poiter to the volume image
    GLubyte *ptr = _lumVolumeData;

    if (_setBoundingBox)
    {
        // Put a box around the volume so that we can see the outline
        // of the data.
        INFO("Setting the Bounding Box");

        int i, j, k;
        for (i = 0; i < _volumeDepth; i++) {
            for (j = 0; j < _volumeHeight; j++) {
                for (k = 0; k < _volumeWidth; k++) {
                    if (((i < 4) && (j < 4)) ||
                            ((j < 4) && (k < 4)) ||
                            ((k < 4) && (i < 4)) ||
                            ((i < 4) && (j >  _volumeHeight-5)) ||
                            ((j < 4) && (k > _volumeWidth-5)) ||
                            ((k < 4) && (i > _volumeDepth-5)) ||
                            ((i > _volumeDepth-5) && (j >  _volumeHeight-5)) ||
                            ((j >  _volumeHeight-5) && (k > _volumeWidth-5)) ||
                            ((k > _volumeWidth-5) && (i > _volumeDepth-5)) ||
                            ((i > _volumeDepth-5) && (j < 4)) ||
                            ((j >  _volumeHeight-5) && (k < 4)) ||
                            ((k > _volumeWidth-5) && (i < 4))) {
                        *ptr = 110;
                    }
                    ptr++;
                }
            }
        }
    }
    else
        INFO("NO bounding box");

    // retrun to the first element
    ptr = _lumVolumeData;

    // Pointer to the RGBA image
    GLubyte *qtr = _RGBAVolumeData;

    // Luminance & RGBA values
    GLubyte rgbaVal, luminanceVal;

    // Reading the luminance volume and constructing the RGBA volume
    for (int i = 0; i < _volNumVoxels; i++)
    {
        rgbaVal = *(ptr++);

        // Area of interest
        luminanceVal = (rgbaVal < _desityThresholdTF) ? 0 : rgbaVal - _desityThresholdTF;

        // Division by 2
        luminanceVal = luminanceVal >> 1;

        *(qtr++) = ((float)luminanceVal) * _rValueTF;
        *(qtr++) = ((float)luminanceVal) * _gValueTF;
        *(qtr++) = ((float)luminanceVal) * _bValueTF;
        *(qtr++) = ((float)luminanceVal) * _aValueTF;
    }
}

void Volume::ReadVolume(char *prefix)
{
    char imgFile[100];
    ifstream inputFileStream;

    // Reading the header file
    ReadHeader(prefix, _volumeWidth, _volumeHeight, _volumeDepth);

    // Adding the ".img" prefix to the dataset path
    sprintf(imgFile, "%s.img", prefix);
    INFO("Reading the volume file ");

    // Total number of voxels
    _volNumVoxels = _volumeWidth * _volumeHeight * _volumeDepth;

    // Allocating the luminance image
    _lumVolumeData = new GLubyte [_volNumVoxels];

    // Allocating the RGBA image
    _RGBAVolumeData = new GLubyte [_volNumVoxels * 4];

    // Reading the volume image (luminance values)
    inputFileStream.open(imgFile, ios::in);
    if (inputFileStream.fail())
    {
        INFO("Could not open the volume file");
        EXIT(0);
    }

    // Read the image byte by byte
    inputFileStream.read((char *)_lumVolumeData, _volNumVoxels);

    // Closing the input volume stream
    inputFileStream.close();

    // Update the volume
    UpdateVolume();

    INFO("The volume has been read successfull and the RGBA one is DONE");
}

#endif // READVOLUME_HPP
