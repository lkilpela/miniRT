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
        }
    }
}

// Function to print the properties of a shape
void print_sp(t_shape *shape) {
    t_sphere *sphere = (t_sphere *)shape->object;
    printf("Shape center: %f %f %f\n", sphere->center.x, sphere->center.y, sphere->center.z);
    printf("Shape radius: %f\n", sphere->radius);
}

void print_debug_info(t_matrix *inverse_transform, t_tuple local_point, t_tuple local_normal, t_matrix *transpose_inverse_transform, t_tuple world_normal, t_tuple result)
{
    printf(YELLOW "Normal at shape\n" RESET);
    printf(GREEN "Inverse transform\n" RESET);
    print_matrix(inverse_transform);
    printf(GREEN "Local point\n" RESET);
    print_tuple(local_point);
    printf(GREEN "Local normal\n" RESET);
    print_tuple(local_normal);
    printf(GREEN "Transpose inverse transform\n" RESET);
    print_matrix(transpose_inverse_transform);
    printf(GREEN "World normal\n" RESET);
    print_tuple(world_normal);
    printf(GREEN "Normalized world normal\n" RESET);
    print_tuple(result);
}


void print_shape(t_shape s)
{
    printf(YELLOW "Shape\n" RESET);
    printf(BLUE "Transform:\n" RESET);
    print_matrix(s.transform);
    printf(BLUE "Material:\n" RESET);
    print_material(&s.material);
    printf(BLUE "Object:\n" RESET);
    if (s.object) {
        // Assuming you have a type identifier or type-specific field
        // For example, if you know it's a sphere:
        t_sphere *sphere = (t_sphere *)s.object;
        printf("Sphere at %p\n", sphere);
        printf("Center: ");
        print_tuple(sphere->center);
        printf("Radius: %f\n", sphere->radius);
    } else {
        printf("None\n");
    }
    printf(BLUE "Local normal at:\n" RESET);
    if (s.local_normal_at) {
        printf("%p\n", s.local_normal_at);
        // Optionally call the function with a test point
        t_tuple test_point = point(1, 0, 0); // Example test point
        t_tuple normal = s.local_normal_at(&s, test_point);
        printf("Normal at (%f, %f, %f): ", test_point.x, test_point.y, test_point.z);
        print_tuple(normal);
    } else {
        printf("None\n");
    }
    printf(BLUE "Local intersect:\n" RESET);
    if (s.local_intersect) {
        printf("%p\n", s.local_intersect);
        // Optionally call the function with a test ray
        t_ray test_ray = ray(point(0, 0, -5), vector(0, 0, 1)); // Example test ray
        t_intersections intersections = s.local_intersect(&s, test_ray);
        printf("Intersections count: %d\n", intersections.count);
        for (int i = 0; i < intersections.count; i++) {
            printf("Intersection %d: t = %f\n", i, intersections.array[i].t);
        }
    } else {
        printf("None\n");
    }
}