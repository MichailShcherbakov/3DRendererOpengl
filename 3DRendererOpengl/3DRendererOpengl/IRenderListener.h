#ifndef _I_RENDER_LISTENER_H_
#define _I_RENDER_LISTENER_H_

#include "Shader.h"

struct MouseEvent
{
	void Accept()
	{
		m_isAccepted = true;
	}

	bool IsAccepted() const
	{
		return m_isAccepted;
	}

private:
	bool m_isAccepted = false;
};

struct KeyEvent
{

	void Accept()
	{
		m_isAccepted = true;
	}

	bool IsAccepted() const
	{
		return m_isAccepted;
	}

private:
	bool m_isAccepted = false;
};

struct IRenderListener
{
	IRenderListener() { this->count++; this->objectID = this->count; }
	virtual ~IRenderListener() {}

	virtual void Draw(Shader& shader) = 0;
	virtual void MousePressEvent(MouseEvent* event) = 0;
	virtual void MouseReleaseEvent(MouseEvent* event) = 0;
	virtual void MouseMoveEvent(MouseEvent* event) = 0;
	virtual void KeyPressEvent(KeyEvent* event) = 0;
	virtual void KeyReleaseEvent(KeyEvent* event) = 0;

	static size_t count;
	size_t objectID = 0;
};

#endif // _I_RENDER_LISTENER_H_
