#include "tuple.h"

t_color create_color(float red, float green, float blue)
{
    t_color color;

    color.red = red;
    color.green = green;
    color.blue = blue;
    return color;
}

void test_color()
{
    t_color c = create_color(-0.5, 0.4, 1.7);

    assert(equal(c.red, -0.5));
    assert(equal(c.green, 0.4));
    assert(equal(c.blue, 1.7));
    printf("Color test passed.\n");
}
