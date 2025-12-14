#include "Core/CoreHeaders.h"

#include "Camera.h"

namespace fw
{
	Camera::Camera()
	{
	}

	Camera::Camera(vec2 pos, float aspectRatio, float zoom) :
		m_position(pos),
		m_aspectRatio(aspectRatio),
		m_zoom(zoom)
	{
	}

	Camera::~Camera()
	{
	}

	vec2 Camera::getProjectionScale()
	{
		return vec2(1.0f / (m_zoom * m_aspectRatio), 1.0f / m_zoom);
	}
}