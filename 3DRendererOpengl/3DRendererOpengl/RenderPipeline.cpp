#include "StdAfx.h"
#include "RenderPipeline.h"


#include "boost/filesystem.hpp"

void RenderPipeline::Draw(Shader& shader)
{
	for (IRenderListener* listener : m_listeners)
		listener->Draw(shader);
}

void RenderPipeline::MousePressEvent(MouseEvent* event, uint32_t objectID)
{
	auto obj = std::find_if(m_listeners.begin(), m_listeners.end(), [=](IRenderListener* listener) {
		return listener->objectID == objectID;
		});

	if (obj != m_listeners.end())
		(*obj)->MousePressEvent(event);
}

void RenderPipeline::MouseReleaseEvent(MouseEvent* event, uint32_t objectID)
{
	auto obj = std::find_if(m_listeners.begin(), m_listeners.end(), [=](IRenderListener* listener) {
		return listener->objectID == objectID;
		});

	if (obj != m_listeners.end())
		(*obj)->MouseReleaseEvent(event);
}

void RenderPipeline::MouseMoveEvent(MouseEvent* event, uint32_t objectID)
{
	auto obj = std::find_if(m_listeners.begin(), m_listeners.end(), [=](IRenderListener* listener) {
		return listener->objectID == objectID;
		});

	if (obj != m_listeners.end())
		(*obj)->MouseMoveEvent(event);
}

void RenderPipeline::KeyPressEvent(KeyEvent* event)
{
	for (IRenderListener* listener : m_listeners)
	{
		listener->KeyPressEvent(event);

		if (event->IsAccepted())
			break;
	}
}

void RenderPipeline::KeyReleaseEvent(KeyEvent* event)
{
	for (IRenderListener* listener : m_listeners)
	{
		listener->KeyReleaseEvent(event);

		if (event->IsAccepted())
			break;
	}
}

void RenderPipeline::AddListener(IRenderListener* listener)
{
	m_listeners.push_back(listener);
}

void RenderPipeline::RemoveListener(IRenderListener* listener)
{
	m_listeners.erase(std::find(m_listeners.begin(), m_listeners.end(), listener));
}
