#include "Core/CoreHeaders.h"

#include "Animation/AnimationCollection.h"

namespace fw
{
	AnimationCollection::AnimationCollection()
	{
	}
	void AnimationCollection::addAnimation(std::string name, Animation* pAnimation)
	{
		assert(m_animations.count(name) == 0);
		m_animations[name] = pAnimation;
	}
	Animation* AnimationCollection::getAnimation(std::string name)
	{
		assert(m_animations.count(name) == 1);
		return m_animations[name];
	}
}