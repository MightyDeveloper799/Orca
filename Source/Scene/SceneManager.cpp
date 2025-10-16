#include "SceneManager.h"
#include <Core/Logger.h>

namespace Orca
{
	std::shared_ptr<Scene> SceneManager::currentScene = nullptr;
	std::shared_ptr<Scene> SceneManager::activeScene = nullptr;
	std::mutex SceneManager::s_SceneMutex;

	void SceneManager::LoadScene(std::shared_ptr<Scene> newScene)
	{
		std::lock_guard<std::mutex> lock(s_SceneMutex);
		currentScene = newScene;
		activeScene = newScene;
	}

	void SceneManager::Update(float deltaTime) 
	{
		std::lock_guard<std::mutex> lock(s_SceneMutex);
		if (activeScene) activeScene->Update(deltaTime);
	}

	void SceneManager::Render() 
	{
		std::lock_guard<std::mutex> lock(s_SceneMutex);
		if (activeScene) activeScene->Render();
	}

	void SceneManager::SetCurrentScene(std::shared_ptr<Scene> scene)
	{
		std::lock_guard<std::mutex> lock(s_SceneMutex);
		Logger::Log(LogLevel::Info, "SceneManager::SetCurrentScene called with address: " +
			std::to_string(reinterpret_cast<uintptr_t>(scene.get())));

		if (!scene)
			throw std::runtime_error("SceneManager::SetCurrentScene received null scene");

		activeScene = scene;
		currentScene = scene;
	}

	std::shared_ptr<Scene> SceneManager::GetCurrentScene() 
	{
		std::lock_guard<std::mutex> lock(s_SceneMutex);
		return activeScene;
	}

	void SceneManager::SetActiveScene(std::shared_ptr<Scene> scene) 
	{
		std::lock_guard<std::mutex> lock(s_SceneMutex);
		Logger::Log(LogLevel::Info, "SceneManager::SetActiveScene called with address: " +
			std::to_string(reinterpret_cast<uintptr_t>(scene.get())));

		if (!scene)
			throw std::runtime_error("SceneManager::SetActiveScene received null scene");

		activeScene = scene;
		currentScene = scene;
	}

	std::shared_ptr<Scene> SceneManager::GetActiveScene()
	{
		std::lock_guard<std::mutex> lock(s_SceneMutex);
		Logger::Log(LogLevel::Info, "GetActiveScene returning: " +
			std::to_string(reinterpret_cast<uintptr_t>(activeScene.get())));
		if (!activeScene)
			Logger::Log(LogLevel::Fatal, "GetActiveScene failed: No active scene has been set!");
		return activeScene;
	}
}