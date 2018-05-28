/*
  This is free and unencumbered software released into the public domain.
  Author: pavel.hromada@gmail.com
*/

#ifndef BUILDPROVIDERSLOADER_H
#define BUILDPROVIDERSLOADER_H

#include <memory>
#include <vector>

#include "buildinfoprovider.h"

class BuildProvidersLoader
{
public:
    BuildProvidersLoader() = delete;

    static BuildInfoProviderContainer loadBuildInfoProviders();
};

#endif // BUILDPROVIDERSLOADER_H
