#pragma once

#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <memory>
#include <mutex>
#include "Scene.h"
#include "../OrcaAPI.h"

namespace Orca
{
#pragma warning(push)
#pragma warning(disable: 4251)

	class ORCA_API SceneManager
	{
	public:
		static void LoadScene(std::shared_ptr<Scene> newScene);
		static void Update(float dt);
		static void Render();
		static void SetCurrentScene(std::shared_ptr<Scene> scene);
		static std::shared_ptr<Scene> GetCurrentScene();

		static void SetActiveScene(std::shared_ptr<Scene> scene);
		static std::shared_ptr<Scene> GetActiveScene();

	private:
		static std::shared_ptr<Scene> currentScene;
		static std::shared_ptr<Scene> activeScene;
		static std::mutex s_SceneMutex;
	};
}

#endif