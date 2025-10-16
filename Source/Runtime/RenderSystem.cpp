#include "RenderSystem.h"
#include "../Scene/MeshComponent.h"
#include "../Scene/TransformComponent.h"
#include "../Renderer/Shader.h"
#include "../Scene/Entity.h"
#include "../Scene/Scene.h"
#include "../Core/Logger.h"
#include <filesystem>
#include "../Renderer/ShaderRegistry.h"
#include "../Scene/CameraComponent.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

namespace fs = std::filesystem;

namespace Orca
{
    void RenderSystem::Initialize()
    {
        try
        {
            const std::string shaderDir = "C:\\Users\\Administrator\\OneDrive\\Documents\\Projects\\Orca\\Source\\Runtime\\Shaders";

            if (!fs::exists(shaderDir))
            {
                Logger::Log(LogLevel::Fatal, "Shader Dir isn't found : " + shaderDir);
                return;
            }

            std::unordered_map<std::string, std::string> vertShaders;
            std::unordered_map<std::string, std::string> fragShaders;

            for (const auto& entry : fs::directory_iterator(shaderDir))
            {
                if (!entry.is_regular_file()) continue;

                const std::string path = entry.path().string();
                const std::string name = entry.path().stem().string();
                const std::string ext = entry.path().extension().string();

                if (ext == ".vert") vertShaders[name] = path;
                else if (ext == ".frag") fragShaders[name] = path;
            }

            for (const auto& [name, vertPath] : vertShaders)
            {
                if (fragShaders.find(name) != fragShaders.end())
                {
                    const std::string& fragPath = fragShaders.at(name);
                    ShaderRegistry::Preload(name, vertPath, fragPath);
                    Logger::Log(LogLevel::Info, "Shader loaded: " + name);
                }
                else
                {
                    Logger::Log(LogLevel::Warning, "Missing fragment shader for: " + name);
                }
            }
        }
        catch (const fs::filesystem_error& e)
        {
            Logger::Log(LogLevel::Fatal, std::string("Filesystem error during shader loading: ") + e.what());
            throw;
        }
        catch (const std::exception& e)
        {
            Logger::Log(LogLevel::Fatal, std::string("CRITICAL RENDER INIT ERROR: ") + e.what());
            throw;
        }
    }

    void RenderSystem::Render(RuntimeContext& ctx)
    {
        Logger::Log(LogLevel::Info, "RenderSystem::Render: Entry: Starting frame draw sequence...");

        try
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            Logger::Log(LogLevel::Info, "RenderSystem::Render: OpenGL buffers cleared. Starting scene access...");

            std::shared_ptr<Scene> activeScene = ctx.GetActiveSceneShared();

            if (!activeScene)
            {
                Logger::Log(LogLevel::Fatal, "RenderSystem::Render failed: Active scene pointer is NULL! Skipping frame...");
                return;
            }

            std::string sceneAddress = std::to_string(reinterpret_cast<std::uintptr_t>(activeScene.get()));
            Logger::Log(LogLevel::Info, "RenderSystem::Render invoked. Scene address: " + sceneAddress);

            glm::mat4 viewProjectionMatrix(1.0f);

            auto cameras = activeScene->GetEntitiesWith<CameraComponent, TransformComponent>();

            if (!cameras.empty())
            {
                Entity* cameraEntity = cameras.front();
                CameraComponent* camera = cameraEntity->GetComponent<CameraComponent>();
                TransformComponent* cameraTransform = cameraEntity->GetComponent<TransformComponent>();

                if (camera && cameraTransform)
                {
                    viewProjectionMatrix = camera->GetViewMatrix();
                    Logger::Log(LogLevel::Info, "Successfully calculated ViewProjection matrix from primary camera.");
                }
                else
                {
                    Logger::Log(LogLevel::Warning, "Camera components were present but invalid.");
                }
            }
            else
            {
                Logger::Log(LogLevel::Error, "No active CameraComponent found. ViewProjection matrix is Identity.");
            }

            for (auto& entity : activeScene->GetEntitiesWith<MeshComponent, TransformComponent>())
            {
                MeshComponent* mesh = entity->GetComponent<MeshComponent>();
                TransformComponent* transform = entity->GetComponent<TransformComponent>();

                if (!mesh || !transform)
                {
                    Logger::Log(LogLevel::Warning, "Missing components—skipping entity: " + entity->GetName());
                    continue;
                }

                Material* material = mesh->GetMaterial().get();
                if (!material)
                {
                    Logger::Log(LogLevel::Warning, "Material is null—skipping entity: " + entity->GetName());
                    continue;
                }

                Mesh* meshAsset = mesh->GetMesh().get();
                if (!meshAsset || !meshAsset->IsRenderable())
                {
                    Logger::Log(LogLevel::Warning, "Mesh asset is not renderable—skipping entity: " + entity->GetName());
                    continue;
                }

                if (mesh && transform)
                {
                    Shader& shader = material->GetShader();
                    if (!shader.IsValid())
                    {
                        Logger::Log(LogLevel::Warning, "Shader is invalid—skipping draw for entity: " + entity->GetName());
                        continue;
                    }

                    try
                    {
                        Logger::Log(LogLevel::Info, "Binding shader for entity: " + entity->GetName());
                        shader.Bind();

                        Logger::Log(LogLevel::Info, "Setting u_ViewProjection...");
                        shader.SetMat4("u_ViewProjection", viewProjectionMatrix);

                        Logger::Log(LogLevel::Info, "Setting u_Model...");
                        shader.SetMat4("u_Model", transform->GetMatrix());
                    }
                    catch (const std::exception& e)
                    {
                        Logger::Log(LogLevel::Fatal, "Shader binding or uniform upload failed: " + std::string(e.what()));
                        throw;
                    }
                    try
                    {
                        Logger::Log(LogLevel::Info, "Drawing mesh...");
                        meshAsset->Draw();
                        shader.Unbind();
                    }
                    catch (const std::exception& e)
                    {
                        Logger::Log(LogLevel::Fatal, "Mesh draw failed: " + std::string(e.what()));
                        throw;
                    }

                    GLenum err = glGetError();
                    if (err != GL_NO_ERROR)
                    {
                        Logger::Log(LogLevel::Error, "OpenGL error after draw: " + std::to_string(err));
                    }
                }
            }
        }
        catch (const std::runtime_error& e)
        {
            Logger::Log(LogLevel::Fatal, std::string("RenderSystem::Render exception caught (Scene access failed): ") + e.what());
        }
        catch (const std::exception& e)
        {
            Logger::Log(LogLevel::Fatal, std::string("RenderSystem::Render exception caught, aborting frame: ") + e.what());
            throw;
        }
    }

    void RenderSystem::Shutdown()
    {
        ShaderRegistry::Clear();
    }
}