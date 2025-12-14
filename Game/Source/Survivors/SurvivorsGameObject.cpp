#include "SurvivorsGameObject.h"

namespace fw
{
    SurvivorsGameObject::SurvivorsGameObject(SurvivorsGame* pGame, Mesh* pMesh, ShaderProgram* pShader) :
        m_pGame(pGame),
        m_pMesh(pMesh),
        m_pShader(pShader)
    {
    }

    SurvivorsGameObject::~SurvivorsGameObject()
    {
    }

    void SurvivorsGameObject::reset()
    {
        setActive(false);
    }

    void SurvivorsGameObject::update(float deltaTime)
    {
    }

    void SurvivorsGameObject::draw(Camera* pCamera)
    {
        m_pMesh->draw(pCamera, m_pShader, m_scale, m_angle, m_position, m_color);
    }

}