#pragma once

#ifndef LIGHT_COMPONENT_H
#define LIGHT_COMPONENT_H

#include "../OrcaAPI.h"
#include "Scene/Component.h"
#include "Math/Vector3.h"
#include <string>

namespace Orca
{
    enum class LightType
    {
        Directional,
        Point,
        Spot
    };

#pragma warning(push)
#pragma warning(disable: 4251)

    class ORCA_API LightComponent : public Component
    {
    public:
        LightComponent();

        float GetIntensity() const;
        void SetIntensity(float value);

        LightType Type = LightType::Point;
        float Intensity = 1.0f;
        Vector3 Color = Vector3(1.0f);
        float Range = 10.0f;
        float SpotAngle = 45.0f;

        std::string GetColorHex() const;
    };
}

#endif // LIGHT_COMPONENT_H