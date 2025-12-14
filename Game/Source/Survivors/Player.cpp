#include "SurvivorsGame.h"
#include "Player.h"

namespace fw
{
	const float Player::c_speed = 150.0f; // Pixels per second.
	const float Player::c_pickupRadius = 100.0f; // Pixels.
	const float Player::c_startingHealth = 100.0f;
	const ivec2 Player::c_mapSize = { 100, 50 };

	Player::Player(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader) :
		AnimatedObject(pGame, pMesh, pShader),
		m_pickupRadius(c_pickupRadius),
		m_health(c_startingHealth),
		m_maxHealth(c_startingHealth)
	{
		m_isActive = true;

		m_radius = 20.0f;

		m_scale = 40.0f;

		m_color = Black();

		m_pAnimationCollection = pGame->GetManager()->get<AnimationCollection>("player");
		m_pAnimationState->setAnimation(m_pAnimationCollection->getAnimation("Idle"));

	}

	Player::~Player()
	{

	}

	void Player::update(float deltaTime)
	{
		AnimatedObject::update(deltaTime);

		vec2 dir = m_controls.getNormalized();

		m_position += dir * c_speed * deltaTime;


		// Lock to edges.
		if (m_position.x < m_radius)
			m_position.x = m_radius;

		if (m_position.x >= m_pGame->getMapSize().x * m_pGame->getTileSize().x - m_radius)
			m_position.x = m_pGame->getMapSize().x * m_pGame->getTileSize().x - m_radius;

		if (m_position.y < m_radius)
			m_position.y = m_radius;

		if (m_position.y >= m_pGame->getMapSize().y * m_pGame->getTileSize().y - m_radius)
			m_position.y = m_pGame->getMapSize().y * m_pGame->getTileSize().y - m_radius;

		if (m_controls.x == 0 && m_controls.y == 0)
		{
			m_isMoving = false;
		}
		else
		{
			m_isMoving = true;
		}
	}

	void Player::onKey(int keyCode, KeyState keyState)
	{
		if (keyState == KeyState::Pressed)
		{
			if (keyCode == 'A')
				m_controls.x = -1;
			if (keyCode == 'D')
				m_controls.x = 1;
			if (keyCode == 'S')
				m_controls.y = -1;
			if (keyCode == 'W')
				m_controls.y = 1;
		}

		if (keyState == KeyState::Released)
		{
			if (keyCode == 'A')
				m_controls.x = 0;
			if (keyCode == 'D')
				m_controls.x = 0;
			if (keyCode == 'S')
				m_controls.y = 0;
			if (keyCode == 'W')
				m_controls.y = 0;
		}
	}

	void Player::handleCollision(vec2 collisionPoint, vec2 collisionNormal)
	{
	}

	bool Player::isMoving()
	{
		if (m_controls.x == 0 && m_controls.y == 0)
		{
			return false;
		}

		return true;
	}
}

