#include "Slime.h"
#include "SurvivorsGame.h"
#include "Player.h"
#include "Tween.h"

namespace fw
{
	const float Slime::c_startingHealth = 1100.0f;
	const float Slime::c_speed = 90.0f;
	const float Slime::c_animSpeed = 0.3f;

	Slime::Slime(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader) :
		Enemy(pGame, pMesh, pShader)
	{
		m_radius = 20.0f;

		m_scale = 40.0f;

		m_health = c_startingHealth;

		m_color = Red();

		m_pAnimationCollection = pGame->GetManager()->get<AnimationCollection>("slime");
		m_pAnimationState->setAnimation(m_pAnimationCollection->getAnimation("Idle"));
	}

	Slime::~Slime()
	{

	}

	void Slime::update(float deltaTime)
	{
		Enemy::update(deltaTime);

		m_movementTimer += deltaTime;

		if (m_movementTimer > 1.0f)
		{
			// Move toward player.

			m_isMoving = true;

			vec2 dir = m_pGame->getPlayer()->getPosition() - m_position;
			dir.normalize();

			vec2 velocity = dir * c_speed;
			m_position += velocity * deltaTime;
		}
		if (m_movementTimer > 2.0f)
		{
			m_isMoving = false;

			m_movementTimer = 0.0f;
		}
	}

	void Slime::setActive(bool active)
	{
		Enemy::setActive(active);

		m_visibleScale = 0.0f;
		m_isFadingOut = false;
		m_health = c_startingHealth;
	}
}
