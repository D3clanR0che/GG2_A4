#include "SurvivorsGame.h"
#include "Types/Color.h"
#include "Pickup.h"
#include "Player.h"

namespace fw
{
    const float Pickup::c_size = 10.0f; // Pixels.
    const color4f Pickup::c_color = Blue();

    Pickup::Pickup(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader)
        : SurvivorsGameObject(pGame, pMesh, pShader)
        , m_tweenPosX(m_position.x)
        , m_tweenPosY(m_position.y)
    {
        m_isActive = false;

        m_position.set(0, 0);
        m_radius = c_size;

        m_color = c_color;

        m_scale = c_size;
    }

    Pickup::~Pickup()
    {
    }

    void Pickup::update(float deltaTime)
    {
        m_tweenPosX.changeTarget(m_pGame->getPlayer()->getPosition().x);
        m_tweenPosY.changeTarget(m_pGame->getPlayer()->getPosition().y);

        m_tweenPosX.update(deltaTime);
        m_tweenPosY.update(deltaTime);

        if (m_animating && m_tweenPosX.isRunning() == false && m_tweenPosY.isRunning() == false)
        {
            m_animating = false;
            setActive(false);
        }
    }

    void Pickup::pickupObject(vec2 destPos)
    {
        m_animating = true;

        m_tweenPosX.start(destPos.x, 0.5f, 0.0f, easingInBack);
        m_tweenPosY.start(destPos.y, 0.5f, 0.0f, easingInBack);
    }
}
