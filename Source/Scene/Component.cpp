#include "Component.h"
#include "Entity.h"

namespace Orca
{
	void Component::SetOwner(Entity* entity)
	{
		owner = entity;
	}

	Entity* Component::GetOwner() const
	{
		return owner;
	}
}