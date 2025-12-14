#pragma once

#include "Math/vec2.h"
#include "ResourceManager.h"

namespace fw
{
    struct UVTransform
    {
        vec2 m_uvScale = 1;
        vec2 m_uvOffset = 0;
    };

    class SpriteSheet : public Resource
    {
    public:
        SpriteSheet(std::string filename);

        static std::string getResourceTypeID() { return "SpriteSheet"; }

        UVTransform* GetUVTransform(std::string name);

    protected:
        std::unordered_map<std::string, UVTransform*> m_sprites;
    };
}
