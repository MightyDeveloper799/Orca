#pragma once

#ifndef INPUT_STATE_H
#define INPUT_STATE_H

#include <unordered_map>
#include <string>
#include <glm/glm.hpp>
#include "../OrcaAPI.h"
#include <memory>

namespace Orca 
{
#pragma warning(push)
#pragma warning(disable: 4251)

    enum class ORCA_API KeyState 
    {
        None,
        Pressed,
        Held,
        Released
    };

    class ORCA_API InputState 
    {
    public:
        InputState();
        ~InputState();
        InputState(InputState&&) noexcept;
        InputState& operator=(InputState&&) noexcept;

        void SetKeyState(int keyCode, KeyState state);
        KeyState GetKeyState(int keyCode) const;

        void SetMousePosition(const glm::vec2& position);
        glm::vec2 GetMousePosition() const;

        void Clear();

    private:
        struct Impl;
        std::unique_ptr<Impl> pImpl;
    };
#pragma warning(pop)
}

#endif