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

void render(t_canvas *canvas, t_sphere *s, t_light *light)
{
    float pixel_size = WALL_SIZE / WIDTH;
    float half = WALL_SIZE / 2.0;
    t_tuple ray_origin = point(RAY_ORIGIN_X, RAY_ORIGIN_Y, RAY_ORIGIN_Z);

    for (int y = 0; y < HEIGHT; ++y) { // # for each row of pixels in the canvas
        float world_y = half - pixel_size * y; // # compute the world y coordinate (top = +half, bottom = -half)
        for (int x = 0; x < WIDTH; ++x) { // # for each pixel in the row
            float world_x = -half + pixel_size * x; // # compute the world x coordinate (left = -half, right = half)
            t_tuple target_point = point(world_x, world_y, WALL_Z); // # describe the point on the wall that the ray will target
            t_ray r = ray(ray_origin, normalize(subtract(target_point, ray_origin)));
            t_intersections xs = intersect(s, &r);
            t_intersection *h = hit(&xs);
            if (h != NULL) {
                t_tuple intersection_point = position(r, h->t);
                t_tuple normal = normal_at(s, intersection_point);
                t_tuple eye = negate(r.direction);
                t_color color = lighting(&s->material, light, intersection_point, eye, normal);
                //printf("Intersection Point: %f %f %f\n", intersection_point.x, intersection_point.y, intersection_point.z);
               // printf("Normal: %f %f %f\n", normal.x, normal.y, normal.z);
                //printf("Eye: %f %f %f\n", eye.x, eye.y, eye.z);
                printf("Color: %f %f %f\n", color.r, color.g, color.b);
                uint32_t pixel_color = (0xFF << 24) | ((int)(color.r * 255) << 16) | ((int)(color.g * 255) << 8) | (int)(color.b * 255);
                printf("Pixel Color: %d\n", pixel_color);
                write_pixel(canvas, x, y, pixel_color);
            } else {
                write_pixel(canvas, x, y, BLACK);
            }
            free(xs.array);
        }
    }
    printf("RENDER(Lighting position): %f %f %f\n", light->position.x, light->position.y, light->position.z);
    
}
