#pragma once
#include "Framework.h"

namespace fw
{
    class ProgressBar
    {
    private:


    public:
        ProgressBar(Mesh* pMesh, ShaderProgram* pShader, vec2 pos, vec2 scale, float angle, color4f firstColor, color4f secondColor, float& current, float& max);
        virtual ~ProgressBar();

        void draw(Camera* pCamera);

    private:
        float& m_referenceCurrent;
        float& m_referenceMax;
        Mesh* m_pMesh;
        ShaderProgram* m_pShader;
        vec2 m_position;
        vec2 m_scale;
        float m_angle;
        color4f m_firstColor;
        color4f m_secondColor;
    };
}
