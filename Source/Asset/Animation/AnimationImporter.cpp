#include "AnimationImporter.h"
#define TINYGLTF_NO_STB_IMAGE
#define TINYGLTF_NO_STB_IMAGE_WRITE
#include <tiny_gltf.h>
#include <iostream>
#include <unordered_map>

namespace Orca
{
	std::vector<AnimationClip> AnimationImporter::ImportFromGLB(const std::string & filePath)
	{
		tinygltf::Model model;
		tinygltf::TinyGLTF loader;
		std::string err, warn;

		bool success = loader.LoadBinaryFromFile(&model, &err, &warn, filePath);
		if (!success)
		{
			std::cerr << "[Orca(R)] Failed to load GLB: " << err << std::endl;
			return {};
		}

		if (!warn.empty())
		{
			std::cout << "[WARNING]: " << warn << std::endl;
		}

		if (model.animations.empty())
		{
			std::cerr << "No animation data found: " << filePath << std::endl;
			return {};
		}

		std::vector<AnimationClip> clips;
		for (const auto& gltfAnim : model.animations)
		{
			std::string clipName = gltfAnim.name.empty() ? "UnnamedClip" : gltfAnim.name;
			float maxTime = 0.0f;
			AnimationClip clip(clipName, 0.0f);
			
			for (const auto& channel : gltfAnim.channels) 
			{
				const auto& sampler = gltfAnim.samplers[channel.sampler];
				const std::string& targetPath = channel.target_path;
				std::string boneName = model.nodes[channel.target_node].name;

				const auto& inputAccessor = model.accessors[sampler.input];
				const auto& outputAccessor = model.accessors[sampler.output];

				const auto& inputView = model.bufferViews[inputAccessor.bufferView];
				const auto& outputView = model.bufferViews[outputAccessor.bufferView];

				const auto& inputBuffer = model.buffers[inputView.buffer];
				const auto& outputBuffer = model.buffers[outputView.buffer];

				const float* times = reinterpret_cast<const float*>(
					&inputBuffer.data[inputView.byteOffset + inputAccessor.byteOffset]);

				const float* values = reinterpret_cast<const float*>(
					&outputBuffer.data[outputView.byteOffset + outputAccessor.byteOffset]);

				for (size_t i = 0; i < inputAccessor.count; ++i) 
				{
					Keyframe frame;
					frame.time = times[i];

					std::string key = boneName + "_" + targetPath;
					frame.boneTransforms[key] = values[i];

					clip.AddKeyframe(frame);
					if (frame.time > maxTime) maxTime = frame.time;
				}
			}

			clip.SetDuration(maxTime);
			clips.push_back(clip);
		}

		return clips;
	}
}