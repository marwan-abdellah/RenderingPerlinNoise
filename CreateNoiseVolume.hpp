#ifndef CREATENOISEVOLUME_HPP
#define CREATENOISEVOLUME_HPP

#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "simplexnoise.h"
#include "simplextextures.h"
#include "Utils.h"
#include "Shared.h"
#include "VolumeSharedData.h"

using namespace std;

float fAbs (float val)
{
    if (val > 0)
        return val;
    else
        return val * -1;
}

char* CreateNoiseVolume(const int volWidth,
                        const int volHeight,
                        const int volDepth);

void UpdateNoiseVolume(char* pData,
                       const int volWidth,
                       const int volHeight,
                       const int volDepth);

void UpdateNoise();

char* CreateNoiseVolume(const int volWidth,
                        const int volHeight,
                        const int volDepth)
{
    INFO("Creating noise");
    const int volumeSize = volWidth * volHeight * volDepth;
    char* pData_1D = (char*) malloc (sizeof(char) * volumeSize);

    float octaves = 1;
    float persistence = 1;
    float scale = 0.01;

    int index = 0;
    for (int i = 0; i < volWidth; i++)
        for (int j = 0; j < volHeight; j++)
            for (int k = 0; k < volDepth; k++)
            {
                pData_1D[index] = 256 * fAbs(octave_noise_3d(octaves,
                                                             persistence,
                                                             scale,
                                                             i,
                                                             j,
                                                             k));

                index++;
            }
    INFO("Noise creation is done");
    return pData_1D;
}

void UpdateNoiseVolume(char* pData,
                       const int volWidth,
                       const int volHeight,
                       const int volDepth)
{
    INFO("Updating noise");
    int index = 0;
    for (int i = 0; i < volWidth; i++)
        for (int j = 0; j < volHeight; j++)
            for (int k = 0; k < volDepth; k++)
            {
                pData[index] = 256 * fAbs(octave_noise_3d(_octaves,
                                                          _persistence,
                                                          _scale,
                                                          i,
                                                          j,
                                                          k));

                index++;
            }
    INFO("Noise update is done");

}

void UpdateNoise()
{
    UpdateNoiseVolume(_lumVolumeData,
                           _volumeWidth,
                           _volumeHeight,
                           _volumeDepth);
}


#endif // CREATENOISEVOLUME_HPP
