#include "Bat.h"
#include "SurvivorsGame.h"
#include "Player.h"
#include "Tween.h"

namespace fw
{
    const float Bat::c_startingHealth = 200.0f;
    const float Bat::c_speed = 90.0f;
    const float Bat::c_animSpeed = 0.3f;

    Bat::Bat(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader)
        : Enemy(pGame, pMesh, pShader)
    {
        m_radius = 20.0f;

        m_scale = 40.0f;

        m_health = c_startingHealth;

        m_color = Red();

        m_pAnimationCollection = pGame->GetManager()->get<AnimationCollection>("bat");
        m_pAnimationState->setAnimation(m_pAnimationCollection->getAnimation("Idle"));
    }

    Bat::~Bat()
    {

    }

    void Bat::update(float deltaTime)
    {
        Enemy::update(deltaTime);

        // Move toward player.
        vec2 dir = m_pGame->getPlayer()->getPosition() - m_position;
        dir.normalize();

        vec2 velocity = dir * c_speed;
        m_position += velocity * deltaTime;

    }

    void Bat::setActive(bool active)
    {
        Enemy::setActive(active);

        m_visibleScale = 0.0f;
        m_isFadingOut = false;
        m_health = c_startingHealth;

    }
}
