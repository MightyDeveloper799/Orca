#pragma once

#ifndef CAMERA_SYSTEM_H
#define CAMERA_SYSTEM_H

#include "Scene/Entity.h"
#include "RuntimeContext.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class CameraSystem
	{
	public:
		static void Initialize();
		static void Shutdown();
		static void Update(RuntimeContext& context);

		static Entity* GetActiveCamera();
		static void SetActiveCamera(Entity camera);

	private:
		static Entity* s_ActiveCamera;
	};
#pragma warning(pop)
}

#endif