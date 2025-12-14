#include "Animation.h"

namespace fw
{
	Animation::Animation(Texture* pTexture, float frameDuration) :
		m_pTexture(pTexture),
		m_frameDuration(frameDuration)
	{
	}

	UVTransform* fw::Animation::GetUVTransform(int index)
	{
		if (index >= 0)
		{
			return m_animationVector[index % m_animationVector.size()];
		}
		else
		{
			return nullptr;
		}
	}
}