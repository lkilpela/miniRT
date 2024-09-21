#include "structs.h"


t_canvas canvas(int width, int height)
{
    t_canvas c;

    c.width = width;
    c.height = height;
    c.pixels = calloc(width * height, sizeof(uint32_t));
    if (c.pixels == NULL)
    {
        printf("Failed to allocate memory for canvas\n");
        exit(1);
    }
    return (c);
}

void write_pixel(t_canvas *c, int x, int y, uint32_t color)
{
    if (x < 0 || x >= c->width || y < 0 || y >= c->height)
        return;
    c->pixels[y * c->width + x] = color;
}

void render(t_canvas *c, t_sphere *s)
{
    float pixel_size = WALL_SIZE / WIDTH;
    float half = WALL_SIZE / 2.0;
    t_tuple ray_origin = point(RAY_ORIGIN_X, RAY_ORIGIN_Y, RAY_ORIGIN_Z);

    for (int y = 0; y < HEIGHT; ++y) { // # for each row of pixels in the canvas
        float world_y = half - pixel_size * y; // # compute the world y coordinate (top = +half, bottom = -half)
        for (int x = 0; x < WIDTH; ++x) { // # for each pixel in the row
            float world_x = -half + pixel_size * x; // # compute the world x coordinate (left = -half, right = half)
            t_tuple position = point(world_x, world_y, WALL_Z); // # describe the point on the wall that the ray will target
            t_ray r = ray(ray_origin, normalize(subtract(position, ray_origin)));
            t_intersections xs = intersect(s, &r);
            if (hit(&xs) != NULL) {
                write_pixel(canvas, x, y, RED);
            } else {
                write_pixel(canvas, x, y, BLACK);
            }
        }
    }
}
