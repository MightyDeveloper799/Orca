#include "Component.h"
#include "EntityImpl.h"
#include "../Core/Logger.h"
#include "Entity.h"
#include <memory>
#include <map>

namespace Orca
{
	Entity::Entity() : pImpl(std::make_unique<Impl>()), m_EntityID(0), owningScene(nullptr) {}
	Entity::Entity(uint32_t id, Scene* owningScene) : pImpl(std::make_unique<Impl>()), m_EntityID(id), owningScene(owningScene) {}

	Entity::~Entity() = default;
	Entity::Entity(Entity&&) noexcept = default;
	Entity& Entity::operator=(Entity&&) noexcept = default;

	std::vector<std::shared_ptr<Component>> Entity::GetComponents() const
	{
		std::vector<std::shared_ptr<Component>> components;

		for (const auto& pair : pImpl->m_Components)
		{
			components.push_back(pair.second);
		}

		return components;
	}

	bool Entity::HasComponentImpl(const std::type_index& componentType) const
	{
		return pImpl->m_Components.count(componentType) > 0;
	}

	void Entity::Update(float dt)
	{
		for (auto& [type, comp] : pImpl->m_Components)
		{
			comp->Update(dt);
		}
	}

	void Entity::Render()
	{
		for (auto& [type, comp] : pImpl->m_Components)
		{
			comp->Render();
		}
	}

	std::string Entity::GetName() const
	{
		return pImpl->name;
	}

	void Entity::SetName(const std::string& filePath)
	{
		pImpl->name = filePath;
	}

	uint32_t Entity::GetID() const 
	{
		return pImpl->id;
	}

	bool Entity::IsValid() const 
	{
		return pImpl->id != 0;
	}

	Component* Entity::GetComponentInternal(std::type_index type)
	{
		auto it = pImpl->m_Components.find(type);
		if (it != pImpl->m_Components.end())
		{
			return it->second.get();
		}
		return nullptr;
	}

	void Entity::AddComponentInternal(std::shared_ptr<Component> component, const std::type_index& type)
	{
		if (!pImpl) 
		{
			Logger::Log(LogLevel::Error, "AddComponentInternal failed: pImpl is null!");
			throw std::runtime_error("Entity is not initialized!");
		}

		if (!component || !component.get())
		{
			Logger::Log(LogLevel::Error, "AddComponentInternal failed: component is null!");
			throw std::runtime_error("component is not initialized!");
		}

		if (pImpl->m_Components.count(type))
		{
			Logger::Log(LogLevel::Warning, "Component of type " + std::string(type.name()) + " already exists in entity " + std::to_string(GetID()));
			return;
		}

		component->SetOwner(this);

		pImpl->m_Components.insert({ type, component });

		Logger::Log(LogLevel::Info, "Injecting component: " + std::string(type.name()) + " into entity: " + std::to_string(GetID()));

		component->OnAttach();
	}

	template Orca::ScriptComponent* Orca::Entity::GetComponent<Orca::ScriptComponent>();
	template Orca::MeshComponent* Orca::Entity::GetComponent<Orca::MeshComponent>();
	template Orca::RigidBodyComponent* Orca::Entity::GetComponent<Orca::RigidBodyComponent>();
	template Orca::AnimationComponent* Orca::Entity::GetComponent<Orca::AnimationComponent>();
	template Orca::SkeletonComponent* Orca::Entity::GetComponent<Orca::SkeletonComponent>();
	template Orca::TransformComponent* Orca::Entity::GetComponent<Orca::TransformComponent>();
	template Orca::CameraComponent* Orca::Entity::GetComponent<Orca::CameraComponent>();

	template void Orca::Entity::AddComponent<Orca::Component>(std::shared_ptr<Orca::Component>);

	template void Orca::Entity::AddComponent<Orca::ScriptComponent>(std::shared_ptr<Orca::ScriptComponent>);
	template void Orca::Entity::AddComponent<Orca::MeshComponent>(std::shared_ptr<Orca::MeshComponent>);
	template void Orca::Entity::AddComponent<Orca::RigidBodyComponent>(std::shared_ptr<Orca::RigidBodyComponent>);
	template void Orca::Entity::AddComponent<Orca::AnimationComponent>(std::shared_ptr<Orca::AnimationComponent>);
	template void Orca::Entity::AddComponent<Orca::SkeletonComponent>(std::shared_ptr<Orca::SkeletonComponent>);
	template void Orca::Entity::AddComponent<Orca::TransformComponent>(std::shared_ptr<Orca::TransformComponent>);
	template void Orca::Entity::AddComponent<Orca::CameraComponent>(std::shared_ptr<Orca::CameraComponent>);
}