#include "structs.h"

typedef struct s_camera {
    double hsize;
    double vsize;
    double field_of_view;
    double half_width;
    double half_height;
    double pixel_size;
    t_matrix *transform;
} t_camera;

t_camera camera(double hsize, double vsize, double field_of_view)
{
    t_camera c;

    c.hsize = hsize;
    c.vsize = vsize;
    c.field_of_view = field_of_view;
    c.transform = identity_matrix(4);

    return c;
}

void setup_camera(t_camera *camera)
{
    double half_view = tan(camera->field_of_view / 2);
    double aspect = camera->hsize / camera->vsize;

    if (aspect >= 1) {
        camera->half_width = half_view;
        camera->half_height = half_view / aspect;
    } else {
        camera->half_width = half_view * aspect;
        camera->half_height = half_view;
    }

    camera->pixel_size = (camera->half_width * 2) / camera->hsize;
}

t_ray ray_for_pixel(t_camera *camera, int px, int py)
{
    // Compute the offset from the edge of the canvas to the pixel's center
    double xoffset = (px + 0.5) * camera->pixel_size;
    double yoffset = (py + 0.5) * camera->pixel_size;

    // Compute the untransformed coordinates of the pixel in world space
    double world_x = camera->half_width - xoffset;
    double world_y = camera->half_height - yoffset;

    // Using the camera matrix, transform the canvas point and the origin
    t_matrix *inverse_transform = inverse(camera->transform);
    t_tuple pixel = matrix_multiply_tuple(inverse_transform, point(world_x, world_y, -1));
    t_tuple origin = matrix_multiply_tuple(inverse_transform , point(0, 0, 0));
    t_tuple direction = normalize(subtract(pixel, origin));
    printf("Direction: %f %f %f\n", direction.x, direction.y, direction.z);
    destroy_matrix(inverse_transform);
    return ray(origin, direction);
}

t_canvas render(t_camera *camera, t_world *world)
{
    t_canvas image = canvas(camera->hsize, camera->vsize);

    for (int y = 0; y < camera->vsize; y++) {
        for (int x = 0; x < camera->hsize; x++)
        {
            t_ray r = ray_for_pixel(camera, x, y);
            t_color color = color_at(world, r);
            write_pixel(&image, x, y, &color);
        }
    }

    return image;
}

void test_setup_camera()
{
    // Test: Constructing a camera
    t_camera c;
    double hsize = 160;
    double vsize = 120;
    double field_of_view = M_PI / 2;

    c = camera(hsize, vsize, field_of_view);
    assert(c.hsize == 160);
    assert(c.vsize == 120);
    assert(c.field_of_view == M_PI / 2);
    assert(matrices_are_equal(c.transform, identity_matrix(4)));
    printf("Passed: Constructing a camera\n");

    // Test: The pixel size for a horizontal canvas
    t_camera c1 = camera(200, 125, M_PI / 2);
    setup_camera(&c1);
    assert(float_equals(c1.pixel_size, 0.01, EPSILON));
    printf("Passed: The pixel size for a horizontal canvas\n");

    // Test: The pixel size for a vertical canvas
    t_camera c2 = camera(125, 200, M_PI / 2);
    setup_camera(&c2);
    assert(float_equals(c2.pixel_size, 0.01, EPSILON));
    printf("Passed: The pixel size for a vertical canvas\n");

    // Test: Constructing a ray through the center of the canvas
    t_camera c3 = camera(201, 101, M_PI / 2);
    setup_camera(&c3);
    t_ray r = ray_for_pixel(&c3, 100, 50);
    assert(equal_tuples(r.origin, point(0, 0, 0), EPSILON));
    assert(equal_tuples(r.direction, vector(0, 0, -1), EPSILON));
    printf("Passed: Constructing a ray through the center of the canvas\n");

    // Test: Constructing a ray through a corner of the canvas
    t_camera c4 = camera(201, 101, M_PI / 2);
    setup_camera(&c4);
    t_ray r1 = ray_for_pixel(&c4, 0, 0);
    t_tuple v = vector(0.66519, 0.33259, -0.66851);
    t_tuple normalized = normalize(v);
 
    assert(equal_tuples(r1.origin, point(0, 0, 0), EPSILON));
    assert(equal_tuples(r1.direction, normalized , EPSILON));
    
    printf("Passed: Constructing a ray through a corner of the canvas\n");

    // Test: Constructing a ray when the camera is transformed
    t_camera c5 = camera(201, 101, M_PI / 2);
    setup_camera(&c5);
    c5.transform = multiply_matrices(rotation_y(M_PI / 4), translation(0, -2, 5));
    t_ray r2 = ray_for_pixel(&c5, 100, 50);
    printf("Origin: %f %f %f\n", r2.origin.x, r2.origin.y, r2.origin.z);
    //printf("R2 Direction: %f %f %f\n", r2.direction.x, r2.direction.y, r2.direction.z);
    t_tuple v1 = vector(sqrt(2) / 2, 0, -sqrt(2) / 2);
    printf("V1: %f %f %f\n", v1.x, v1.y, v1.z);
    assert(equal_tuples(r2.origin, point(0, 2, -5), EPSILON));
    assert(equal_tuples(r2.direction, v1, EPSILON));
    printf("Passed: Constructing a ray when the camera is transformed\n");
}
