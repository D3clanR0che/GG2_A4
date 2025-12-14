#pragma once
#include "math.h"

namespace fw
{
    class ivec2
    {
    public:
        ivec2() {}
        ivec2(int nx, int ny) : x(nx), y(ny) {}

    public:
        int x;
        int y;
    };

    class vec2
    {
    public:
        vec2() {}
        vec2(float nxy) : x(nxy), y(nxy) {}
        vec2(float nx, float ny) : x(nx), y(ny) {}

        void set(float nx, float ny) { x = nx; y = ny; }

        vec2 operator+(vec2 o) const { return vec2( x + o.x, y + o.y ); }
        vec2 operator-(vec2 o) const { return vec2( x - o.x, y - o.y ); }
        vec2 operator*(vec2 o) const { return vec2( x * o.x, y * o.y ); }
        vec2 operator/(vec2 o) const { return vec2( x / o.x, y / o.y ); }

        vec2 operator+(float o) const { return vec2( x + o, y + o ); }
        vec2 operator-(float o) const { return vec2( x - o, y - o ); }
        vec2 operator*(float o) const { return vec2( x * o, y * o ); }
        vec2 operator/(float o) const { return vec2( x / o, y / o ); }

        void operator+=(vec2 o) { x += o.x; y += o.y; }
        void operator-=(vec2 o) { x -= o.x; y -= o.y; }
        void operator*=(vec2 o) { x *= o.x; y *= o.y; }
        void operator/=(vec2 o) { x /= o.x; y /= o.y; }

        void operator+=(float o) { x += o; y += o; }
        void operator-=(float o) { x -= o; y -= o; }
        void operator*=(float o) { x *= o; y *= o; }
        void operator/=(float o) { x /= o; y /= o; }

        float length() { return sqrtf( x*x + y*y ); }
        float dot(vec2 o) { return x*o.x + y*o.y; }

        void normalize()
        {
            float len = length();
            if( len == 0 )
                return;
            x /= len;
            y /= len;
        }

        vec2 getNormalized() const
        {
            vec2 v = *this;
            v.normalize();
            return v;
        }

        static void test();

    public:
        float x = 0;
        float y = 0;
    };
}
