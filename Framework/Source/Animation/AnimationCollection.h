#pragma once

#include "ResourceManager.h"

namespace fw
{
	class Animation;

	class AnimationCollection : public Resource
	{
	public:
		AnimationCollection();

		void addAnimation(std::string name, Animation* pAnimation);

		static std::string getResourceTypeID() { return "AnimationCollection"; }

		Animation* getAnimation(std::string name);

	private:
		std::unordered_map<std::string, Animation*> m_animations;
	};
}