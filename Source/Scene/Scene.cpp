#include "Scene.h"
#include "Entity.h"
#include "RigidBodyComponent.h"
#include "../Core/Logger.h"
#include <Scripting/ScriptComponent.h>
#include "../Runtime/RuntimeContext.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include <stdexcept>

namespace Orca
{
	struct Scene::Impl
	{
		std::vector<std::unique_ptr<Entity>> m_Entities;
		std::vector<std::shared_ptr<Object>> m_Objects;
		std::unordered_map<std::string, Entity*> nameLookup;
		uint32_t m_NextEntityID = 0;
		RuntimeContext* r_Ctx = nullptr;
	};

	Scene::Scene(RuntimeContext& ctx)
		: pImpl(std::make_unique<Impl>())
	{
		pImpl->r_Ctx = &ctx;
	}

	Scene::~Scene() = default;

	void Scene::Initialize() {}

	Entity* Scene::CreateEntity()
	{
		if (!pImpl)
			throw std::runtime_error("pImpl is null (0x00)!");

		uint32_t newID = pImpl->m_NextEntityID++;

		Entity* newEntity = new Entity(newID, this);

		pImpl->m_Entities.push_back(std::unique_ptr<Entity>(newEntity));

		return newEntity;
	}

	void Scene::Update(float dt)
	{
		for (auto& entity : pImpl->m_Entities)
		{
			entity->Update(dt);
		}
	}

	void Scene::Render()
	{
		for (auto* entity : GetEntitiesWith<MeshComponent, TransformComponent>()) 
		{
			auto* mesh = entity->GetComponent<MeshComponent>();
			auto* transform = entity->GetComponent<TransformComponent>();
			
			if (!mesh || !transform) continue;

			mesh->Draw();
		}
	}

	std::vector<std::unique_ptr<Entity>>& Scene::GetEntities()
	{
		return pImpl->m_Entities;
	}

	const std::vector<std::shared_ptr<Object>>& Scene::GetObjects() const
	{
		return pImpl->m_Objects;
	}

	std::vector<Entity*> Scene::GetAllEntities()
	{
		std::vector<Entity*> result;

		for (auto& e : pImpl->m_Entities)
			result.push_back(e.get());

		return result;
	}

	RuntimeContext& Scene::GetRuntimeContext()
	{
		if (!pImpl || !pImpl->r_Ctx)
		{
			Logger::Log(LogLevel::Fatal, "GetRuntimeContext: runtimeContext is null!");
;			throw std::runtime_error("Scene::GetRuntimeContext: runtimeContext is null!");
		}
		return *pImpl->r_Ctx;
	}

	Entity* Scene::GetEntityByName(const std::string& name) 
	{
		auto it = pImpl->nameLookup.find(name);
		return (it != pImpl->nameLookup.end()) ? it->second : nullptr;
	}

	void Scene::DestroyEntity(Entity* entity) 
	{
		auto it = std::remove_if(pImpl->m_Entities.begin(), pImpl->m_Entities.end(),
			[&](const std::unique_ptr<Entity>& e) 
			{
				return e->GetID() == entity->GetID();
			});

		pImpl->m_Entities.erase(it, pImpl->m_Entities.end());

		for (auto iter = pImpl->nameLookup.begin(); iter != pImpl->nameLookup.end(); iter++)
		{
			if (iter->second->GetID() == entity->GetID())
				iter = pImpl->nameLookup.erase(iter);
			else
				++iter;
		}
	}

	template std::vector<Orca::Entity*> Orca::Scene::GetEntitiesWith<Orca::RigidBodyComponent>();
	template std::vector<Orca::Entity*> Orca::Scene::GetEntitiesWith<Orca::ScriptComponent>();
	template std::vector<Orca::Entity*> Orca::Scene::GetEntitiesWith<Orca::MeshComponent, Orca::TransformComponent>();
}