#include "InputState.h"

namespace Orca 
{
    struct InputState::Impl 
    {
        std::unordered_map<int, KeyState> m_KeyStates;
        glm::vec2 m_MousePosition = glm::vec2(0.0f);
    };

    inline InputState::InputState() : pImpl(std::make_unique<Impl>()) {}

    inline InputState::~InputState() = default;

    inline InputState::InputState(InputState&&) noexcept = default;

    inline InputState& InputState::operator=(InputState&&) noexcept = default;

    void InputState::SetKeyState(int keyCode, KeyState state) 
    {
        pImpl->m_KeyStates[keyCode] = state;
    }

    KeyState InputState::GetKeyState(int keyCode) const 
    {
        auto it = pImpl->m_KeyStates.find(keyCode);
        return (it != pImpl->m_KeyStates.end()) ? it->second : KeyState::None;
    }

    void InputState::SetMousePosition(const glm::vec2& position) 
    {
        pImpl->m_MousePosition = position;
    }

    glm::vec2 InputState::GetMousePosition() const 
    {
        return pImpl->m_MousePosition;
    }

    void InputState::Clear() 
    {
        for (auto& [key, state] : pImpl->m_KeyStates)
        {
            if (state == KeyState::Released)
                state = KeyState::None;
            else if (state == KeyState::Pressed)
                state = KeyState::Held;
        }
    }
}