#pragma once

#include "ResourceManager.h"

namespace fw
{
    class Texture : public Resource
    {
    public:
        Texture();
        Texture(const char* filename);
        virtual ~Texture();

        static std::string getResourceTypeID() { return "Texture"; }

        GLuint getTextureID() { return m_textureID; }

    protected:
        void create(void* pixels, int w, int h);

        GLuint m_textureID = 0;
    };
} // namespace fw
