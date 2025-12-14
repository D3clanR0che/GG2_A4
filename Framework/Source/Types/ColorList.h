#pragma once

#include "Framework.h"
#include "Color.h"

namespace fw
{
    namespace ColorList
    {
        // Hex to RGB 0-1 https://rgbcolorpicker.com/0-1

     //Standard colors

        static const color4f Clear() { return color4f(0.0f, 0.0f, 0.0f, 0.0f); };
        static const color4f White() { return color4f(1.0f, 1.0f, 1.0f, 1.0f); };
        static const color4f Black() { return color4f(0.0f, 0.0f, 0.0f, 1.0f); };
        static const color4f Red() { return color4f(1.0f, 0.0f, 0.0f, 1.0f); };
        static const color4f Green() { return color4f(0.0f, 1.0f, 0.0f, 1.0f); };
        static const color4f Blue() { return color4f(0.0f, 0.0f, 1.0f, 1.0f); };

        // White colors

        static const color4f Snow() { return color4f(1.0f, 0.98f, 0.98f, 1.0f); };
        static const color4f Azure() { return color4f(0.941f, 1.0f, 1.0f, 1.0f); };
        static const color4f Ivory() { return color4f(1.0f, 1.0f, 0.941f, 1.0f); };
        static const color4f GhostWhite() { return color4f(0.973f, 0.973f, 1.0f, 1.0f); };
        static const color4f Mint() { return color4f(0.961f, 1.0f, 0.98f, 1.0f); };
        static const color4f Beige() { return color4f(0.961f, 0.961f, 0.863f, 1.0f); };

        //Black colors

        static const color4f Onxy() { return color4f(0.208f, 0.22f, 0.224f, 1.0f); };
        static const color4f Charcoal() { return color4f(0.212f, 0.271f, 0.31f, 1.0f); };
        static const color4f Licorice() { return color4f(0.102f, 0.067f, 0.063f, 1.0f); };

        //Grey colors

        static const color4f Silver() { return color4f(0.753f, 0.753f, 0.753f, 1.0f); };
        static const color4f Grey() { return color4f(0.502f, 0.502f, 0.502f, 1.0f); };
        static const color4f LightGrey() { return color4f(0.827f, 0.827f, 0.827f, 1.0f); };
        static const color4f DarkGrey() { return color4f(0.663f, 0.663f, 0.663f, 1.0f); };
        static const color4f SlateGrey() { return color4f(0.439f, 0.502f, 0.565f, 1.0f); };

        //Oragne colors

        static const color4f Orange() { return color4f(1.0f, 0.647f, 0.0f, 1.0f); };
        static const color4f DarkOrange() { return color4f(1.0f, 0.549f, 0.0f, 1.0f); };
        static const color4f OrangeRed() { return color4f(1.0f, 0.271f, 0.0f, 1.0f); };
        static const color4f Coral() { return color4f(1.0f, 0.498f, 0.314f, 1.0f); };
        static const color4f LightSalmon() { return color4f(1.0f, 0.627f, 0.478f, 1.0f); };
        static const color4f Tomato() { return color4f(1.0f, 0.271f, 0.0f, 1.0f); };

        //Yellow colors

        static const color4f Yellow() { return color4f(1.0f, 1.0f, 0, 1.0f); };
        static const color4f LightYellow() { return color4f(1.0f, 1.0f, 0.878f, 1.0f); };
        static const color4f LemonChiffon() { return color4f(1.0f, 0.98f, 0.804f, 1.0f); };
        static const color4f Gold() { return color4f(1.0f, 0.843f, 0.0f, 1.0f); };
        static const color4f Peachpuff() { return color4f(1.0f, 0.855f, 0.725f, 1.0f); };
        static const color4f Khaki() { return color4f(0.941f, 0.902f, 0.549f, 1.0f); };
        static const color4f DarkKhaki() { return color4f(0.741f, 0.718f, 0.42f, 1.0f); };

        //Red colors

