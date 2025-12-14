#include "Core/CoreHeaders.h"
#include <fstream>
#include "../Libraries/nlohmann/json.hpp"

#include "Math/vec2.h"
#include "SpriteSheet.h"

namespace fw
{
    SpriteSheet::SpriteSheet(std::string filename)
    {
        using json = nlohmann::json;

        std::ifstream f(filename);
        json data = json::parse(f);

        int version = data["spritetool"];
        assert(version == 3);
        vec2 texSize = { data["size"][0], data["size"][1] };

        for (const json& sprite : data["sprites"])
        {
            std::string spriteName = sprite["name"];
            vec2 pos = { sprite["pos"][0], sprite["pos"][1] };
            vec2 size = { sprite["size"][0], sprite["size"][1] };

            UVTransform* uvTransform = new UVTransform();
            uvTransform->m_uvScale = size / texSize;
            uvTransform->m_uvOffset = pos / texSize;
            m_sprites[spriteName] = uvTransform;
        }
    }

    UVTransform* SpriteSheet::GetUVTransform(std::string name)
    {
        if (m_sprites.find(name) != m_sprites.end())
        {
            return m_sprites[name];
        }
        else
        {
            return nullptr;
        }
    }
}