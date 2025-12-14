#include "Framework.h"
#include "ProgressBar.h"

namespace fw
{
	ProgressBar::ProgressBar(Mesh* pMesh, ShaderProgram* pShader, vec2 pos, vec2 scale, float angle, color4f color1, color4f color2, float& current, float& max) : 
		m_pMesh(pMesh), 
		m_pShader(pShader), 
		m_position(pos), 
		m_scale(scale), 
		m_angle(angle), 
		m_firstColor(color1), 
		m_secondColor(color2), 
		m_referenceCurrent(current), 
		m_referenceMax(max)
	{
	}

	ProgressBar::~ProgressBar()
	{
	}

	void ProgressBar::draw(Camera* pCamera)
	{
		m_pMesh->draw(pCamera, m_pShader, m_scale, m_angle, m_position, m_firstColor);
		m_pMesh->draw(pCamera, m_pShader, m_scale * vec2(m_referenceCurrent / m_referenceMax, 1.0f), m_angle, m_position, m_secondColor);
	}
}
