#pragma once

#include "Framework.h"
#include "Survivors/SurvivorsGameObject.h"

namespace fw
{

	class AnimatedObject : public SurvivorsGameObject
	{
	public:
		AnimatedObject(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader);
		virtual ~AnimatedObject();

		virtual void update(float deltaTime) override;
		virtual void draw(Camera* pCamera) override;

	protected:
		Texture* m_pTexture = nullptr;
		UVTransform* m_pUVTransform = nullptr;
		AnimationCollection* m_pAnimationCollection = nullptr;
		AnimationState* m_pAnimationState = nullptr;
		bool m_isMoving = false;
		std::string name;
	};
}