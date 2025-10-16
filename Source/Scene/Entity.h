#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include <stdexcept>
#include <unordered_map>
#include <typeindex>
#include <type_traits>
#include <memory>
#include <string>

#include "../Scripting/ScriptComponent.h"
#include "MeshComponent.h"
#include "RigidBodyComponent.h"
#include "SkeletonComponent.h"
#include "CameraComponent.h"
#include "AnimationComponent.h"
#include "TransformComponent.h"
#include "../OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class Component;
	class Scene;

	class ORCA_API Entity
	{
	public:
		Entity();
		Entity(uint32_t id, Scene* owningScene);

		~Entity();
		Entity(Entity&&) noexcept;
		Entity& operator=(Entity&&) noexcept;

		Entity(const Entity&) = delete;
		Entity& operator=(const Entity&) = delete;

		template<typename T>
		static std::type_index GetTypeID()
		{
			return std::type_index(typeid(T));
		}

		template<typename T>
		void AddComponent(std::shared_ptr<T> component)
		{
			static_assert(std::is_base_of_v<Component, T>, "T must derive from Orca::Component");

			if (!component) return;

			AddComponentInternal(component, GetTypeID<T>());
		}

		template<typename T>
		T* GetComponent()
		{
			Component* baseComponent = GetComponentInternal(typeid(T));
			if (!baseComponent) return nullptr;

			return static_cast<T*>(baseComponent);
		}

		std::vector<std::shared_ptr<Component>> GetComponents() const;

		template<typename... Components>
		bool HasComponents() const
		{
			return (HasComponent<Components>() && ...);
		}

		template<typename T>
		bool HasComponent() const
		{
			return this->HasComponentImpl(typeid(T));
		}

		bool HasComponentImpl(const std::type_index& componentType) const;

		void Update(float dt);
		void Render();

		std::string GetName() const;
		void SetName(const std::string& filePath);

		uint32_t GetID() const;
		uint32_t GetEntityID() const { return m_EntityID; }

		bool IsValid() const;

	private:
		struct Impl;
		std::unique_ptr<Impl> pImpl;
		uint32_t m_EntityID;
		Scene* owningScene;

		Component* GetComponentInternal(std::type_index type);
		void AddComponentInternal(std::shared_ptr<Component> component, const std::type_index& type);
	};
#pragma warning(pop)
}

#include "Entity.inl"

#endif