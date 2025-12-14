#pragma once

namespace fw
{
    class color4f
    {
    public:

        color4f() {}
        color4f(float nr, float ng, float nb, float na) : r(nr), g(ng), b(nb), a(na) {}

    public:
        float r = 0;
        float g = 0;
        float b = 0;
        float a = 0;


    };

    class color4b
    {

    };
}