#pragma once

#ifndef ENTITY_IMPL_H
#define ENTITY_IMPL_H

#include "Component.h"
#include "Entity.h"
#include <unordered_map>
#include <typeindex>
#include <string>
#include <memory>

namespace Orca
{
    struct Entity::Impl
    {
        std::unordered_map<std::type_index, std::shared_ptr<Component>> m_Components;
        std::string name;
        uint32_t id;

        Impl() : id(0), name("New Entity") {}
        Impl(uint32_t entityID) : id(entityID), name("Entity" + std::to_string(entityID)) {}
    };
}

#endif