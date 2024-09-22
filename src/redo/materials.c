#include "structs.h"

t_color color(float r, float g, float b)
{
    t_color c;

    c.r = r;
    c.g = g;
    c.b = b;
    return (c);
}


// A default material
t_material material()
{
    t_material m;

    m.color = color(1, 1, 1);
    m.ambient = 0.1;
    m.diffuse = 0.9;
    m.specular = 0.9;
    m.shininess = 200.0;
    return (m);
}

bool color_equal(t_color a, t_color b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b;
}

void print_color(t_color c)
{
    printf("Color: %f %f %f\n", c.r, c.g, c.b);
}

void test_lighting()
{
    // Eye is positioned directly between the light and the surface
    t_material m = material();
    t_tuple position = point(0, 0, 0);

    /* Lighting with the eye between the light and the surface
    ** - Eye is positioned directly between the light and the surface
    ** - Ambient, diffuse and specular components are all at full strength
    ** - Total intensity: 0.1(ambient) + 0.9(diffuse) + 0.9(specular) = 1.9
    */
    t_tuple eyev = vector(0, 0, -1);
    t_tuple normalv = vector(0, 0, -1);
    t_light light = point_light(point(0, 0, -10), color(1, 1, 1));
    t_color result = lighting(&m, &light, position, eyev, normalv);
    assert(float_equals(result.r, 1.9, EPSILON));
    assert(float_equals(result.g, 1.9, EPSILON));
    assert(float_equals(result.b, 1.9, EPSILON));
    printf("Passed: Lighting with the eye between the light and the surface\n");

    /* Lighting with the eye between the light and the surface, eye offset 45 degrees
    ** - Light and surface normal are positioned directly
    ** - Eye is offset 45 degrees the normal
    ** - Ambient and diffuse components are unchanged because light and normal are the same
    ** - Specular component: 0
    ** - Total intensity: 0.1 + 0.9 + 0 = 1.0
    */
    eyev = vector(0, sqrt(2)/2, -sqrt(2)/2);
    normalv = vector(0, 0, -1);
    result = lighting(&m, &light, position, eyev, normalv);
    assert(float_equals(result.r, 1.0, EPSILON));  
    assert(float_equals(result.g, 1.0, EPSILON));
    assert(float_equals(result.b, 1.0, EPSILON));
    printf("Passed: Lighting with the eye between the light and the surface, eye offset 45 degrees\n");

    /* Lighting with eye opposite surface, light offset 45 degrees
    ** - Eye is positioned opposite the surface
    ** - Light is offset 45 degrees from the surface
    ** - Diffuse component: 0.9 x sqrt(2)/2 because light and normal are at 45 degree angles
    ** - Specular component: 0
    ** - Total intensity: 0.1 + 0.9 x sqrt(2)/2 + 0 = 0.7364
    */
    eyev = vector(0, 0, -1);
    normalv = vector(0, 0, -1);
    light = point_light(point(0, 10, -10), color(1, 1, 1));
    result = lighting(&m, &light, position, eyev, normalv);
    assert(float_equals(result.r, 0.7364, EPSILON));
    assert(float_equals(result.g, 0.7364, EPSILON));
    assert(float_equals(result.b, 0.7364, EPSILON));
    printf("Passed: Lighting with eye opposite surface, light offset 45 degrees\n");

    /* Lighting with eye in the path of the reflection vector
    ** - Light and normal vectors are at 45 degree angles
    ** - Eye is in the path of the reflection vector
    ** - Specular component to be at full strength
    ** - Ambient and diffuse components are same as previous test
    ** - Total intensity: 0.1 + 0.9 x sqrt(2)/2 + 0.9 = 1.6364
    */
    eyev = vector(0, -sqrt(2)/2, -sqrt(2)/2);
    normalv = vector(0, 0, -1);
    result = lighting(&m, &light, position, eyev, normalv);
    printf("Result: %f %f %f\n", result.r, result.g, result.b);
    assert(float_equals(result.r, 1.6364, EPSILON));
    assert(float_equals(result.g, 1.6364, EPSILON));
    assert(float_equals(result.b, 1.6364, EPSILON));
    printf("Passed: Lighting with eye in the path of the reflection vector\n");

    /* Lighting with the light behind the surface
    ** - Light no longer illuminates the surface
    ** - Diffuse and specular components are zero
    ** - Total intensity is the same as the ambient component or 0.1
    */
    eyev = vector(0, 0, -1);
    normalv = vector(0, 0, -1);
    light = point_light(point(0, 0, 10), color(1, 1, 1));
    result = lighting(&m, &light, position, eyev, normalv);
    assert(float_equals(result.r, 0.1, EPSILON));
    assert(float_equals(result.g, 0.1, EPSILON));
    assert(float_equals(result.b, 0.1, EPSILON));
    printf("Passed: Lighting with the light behind the surface\n");
}