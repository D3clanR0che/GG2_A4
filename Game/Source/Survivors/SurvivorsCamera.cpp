#include "Framework.h"
#include "SurvivorsCamera.h"

namespace fw
{
	SurvivorsCamera::SurvivorsCamera(vec2 pos, float aspectRatio, float zoom): 
		Camera(pos, aspectRatio, zoom)
	{
		m_targetZoom = m_zoom;
	}
	
	SurvivorsCamera::~SurvivorsCamera()
	{
	}

	void SurvivorsCamera::update(float deltaTime)
	{
		if (m_zoom < m_targetZoom)
		{
			m_zoom += 100.0f * deltaTime;

			if (m_zoom > m_targetZoom)
			{
				m_zoom = m_targetZoom;
			}
		}
		else if (m_zoom > m_targetZoom)
		{
			m_zoom -= 100.0f * deltaTime;

			if (m_zoom < m_targetZoom)
			{
				m_zoom = m_targetZoom;
			}
		}
	}
}
