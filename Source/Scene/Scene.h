#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include <unordered_map>
#include <string> 
#include "Entity.h"
#include "../Asset/Object/Object.h"
#include "../Runtime/RuntimeContext.h"
#include "../OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API Scene
	{
	public:
		Scene(RuntimeContext& ctx);
		inline ~Scene();

		void Initialize();
		void Update(float dt);
		void Render();
		void Shutdown();

		Scene(const Scene&) = delete;
		Scene& operator=(const Scene&) = delete;

		Entity* CreateEntity();
		std::vector<std::unique_ptr<Entity>>& GetEntities();

		template<typename... Components>
		std::vector<Entity*> GetEntitiesWith()
		{
			std::vector<Entity*> result;

			for (auto& entity_ptr : GetEntities())
			{
				if (entity_ptr->HasComponents<Components...>())
				{
					result.push_back(entity_ptr.get());
				}
			}

			return result;
		}

		const std::vector<std::shared_ptr<Object>>& GetObjects() const;
		std::vector<Entity*> GetAllEntities();

		RuntimeContext& GetRuntimeContext();

		Entity* GetEntityByName(const std::string& name);
		void DestroyEntity(Entity* entity);

	private:
		struct Impl;
		std::unique_ptr<Impl> pImpl;
	};
}

#endif