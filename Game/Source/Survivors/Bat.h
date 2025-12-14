#pragma once

#include "Enemy.h"
#include "Tween.h"

namespace fw
{
    class Bat : public Enemy
    {
    private:
        static const float c_startingHealth;
        static const float c_speed;
        static const float c_animSpeed;

    public:
        Bat(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader);
        virtual ~Bat();

        virtual void update(float deltaTime) override;

        //Setters
        void setActive(bool active) override;
    };
}
