#include "structs.h"
#include "matrix.h"

void print_float(float f)
{
    printf("%f\n", f);
}

void print_lighting(t_light *light, t_color *color, t_tuple point, t_tuple eyev, t_tuple normalv)
{
    printf(BOLD YELLOW "Lighting: \n" RESET);
    printf(BOLD CYAN "Light position: \n" RESET);
    print_tuple(light->position);
    printf(BOLD GREEN "Color: \n" RESET);
    print_color(*color);
    printf(BOLD MAGENTA "Point: \n" RESET);
    print_tuple(point);
    printf(BOLD BLUE "Eye vector: \n" RESET);
    print_tuple(eyev);
    printf(BOLD RED "Normal vector: \n" RESET);
    print_tuple(normalv);
}

void print_material(t_material *m)
{
    printf(BOLD GREEN "Color: \n" RESET);
    print_color(m->color);
    printf(BOLD GREEN "Ambient: \n" RESET);
    print_float(m->ambient);
    printf(BOLD GREEN "Diffuse: \n" RESET);
    print_float(m->diffuse);
    printf(BOLD GREEN "Specular: \n" RESET);
    print_float(m->specular);
}

void print_lighting_shadow(t_material *m, t_light *light, t_tuple point, t_tuple eyev, t_tuple normalv, bool in_shadow)
{
    printf(BOLD YELLOW "Lighting: \n" RESET);
    printf(BOLD GREEN "Material: \n" RESET);
    print_material(m);
    printf(BOLD CYAN "Light position: \n" RESET);
    print_tuple(light->position);
    printf(BOLD GREEN "Point: \n" RESET);
    print_tuple(point);
    printf(BOLD BLUE "Eye vector: \n" RESET);
    print_tuple(eyev);
    printf(BOLD RED "Normal vector: \n" RESET);
    print_tuple(normalv);
    printf(BOLD MAGENTA "In shadow: \n" RESET);
    printf("%s\n", in_shadow ? "true" : "false");
}

/* void print_world(t_world *w)
{
    printf(BOLD YELLOW "World count: " RESET "%d\n", w->count);
    for (int i = 0; i < w->count; i++)
    {
        printf(BOLD CYAN "Sphere %d: \n" RESET, i);
        printf(BOLD GREEN "Center: " RESET);
        print_tuple(w->spheres[i].center);
        printf(BOLD GREEN "Transform: \n" RESET);
        print_matrix(w->spheres[i].transform);
        printf(BOLD GREEN "Color: " RESET);
        print_color(w->spheres[i].material.color);
        printf(BOLD GREEN "Ambient: " RESET);
        print_float(w->spheres[i].material.ambient);
        printf(BOLD GREEN "Diffuse: " RESET);
        print_float(w->spheres[i].material.diffuse);
        printf(BOLD GREEN "Specular: " RESET);
        print_float(w->spheres[i].material.specular);
    }
} */

void print_hit_info(t_world *world, t_computations *comps, t_color *result, int x, int y, t_camera *camera, t_intersection *hit_p)
{
    if (hit_p)
    {
        // Print hit information at key pixels
        if ((x == camera->hsize / 2 && y == camera->vsize / 2) || // Center
            (x == 0 && y == 0) || // Top-Left Corner
            (x == camera->hsize - 1 && y == 0) || // Top-Right Corner
            (x == 0 && y == camera->vsize - 1) || // Bottom-Left Corner
            (x == camera->hsize - 1 && y == camera->vsize - 1)) { // Bottom-Right Corner

            printf(BOLD YELLOW "Hit at key pixel (%d, %d): " RESET "t = %f\n", x, y, hit_p->t);
            printf(BOLD YELLOW "Camera: " RESET "%f %f %f\n", camera->hsize, camera->vsize, camera->field_of_view);
            print_lighting(&world->light, result, comps->point, comps->eyev, comps->normalv);
            uint32_t pixel_color = color_to_pixel(*result);
            printf(BOLD GREEN "Pixel Color: " RESET "%x\n", pixel_color);
            printf(BOLD MAGENTA "Color from pixel: " RESET);
            print_color(*result);
            print_world(world);
        }
    }
}

// Function to print the properties of a shape
void print_sp(t_shape *shape) {
    t_sphere *sphere = (t_sphere *)shape->object;
    printf("Shape center: %f %f %f\n", sphere->center.x, sphere->center.y, sphere->center.z);
    printf("Shape radius: %f\n", sphere->radius);
}