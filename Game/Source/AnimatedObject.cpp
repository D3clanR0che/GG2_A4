#include "AnimatedObject.h"

fw::AnimatedObject::AnimatedObject(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader) :
	SurvivorsGameObject(pGame, pMesh, pShader),
	m_pTexture(nullptr),
	m_pUVTransform(nullptr),
	m_pAnimationCollection(nullptr),
	m_isMoving(false)
{
	m_pAnimationState = new AnimationState(); 
}

fw::AnimatedObject::~AnimatedObject()
{
	delete m_pAnimationState;
}

void fw::AnimatedObject::update(float deltaTime)
{
	if (m_isMoving && name != "Moving")
	{
		name = "Moving";
		m_pAnimationState->setAnimation(m_pAnimationCollection->getAnimation("Moving"));
	}
	else if (!m_isMoving && name != "Idle")
	{
		name = "Idle";
		m_pAnimationState->setAnimation(m_pAnimationCollection->getAnimation("Idle"));
	}

	m_pAnimationState->update(deltaTime);
}

void fw::AnimatedObject::draw(Camera* pCamera)
{
	m_pTexture = m_pAnimationState->GetTexture();
	m_pUVTransform = m_pAnimationState->GetUVTransform();

	m_pMesh->draw(pCamera, m_pShader, m_scale, m_angle, m_position, m_color, m_pTexture, m_pUVTransform);
}
