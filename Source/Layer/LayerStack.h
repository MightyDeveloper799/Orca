#pragma once

#ifndef LAYER_STACK_H
#define LAYER_STACK_H

#include "../OrcaAPI.h"
#include "Layer.h"
#include <vector>
#include <memory>

namespace Orca
{
#pragma warning(push)
#pragma warning(disable : 4251)

	class ORCA_API LayerStack
	{
	public:
		using LayerPtr = std::unique_ptr<Layer>;

		LayerStack() = default;
		~LayerStack();

		LayerStack(const LayerStack&) = delete;
		LayerStack& operator=(const LayerStack&) = delete;

		void PushLayer(LayerPtr layer);
		void PushOverlay(LayerPtr layer);

		void PopLayer(Layer* layer);
		void PopOverlay(Layer* layer);

		std::vector<LayerPtr>::iterator begin() { return m_Layers.begin(); }
		std::vector<LayerPtr>::iterator end() { return m_Layers.end(); }
		std::vector<LayerPtr>::reverse_iterator rbegin() { return m_Layers.rbegin(); }
		std::vector<LayerPtr>::reverse_iterator rend() { return m_Layers.rend(); }

		std::vector<LayerPtr>::const_iterator begin() const { return m_Layers.begin(); }
		std::vector<LayerPtr>::const_iterator end()	const { return m_Layers.end(); }

	private:
		std::vector<LayerPtr> m_Layers;
		unsigned int m_LayerInsertIndex = 0;
	};

#pragma warning(pop)
}

#endif