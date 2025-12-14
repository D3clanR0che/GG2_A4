#pragma once

#include "Tween.h"
#include "Types/Color.h"
#include "SurvivorsGameObject.h"

namespace fw
{
    class Pickup : public SurvivorsGameObject
    {
    private:
        static const float c_size; // Pixels.
        static const color4f c_color;

    public:
        Pickup(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader);
        virtual ~Pickup();

        virtual void update(float deltaTime) override;

        void pickupObject(vec2 destPos);
        bool isAnimating() { return m_animating; }

        // Getters.

        // Setters.

    private:
        bool m_animating = false;

        Tween m_tweenPosX;
        Tween m_tweenPosY;
    };
}
