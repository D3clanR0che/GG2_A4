#pragma once
#include "Core/CoreHeaders.h"
#include "ResourceManager.h"
#include "Objects/SpriteSheet.h"

namespace fw
{
	class Texture;

	class Animation : public Resource
	{

	public:
		Animation(Texture* pTexture, float frameDuration);

		static std::string getResourceTypeID() { return "Animation"; }

		void addUVTransform(UVTransform* pUVTransform) { m_animationVector.push_back(pUVTransform); }

		UVTransform* GetUVTransform(int index);

		Texture* GetTexture() { return m_pTexture; }

		float GetFrameDuration() { return m_frameDuration; }

	private:
		Texture* m_pTexture;
		float m_frameDuration;
		std::vector<UVTransform*> m_animationVector;
	};
}