#pragma once

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector3.h"
#include "Quaternion.h"
#include "../OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

    struct ORCA_API Transform
    {
        Vector3 position;
        Quaternion rotation;
        Vector3 scale;

        Transform();
        Matrix4 ToMatrix() const;
    };
#pragma warning(pop)
}

#endif