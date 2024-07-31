#include "tuple.h"

t_color create_color(float red, float green, float blue)
{
    t_color color;

    color.red = red;
    color.green = green;
    color.blue = blue;
    return color;
}
bool equal_color(t_color c1, t_color c2)
{
	return (equal(c1.red, c2.red) && equal(c1.green, c2.green) 
		&& equal(c1.blue, c2.blue));
}

t_color add_color(t_color c1, t_color c2)
{
    t_color result;

    result.red = c1.red + c2.red;
    result.green = c1.green + c2.green;
    result.blue = c1.blue + c2.blue;
    return result;
}

t_color subtract_color(t_color c1, t_color c2)
{
    t_color result;

    result.red = c1.red - c2.red;
    result.green = c1.green - c2.green;
    result.blue = c1.blue - c2.blue;
    return result;
}

t_color multiply_color_by_scalar(t_color c, float scalar)
{
    t_color result;

    result.red = c.red * scalar;
    result.green = c.green * scalar;
    result.blue = c.blue * scalar;
    return result;
}

// Hadamard product (or Schur product): 
// This method of blending two colors works by multiplying corresponding
// components of each color to form a new color.
t_color multiply_colors(t_color c1, t_color c2)
{
    t_color result;

    result.red = c1.red * c2.red;
    result.green = c1.green * c2.green;
    result.blue = c1.blue * c2.blue;
    return result;
}

void test_color()
{
    t_color c = create_color(-0.5, 0.4, 1.7);

    assert(equal(c.red, -0.5));
    assert(equal(c.green, 0.4));
    assert(equal(c.blue, 1.7));
    printf("Test create_color passed.\n");

    t_color c1 = create_color(0.9, 0.6, 0.75);
    t_color c2 = create_color(0.7, 0.1, 0.25);

    t_color expected1 = create_color(1.6, 0.7, 1.0);
    t_color result1 = add_color(c1, c2);
    assert(equal_color(result1, expected1));
    printf("Test add_color passed.\n");

    t_color expected2 = create_color(0.2, 0.5, 0.5);
    t_color result2 = subtract_color(c1, c2);
    assert(equal_color(result2, expected2));
    printf("Test subtract_color passed.\n");

    t_color c3 = create_color(0.2, 0.3, 0.4);
    t_color expected3 = create_color(0.4, 0.6, 0.8);
    t_color result3 = multiply_color_by_scalar(c3, 2);
    assert(equal_color(result3, expected3));
    printf("Test multiply_color_by_scalar passed.\n");

    t_color c4 = create_color(1, 0.2, 0.4);
    t_color c5 = create_color(0.9, 1, 0.1);
    t_color expected4 = create_color(0.9, 0.2, 0.04);
    t_color result4 = multiply_colors(c4, c5);
    assert(equal_color(result4, expected4));
    printf("Test multiply_colors passed.\n");
}

