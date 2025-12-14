#pragma once

#include "AnimatedObject.h"

namespace fw
{
	class Sprite;

	class Player : public AnimatedObject
	{
	private:
		static const float c_speed; // Pixels per second.
		static const float c_pickupRadius; // Pixels.
		static const float c_startingHealth;
		static const ivec2 c_mapSize;

	public:
		Player(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader);
		virtual ~Player();

		virtual void update(float deltaTime) override;

		// Input event methods.

		void onKey(int keyCode, KeyState keyState);
		//void onMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY);
		//void onMouseMovedEvent(float mouseX, float mouseY);

		void handleCollision(vec2 collisionPoint, vec2 collisionNormal);

		float setHealth() { return m_health = c_startingHealth; }

		// Getters.

		float getHealth() { return m_health; }
		float& getHealthAddress() { return m_health; }
		float& getMaxHealthAddress() { return m_maxHealth; }
		float getPickupRadius() { return m_pickupRadius; }
		bool isMoving();
		void damagePlayer() { m_health -= 10.0f; }

	private:
		float m_health = 0;
		float m_maxHealth = 0;
		float m_pickupRadius = 0;
		vec2 m_controls = { 0, 0 };
	};
}

