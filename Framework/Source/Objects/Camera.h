#pragma once

#include "Core/CoreHeaders.h"
#include "Math/vec2.h"

namespace fw
{
    class ShaderProgram;

    class Camera
    {
    public:
        Camera();
        Camera(vec2 pos, float aspectRatio, float zoom);
        virtual ~Camera();

        vec2 getPosition() { return m_position; }
        vec2 getProjectionScale();

        void setPosition(vec2 pos) { m_position = pos; }
        void setAspectRatio(float aspectRatio) { m_aspectRatio = aspectRatio; }
        void setZoom(float zoom) { m_zoom = zoom; }

    protected:
        vec2 m_position;
        float m_aspectRatio = 1;
        float m_zoom = 1;
    };
}
