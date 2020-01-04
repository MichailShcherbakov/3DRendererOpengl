#include "StdAfx.h"
#include "RenderPipeline.h"


#include "boost/filesystem.hpp"

void RenderPipeline::Render(Shader& shader)
{
	for (IRenderListener* it : m_listeners)
		it->Draw(shader);
}

void RenderPipeline::AddListener(IRenderListener* listener)
{
	m_listeners.push_back(listener);
}

void RenderPipeline::RemoveListener(IRenderListener* listener)
{
	m_listeners.erase(std::find(m_listeners.begin(), m_listeners.end(), listener));
}
