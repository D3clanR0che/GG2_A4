#include "Core/CoreHeaders.h"
#include "Animation/AnimationState.h"

namespace fw
{
	AnimationState::AnimationState() :
		m_pAnimation(nullptr),
		m_currentFrame(0),
		m_timeElapsed(0.0f)
	{
	}
	void AnimationState::update(float deltaTime)
	{
		m_timeElapsed += deltaTime;

		if (m_timeElapsed >= m_pAnimation->GetFrameDuration())
		{
			m_currentFrame++;
			m_timeElapsed = 0.0f;
		}
	}

	void AnimationState::setAnimation(Animation* animation)
	{
		m_currentFrame = 0;
		m_timeElapsed = 0.0f;
		m_pAnimation = animation;
	}
}