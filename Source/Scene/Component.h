#pragma once

#ifndef COMPONENT_H
#define COMPONENT_H

#include "../OrcaAPI.h"

namespace Orca
{
	class Entity;

#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API Component
	{
	public:
		virtual ~Component() = default;

		virtual void OnAttach() {}
		virtual void OnStart() {}
		virtual void Update(float dt) {}
		virtual void Render() {}

		void SetOwner(Entity* entity);
		Entity* GetOwner() const;

	protected:
		Entity* owner = nullptr;
	};
#pragma warning(pop)
}

#endif