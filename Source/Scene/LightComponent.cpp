#include "LightComponent.h"
#include <sstream>
#include <iomanip>

namespace Orca
{
    LightComponent::LightComponent() = default;

    float LightComponent::GetIntensity() const
    {
        return Intensity;
    }

    void LightComponent::SetIntensity(float value)
    {
        Intensity = value;
    }

    std::string LightComponent::GetColorHex() const
    {
        auto clamp = [](float v) { return std::max(0, std::min(255, static_cast<int>(v * 255.0f))); };
        std::stringstream ss;
        ss << "#" << std::hex << std::setw(2) << std::setfill('0') << clamp(Color.x)
            << std::setw(2) << std::setfill('0') << clamp(Color.y)
            << std::setw(2) << std::setfill('0') << clamp(Color.z);
        return ss.str();
    }
}