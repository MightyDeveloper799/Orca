#include "Object.h"
#include <Scene/SkeletonComponent.h>
#include <Scene/AnimationComponent.h>
#include <Scene/RigidBodyComponent.h>
#include <Scene/MeshComponent.h>
#include <Scripting/ScriptComponent.h>

namespace Orca
{
	Object::Object(const std::string& name) : m_Name(name), m_Entity(std::make_unique<Entity>()) {}

	Object::~Object() {}

    void Object::Update(float dt) 
    {
        if (m_Entity) m_Entity->Update(dt);
    }

    void Object::Render() 
    {
        if (m_Entity) m_Entity->Render();
    }

    void Object::AddComponent(std::shared_ptr<Component> component) 
    {
        if (m_Entity) m_Entity->AddComponent(component);
    }

    std::shared_ptr<Object> Object::GetParent() const 
    {
        return m_Parent;
    }

    void Object::SetParent(std::shared_ptr<Object> parent) 
    {
        m_Parent = parent;
    }

    const std::string& Object::GetName() const
    {
        return m_Name;
    }

    void Object::SetName(const std::string& name) 
    {
        m_Name = name;
    }

    template<typename T>
    std::shared_ptr<T> Object::GetComponent() 
    {
        if (!m_Entity)
        {
            return nullptr;
        }

        T* raw_ptr = m_Entity->GetComponent<T>();

        if (raw_ptr)
        {
            return std::shared_ptr<T>(raw_ptr);
        }

        return nullptr;
    }

    template std::shared_ptr<Orca::SkeletonComponent> Orca::Object::GetComponent<Orca::SkeletonComponent>();
    template std::shared_ptr<Orca::AnimationComponent> Orca::Object::GetComponent<Orca::AnimationComponent>();
    template std::shared_ptr<Orca::RigidBodyComponent> Orca::Object::GetComponent<Orca::RigidBodyComponent>();
    template std::shared_ptr<Orca::MeshComponent> Orca::Object::GetComponent<Orca::MeshComponent>();
    template std::shared_ptr<Orca::ScriptComponent> Orca::Object::GetComponent<Orca::ScriptComponent>();
}