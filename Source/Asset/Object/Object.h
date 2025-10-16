#pragma once

#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <string>
#include <vector>
#include "Scene/Entity.h"
#include "Scene/Component.h"

namespace Orca 
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class ORCA_API Object 
    {
    public:
        Object(const std::string& name);
        ~Object();

        void Update(float dt);
        void Render();

        void AddComponent(std::shared_ptr<Component> component);
        template<typename T>
        std::shared_ptr<T> GetComponent();

        void SetParent(std::shared_ptr<Object> parent);
        std::shared_ptr<Object> GetParent() const;

        const std::string& GetName() const;
        void SetName(const std::string& name);

    private:
        std::string m_Name;
        std::shared_ptr<Entity> m_Entity;
        std::shared_ptr<Object> m_Parent;
    };
#pragma warning(pop)
}

#endif