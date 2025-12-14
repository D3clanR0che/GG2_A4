#include "Enemy.h"
#include "SurvivorsGame.h"
#include "Player.h"
#include "Tween.h"

namespace fw
{
    const float Enemy::c_startingHealth = 1.0f;
    const float Enemy::c_speed = 90.0f;
    const float Enemy::c_animSpeed = 0.3f;

    Enemy::Enemy(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader): 
        AnimatedObject(pGame, pMesh, pShader), 
        m_tweenSize(m_visibleScale)
    {
        m_radius = 20.0f;

        m_scale = 40.0f;

        m_isMoving = true;
    }

    Enemy::~Enemy()
    {

    }

    void Enemy::update(float deltaTime)
    {
        AnimatedObject::update(deltaTime);

        m_tweenSize.update(deltaTime);

        // Deactivate when tween is finished.
        if (m_isFadingOut == true && m_tweenSize.isRunning() == false)
        {
            m_isActive = false;
            return;
        }

        // Update animation.
        m_animTimer += deltaTime;

        if (m_animTimer > 2)
        {
            m_animTimer = 0;
        }

    }

    void Enemy::startDeathAnim()
    {
        m_health = 0.0f;
        m_visibleScale = 1.0f;
        m_isFadingOut = true;

        m_tweenSize.start(0.0f, 0.5f, 0.0f, easingLinear);
    }

    void Enemy::applyDamage(float damage)
    {
        m_health -= damage;
        if (m_health <= 0)
        {
            startDeathAnim();
            m_pGame->onEnemyKilled(m_position);
        }
    }

    void Enemy::setActive(bool active)
    {
        SurvivorsGameObject::setActive(active);

        if (m_isActive == true)
        {
            m_tweenSize.start(1.0f, 1.5f, 0.0f, easingOutElastic);
        }
    }
}
