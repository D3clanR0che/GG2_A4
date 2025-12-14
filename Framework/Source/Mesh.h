#pragma once

#include "Core/CoreHeaders.h"
#include "Math/vec2.h"
#include "Types/Color.h"
#include "ResourceManager.h"
#include "Objects/SpriteSheet.h"

namespace fw
{
    class Camera;
    class ShaderProgram;
    class Texture;

    struct VertexFormat
    {
        vec2 pos;
        unsigned char color[4];
        vec2 uv;
    };

    class Mesh : public Resource
    {
    public:
        Mesh(GLenum primitiveType, const std::vector<VertexFormat>& verts);
        virtual ~Mesh();

        static std::string getResourceTypeID() { return "Mesh"; }
       
        void draw(Camera* pCamera, ShaderProgram* pShader, vec2 scale, float angle, vec2 pos, color4f color);
        void draw(Camera* pCamera, ShaderProgram* pShader, vec2 scale, float angle, vec2 pos, color4f color, Texture* pTexture, UVTransform* pUvTransform);

        void setUniform(ShaderProgram* pShader, const char* name, int v0);
        void setUniform(ShaderProgram* pShader, const char* name, float v0);
        void setUniform(ShaderProgram* pShader, const char* name, vec2 v);
        void setUniform(ShaderProgram* pShader, const char* name, float v0, float v1, float v2, float v3);
        void setUniform(ShaderProgram* pShader, const char* name, color4f color);

    protected:
        GLuint m_VBO = 0;
        int m_numVerts = 0;
        GLenum m_primitiveType = GL_POINTS;
    };
} // namespace fw
