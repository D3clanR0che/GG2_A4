#pragma once

#include "Tween.h"
#include "Enemy.h"

namespace fw
{
    class Sprite;

    class Slime : public Enemy
    {
    private:
        static const float c_startingHealth;
        static const float c_speed;
        static const float c_animSpeed;

    public:
        Slime(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader);
        virtual ~Slime();

        virtual void update(float deltaTime) override;

        //Setters
        void setActive(bool active) override;

    private:
        float m_movementTimer = 0.0f;
    };
}
