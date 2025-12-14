#include "Core/CoreHeaders.h"

#include "Mesh.h"
#include "Objects/Camera.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Utility.h"

namespace fw
{
    Mesh::Mesh(GLenum primitiveType, const std::vector<VertexFormat>& verts)
    {
        m_numVerts = (int)verts.size();
        m_primitiveType = primitiveType;

        // Generate a buffer for our vertex attributes.
        glGenBuffers( 1, &m_VBO );

        // Set this VBO to be the currently active one.
        glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

        // Copy our attribute data into the VBO.
        glBufferData( GL_ARRAY_BUFFER, sizeof(VertexFormat)*verts.size(), verts.data(), GL_STATIC_DRAW);
    }

    Mesh::~Mesh()
    {
        glDeleteBuffers( 1, &m_VBO );
    }

    void Mesh::setUniform(ShaderProgram* pShader, const char* name, int v0)
    {
        int location = glGetUniformLocation( pShader->getProgram(), name );
        glUniform1i( location, v0 );
    }

    void Mesh::setUniform(ShaderProgram* pShader, const char* name, float v0)
    {
        int location = glGetUniformLocation( pShader->getProgram(), name );
        glUniform1f( location, v0 );
    }

    void Mesh::setUniform(ShaderProgram* pShader, const char* name, vec2 v)
    {
        int location = glGetUniformLocation( pShader->getProgram(), name );
        glUniform2f( location, v.x, v.y );
    }

    void Mesh::setUniform(ShaderProgram* pShader, const char* name, float v0, float v1, float v2, float v3)
    {
        int location = glGetUniformLocation( pShader->getProgram(), name );
        glUniform4f( location, v0, v1, v2, v3 );
    }

    void Mesh::setUniform(ShaderProgram* pShader, const char* name, color4f color)
    {
        int location = glGetUniformLocation( pShader->getProgram(), name );
        glUniform4f( location, color.r, color.g, color.b, color.a );
    }


    void Mesh::draw(Camera* pCamera, ShaderProgram* pShader, vec2 scale, float angle, vec2 pos, color4f color)
    {
        glUseProgram(pShader->getProgram());

        setUniform(pShader, "u_time", getRunningTime());
        setUniform(pShader, "u_color", color);
        setUniform(pShader, "u_objectScale", scale);
        setUniform(pShader, "u_objectAngle", angle);
        setUniform(pShader, "u_objectPosition", pos);
        setUniform(pShader, "u_cameraPosition", pCamera->getPosition());
        setUniform(pShader, "u_projectionScale", pCamera->getProjectionScale());

        vec2 textureSize = { 256, 128 };
        vec2 spriteSize = { 16, 16 };
        vec2 spritePos = { 68, 78 };

        vec2 uvScale = spriteSize / textureSize;
        vec2 uvOffset = spritePos / textureSize;

        setUniform(pShader, "u_uvScale", uvScale);
        setUniform(pShader, "u_uvOffset", uvOffset);


        // Set this VBO to be the currently active one.
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

        // Get the attribute variable’s location from the shader.
        // The shader part is commented out here, we'll discuss that later.
        // Describe the attributes in the VBO to OpenGL.
        GLint locPos = glGetAttribLocation(pShader->getProgram(), "a_position");
        glEnableVertexAttribArray(locPos);
        glVertexAttribPointer(locPos, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, pos));

        GLint locColor = glGetAttribLocation(pShader->getProgram(), "a_color");
        glEnableVertexAttribArray(locColor);
        glVertexAttribPointer(locColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, color));

        GLint locUV = glGetAttribLocation(pShader->getProgram(), "a_uv");
        glEnableVertexAttribArray(locUV);
        glVertexAttribPointer(locUV, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, uv));

        // Draw the primitive.
        glDrawArrays(m_primitiveType, 0, m_numVerts);
    }

    void Mesh::draw(Camera* pCamera, ShaderProgram* pShader, vec2 scale, float angle, vec2 pos, color4f color, Texture* pTexture, UVTransform* pUvTransform)
    {
        glUseProgram( pShader->getProgram() );

        setUniform( pShader, "u_time", getRunningTime() );
        setUniform( pShader, "u_color", color );
        setUniform( pShader, "u_objectScale", scale );
        setUniform( pShader, "u_objectAngle", angle );
        setUniform( pShader, "u_objectPosition", pos );
        setUniform( pShader, "u_cameraPosition", pCamera->getPosition() );
        setUniform( pShader, "u_projectionScale", pCamera->getProjectionScale() );

        setUniform( pShader, "u_uvScale", pUvTransform->m_uvScale );
        setUniform( pShader, "u_uvOffset", pUvTransform->m_uvOffset );

        if( pTexture )
        {
            int textureUnitIndex = 1;
            glActiveTexture( GL_TEXTURE0 + textureUnitIndex );
            glBindTexture( GL_TEXTURE_2D, pTexture->getTextureID() );
            setUniform( pShader, "u_texture", textureUnitIndex );
        }

        // Set this VBO to be the currently active one.
        glBindBuffer( GL_ARRAY_BUFFER, m_VBO );

        // Get the attribute variable’s location from the shader.
        // The shader part is commented out here, we'll discuss that later.
        // Describe the attributes in the VBO to OpenGL.
        GLint locPos = glGetAttribLocation( pShader->getProgram(), "a_position" );
        glEnableVertexAttribArray( locPos );
        glVertexAttribPointer( locPos, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, pos) );

        GLint locColor = glGetAttribLocation( pShader->getProgram(), "a_color" );
        glEnableVertexAttribArray( locColor );
        glVertexAttribPointer( locColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, color) );

        GLint locUV = glGetAttribLocation( pShader->getProgram(), "a_uv" );
        glEnableVertexAttribArray( locUV );
        glVertexAttribPointer( locUV, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, uv) );

        // Draw the primitive.
        glDrawArrays( m_primitiveType, 0, m_numVerts );
    }
} // namespace fw
