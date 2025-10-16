#include "ObjectManager.h"

namespace Orca {

    std::shared_ptr<Object> ObjectManager::CreateObject(const std::string& name) 
    {
        auto obj = std::make_shared<Object>(name);
        m_Objects.push_back(obj);
        return obj;
    }

    std::shared_ptr<Object> ObjectManager::FindByName(const std::string& name) 
    {
        for (auto& obj : m_Objects) 
        {
            if (obj->GetName() == name)
                return obj;
        }
        return nullptr;
    }

    void ObjectManager::UpdateAll() 
    {
        float dt{};
        for (auto& obj : m_Objects)
            obj->Update(dt);
    }

    void ObjectManager::RenderAll() 
    {
        for (auto& obj : m_Objects)
            obj->Render();
    }
}