        static const color4f DarkRed() { return color4f(0.545f, 0.0f, 0.0f, 1.0f); };
        static const color4f Crimson() { return color4f(0.863f, 0.078f, 0.235f, 1.0f); };
        static const color4f FireBrick() { return color4f(0.698f, 0.133f, 0.133f, 1.0f); };
        static const color4f LightCoral() { return color4f(0.941f, 0.502f, 0.502f, 1.0f); };
        static const color4f Salmon() { return color4f(0.98f, 0.502f, 0.447f, 1.0f); };
        static const color4f DarkSalmon() { return color4f(0.914f, 0.588f, 0.478f, 1.0f); };

        //Green colors

        static const color4f LightGreen() { return color4f(0.565f, 0.933f, 0.565f, 1.0f); };
        static const color4f DarkGreen() { return color4f(0.0f, 0.392f, 0.0f, 1.0f); };
        static const color4f YellowGreen() { return color4f(0.604f, 0.804f, 0.196f, 1.0f); };
        static const color4f ForestGreen() { return color4f(0.133f, 0.545f, 0.133f, 1.0f); };
        static const color4f OliveGreen() { return color4f(0.502f, 0.502f, 0.0f, 1.0f); };
        static const color4f PaleGreen() { return color4f(0.596f, 0.984f, 0.596f, 1.0f); };
        static const color4f LimeGreen() { return color4f(0.196f, 0.804f, 0.196f, 1.0f); };
        static const color4f Teal() { return color4f(0.0f, 0.502f, 0.502f, 1.0f); };

        //Blue colors

        static const color4f Cyan() { return color4f(0.0f, 1.0f, 1.0f, 1.0f); };
        static const color4f LightBlue() { return color4f(0.678f, 0.847f, 0.902f, 1.0f); };
        static const color4f DarkBlue() { return color4f(0.0f, 0.0f, 0.545f, 1.0f); };
        static const color4f CornflowerBlue() { return color4f(0.392f, 0.584f, 0.929f, 1.0f); };
        static const color4f MidnightBlue() { return color4f(0.098f, 0.098f, 0.439f, 1.0f); };
        static const color4f Navy() { return color4f(0.0f, 0.0f, 0.502f, 1.0f); };
        static const color4f PowderBlue() { return color4f(0.69f, 0.878f, 0.902f, 1.0f); };
        static const color4f RoyalBlue() { return color4f(0.255f, 0.412f, 0.882f, 1.0f); };
        static const color4f SkyBlue() { return color4f(0.529f, 0.808f, 0.922f, 1.0f); };
        static const color4f SteelBlue() { return color4f(0.275f, 0.51f, 0.706f, 1.0f); };

        //Brown colors

        static const color4f Brown() { return color4f(0.588f, 0.294f, 0.0f, 1.0f); };
        static const color4f SandyBrown() { return color4f(0.957f, 0.643f, 0.376f, 1.0f); };
        static const color4f Tan() { return color4f(0.824f, 0.706f, 0.549f, 1.0f); };
        static const color4f Chocolate() { return color4f(0.824f, 0.412f, 0.118f, 1.0f); };
        static const color4f Sienna() { return color4f(0.627f, 0.322f, 0.176f, 1.0f); };

        //Purple colors

        static const color4f Purple() { return color4f(0.502f, 0.0f, 0.502f, 1.0f); };
        static const color4f MediumPurple() { return color4f(0.576f, 0.439f, 0.859f, 1.0f); };
        static const color4f Magenta() { return color4f(1.0f, 0.0f, 1.0f, 1.0f); };
        static const color4f DarkMagenta() { return color4f(0.545f, 0.0f, 0.545f, 1.0f); };
        static const color4f Indigo() { return color4f(0.294f, 0.0f, 0.51f, 1.0f); };
        static const color4f Violet() { return color4f(0.933f, 0.51f, 0.933f, 1.0f); };
        static const color4f Plum() { return color4f(0.867f, 0.627f, 0.867f, 1.0f); };
        static const color4f Lavender() { return color4f(0.902f, 0.902f, 0.98f, 1.0f); };

        //Pink colors

        static const color4f Pink() { return color4f(1.0f, 0.753f, 0.796f, 1.0f); };
        static const color4f LightPink() { return color4f(1.0f, 0.714f, 0.757f, 1.0f); };
        static const color4f HotPink() { return color4f(1.0f, 0.412f, 0.706f, 1.0f); };
        static const color4f DeepPink() { return color4f(1.0f, 0.078f, 0.576f, 1.0f); };
    }
}