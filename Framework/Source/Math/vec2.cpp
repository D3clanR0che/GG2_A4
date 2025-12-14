#include "Core/CoreHeaders.h"
#include "vec2.h"

namespace fw
{
    void vec2::test()
    {
        const vec2 a(3, 4);
        assert(a.x == 3 && a.y == 4);

        vec2 b(5, 6);

        vec2 c = a + b;
        assert(c.x == 8 && c.y == 10);

        vec2 d(1, 1);
        d += b;
        assert(d.x == 6 && d.y == 7);
    }
}