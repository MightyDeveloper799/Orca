#pragma once

#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <memory>
#include <vector>
#include "Object.h"
#include "OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

    class ORCA_API ObjectManager 
    {
    public:
        std::shared_ptr<Object> CreateObject(const std::string& name);
        std::shared_ptr<Object> FindByName(const std::string& name);
        void UpdateAll();
        void RenderAll();

    private:
        std::vector<std::shared_ptr<Object>> m_Objects;
    };
#pragma warning(pop)
}

#endif