#pragma once

#include "AnimatedObject.h"
#include "Tween.h"

namespace fw
{
    class Mesh;

    class Enemy : public AnimatedObject
    {
    private:
        static const float c_startingHealth;
        static const float c_speed;
        static const float c_animSpeed;

    public:
        Enemy(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader);
        virtual ~Enemy();

        virtual void update(float deltaTime) override;

        void startDeathAnim();
        bool isFadingOut() { return m_isFadingOut; }

        // Getters.
        float getHealth() { return m_health; }

        // Setters.
        void applyDamage(float damage);
        void setHealth(float health) { m_health = health; }
        void setActive(bool active) override;

    protected:
        float m_health = 0.0f;

        float m_animTimer = 0;
        int m_currentFrame = 0;

        bool m_isFadingOut = false;

        float m_visibleScale = 0.0f;

        Tween m_tweenSize;
    };
}

