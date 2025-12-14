#pragma once

#include "Types/KeyStates.h"

namespace fw
{
    class GameCore
    {
    public:
        GameCore() {}
        virtual ~GameCore() {}

        virtual void onKey(int keyCode, KeyState state) = 0;
        virtual void update(float deltaTime) = 0;
        virtual void draw() = 0;
    };
} // namespace fw
