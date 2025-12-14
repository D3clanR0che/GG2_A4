#pragma once

#include "Math/vec2.h"
#include "Types/Color.h"
#include "Types/ColorList.h"
#include "Mesh.h"

namespace fw
{
    class SurvivorsGame;

    class SurvivorsGameObject
    {
    public:
        SurvivorsGameObject(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader);
        virtual ~SurvivorsGameObject();

        virtual void reset();
        virtual void update(float deltaTime);
        virtual void draw(Camera* pCamera);
        virtual bool isCollidingWithGameObject(SurvivorsGameObject* pOtherObject) { return false; }

        // Getters.
        bool isActive() { return m_isActive; }
        vec2 getPosition() { return m_position; }
        float getAngle() { return m_angle; }
        vec2 getScale() { return m_scale; }
        float getRadius() { return m_radius; }
        color4f getColor() { return m_color; }

        // Setters.
        virtual void setActive(bool active) { m_isActive = active; }
        void setPosition(vec2 pos) { m_position = pos; }
        void setAngle(float angle) { m_angle = angle; }
        void setScale(vec2 scale) { m_scale = scale; }
        void setRadius(float radius) { m_radius = radius; }
        void setColor(color4f color) { m_color = color; }

    protected:
        SurvivorsGame* m_pGame = nullptr;

        Mesh* m_pMesh = nullptr;

        ShaderProgram* m_pShader = nullptr;

        bool m_isActive = false;

        vec2 m_position = 0;
        float m_angle = 0;
        vec2 m_scale = 20.0f;
        float m_radius = 0;
        color4f m_color = ColorList::White();
    };
}
