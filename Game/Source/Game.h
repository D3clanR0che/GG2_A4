#pragma once

#include "Framework.h"
#include "GameTypes.h"

class Game : public fw::GameCore
{
public:
    Game();
    virtual ~Game();

    virtual void onKey(int keyCode, fw::KeyState state) override;
    virtual void update(float deltaTime) override;
    virtual void draw() override;

public:
    fw::ShaderProgram* m_pBasicShader = nullptr;

    std::map<std::string, fw::Mesh*> m_meshes;

    fw::Camera* m_pCamera = nullptr;

    vec2 m_controls = vec2(0, 0);
    vec2 m_position = vec2(0, 0);
    float m_angle = 0.0f;
};