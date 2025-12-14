#include "Framework.h"
#include "Game.h"
#include "GameTypes.h"
#include "GameObject.h"

Game::Game()
{
    std::vector<fw::VertexFormat> trianglePoints = { {vec2(-0.5f, -0.5f)}, {vec2(0.5f, -0.5f)}, {vec2(0.0f, 0.5f)} };
    std::vector<fw::VertexFormat> boxPoints = { {vec2(-0.5f, -0.5f)}, {vec2(0.5f, -0.5f)}, {vec2(0.5f, 0.5f)}, {vec2(-0.5f,0.5f)} };
    std::vector<fw::VertexFormat> diamondPoints = { {vec2(0.0f,-0.5f)}, {vec2(0.5f,0.0f)}, {vec2(0.0f,0.5f)}, {vec2(-0.5f,0.0f)} };

    m_pBasicShader = new fw::ShaderProgram("Data/Basics/basic.vert", "Data/Basics/basic.frag");
    m_meshes["triangle"] = new fw::Mesh(GL_TRIANGLES, trianglePoints);
    m_meshes["box"] = new fw::Mesh(GL_LINES, boxPoints);
    m_meshes["diamond"] = new fw::Mesh(GL_LINES, diamondPoints);

    float aspectRatio = 16.0f / 9.0f;

    m_pCamera = new fw::Camera(vec2(640, 360), aspectRatio, 360.0f);

    m_position = vec2(300, 300);

}

Game::~Game()
{
    for (const auto& pair : m_meshes)
    {
        delete pair.second;
    }

    delete m_pCamera;
}

void Game::onKey(int keyCode, fw::KeyState state)
{
    if (state == fw::KeyState::Pressed)
    {
        switch (keyCode)
        {
        case 'W': m_controls.y++; break;
        case 'S': m_controls.y--; break;
        case 'A': m_controls.x--; break;
        case 'D': m_controls.x++; break;
        }
    }
    else if (state == fw::KeyState::Released)
    {
        switch (keyCode)
        {
        case 'W': m_controls.y--; break;
        case 'S': m_controls.y++; break;
        case 'A': m_controls.x++; break;
        case 'D': m_controls.x--; break;
        }
    }
}

void Game::update(float deltaTime)
{
    float speed = 200.0f; // 200 units per second
    float rotationSpeed = 3.0f; // 3 radians per second

    vec2 dir = vec2(cosf(m_angle), sinf(m_angle));

    m_position += dir * speed * m_controls.y * deltaTime;
    m_angle += -m_controls.x * 2.0f * deltaTime;
}

void Game::draw()
{
    glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    m_meshes["triangle"]->draw(m_pCamera, m_pBasicShader, 100, m_angle, m_position, Yellow());
    m_meshes["box"]->draw(m_pCamera, m_pBasicShader, 300, 0, vec2(640, 360), Cyan());
}