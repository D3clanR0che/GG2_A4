#pragma once

#include "Core/CoreHeaders.h"
#include "Objects/SpriteSheet.h"
#include "Animation/Animation.h"

namespace fw
{
	class Animation;
	class Texture;

	class AnimationState
	{
	public:
		AnimationState();

		void update(float deltaTime);

		void setAnimation(Animation* animation);

		UVTransform* GetUVTransform() { return m_pAnimation->GetUVTransform(m_currentFrame); }

		Texture* GetTexture() { return m_pAnimation->GetTexture(); }

	private:
		Animation* m_pAnimation;
		int m_currentFrame;
		float m_timeElapsed;
	};
}