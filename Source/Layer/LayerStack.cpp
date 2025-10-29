#include "LayerStack.h"
#include <algorithm> 

namespace Orca
{
    LayerStack::~LayerStack() {}

    void LayerStack::PushLayer(LayerPtr layer)
    {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, std::move(layer));
        m_LayerInsertIndex++;
        m_Layers[m_LayerInsertIndex - 1]->OnAttach();
    }

    void LayerStack::PushOverlay(LayerPtr overlay)
    {
        m_Layers.emplace_back(std::move(overlay));
        m_Layers.back()->OnAttach();
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find_if(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex,
            [&](const LayerPtr& element) { return element.get() == layer; });

        if (it != m_Layers.begin() + m_LayerInsertIndex)
        {
            layer->OnDetach();
            m_Layers.erase(it);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* overlay)
    {
        auto it = std::find_if(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(),
            [&](const LayerPtr& element) { return element.get() == overlay; });

        if (it != m_Layers.end())
        {
            overlay->OnDetach();
            m_Layers.erase(it);
        }
    }
}