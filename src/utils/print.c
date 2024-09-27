#include "structs.h"

void print_color(t_color c)
{
    printf("%f %f %f\n", c.r, c.g, c.b);
}

void print_float(double f)
{
    printf("%f\n", f);
}

/* void print_lighting(t_light *light, t_color *color, t_tuple point, t_tuple eyev, t_tuple normalv)
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
} */

void print_material(t_material *material)
{
    printf(BOLD GREEN "Color: \n" RESET);
    print_color(material->color);
    printf(BOLD GREEN "Diffuse: \n" RESET);
    print_float(material->diffuse);
    printf(BOLD GREEN "Specular: \n" RESET);
    print_float(material->specular);
}

/* void print_lighting_shadow(t_material *material, t_light *light, t_tuple point, t_tuple eyev, t_tuple normalv, bool in_shadow)
{
    printf(BOLD YELLOW "Lighting: \n" RESET);
    printf(BOLD GREEN "Material: \n" RESET);
    print_material(material);
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
} */

void print_ray_for_pixel(double xoffset, double yoffset, double world_x, double world_y, t_matrix *inverse_transform, t_tuple pixel, t_tuple origin, t_tuple direction)
{
    printf(BOLD YELLOW "Ray for pixel\n" RESET);
    printf(BOLD GREEN "xoffset: " RESET);
    print_float(xoffset);
    printf(BOLD GREEN "yoffset: " RESET);
    print_float(yoffset);
    printf(BOLD GREEN "world_x: " RESET);
    print_float(world_x);
    printf(BOLD GREEN "world_y: " RESET);
    print_float(world_y);
    printf(BOLD GREEN "Inverse transform: \n" RESET);
    print_matrix(inverse_transform);
    printf(BOLD GREEN "Pixel: \n" RESET);
    print_tuple_p(pixel);
    printf(BOLD GREEN "Origin: \n" RESET);
    print_tuple_p(origin);
    printf(BOLD GREEN "Direction: \n" RESET);
    print_tuple_v(direction);
}

void print_camera(t_camera camera)
{
    printf(BOLD YELLOW "Camera: \n" RESET);
    printf(BOLD GREEN "hsize: \n" RESET);
    print_float(camera.hsize);
    printf(BOLD GREEN "vsize: \n" RESET);
    print_float(camera.vsize);
    printf(BOLD GREEN "fov: \n" RESET);
    print_float(camera.fov);
    printf(BOLD GREEN "from: \n" RESET);
    print_tuple_p(camera.from);
    printf(BOLD GREEN "to: \n" RESET);
    print_tuple_p(camera.to);
    printf(BOLD GREEN "up: \n" RESET);
    print_tuple_v(camera.up);
    printf(BOLD GREEN "half_width: \n" RESET);
    print_float(camera.half_width);
    printf(BOLD GREEN "half_height: \n" RESET);
    print_float(camera.half_height);
    printf(BOLD GREEN "pixel_size: \n" RESET);
    print_float(camera.pixel_size);
    printf(BOLD GREEN "transform: \n" RESET);
    print_matrix(camera.transform);
}

/* 
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
            printf(BOLD YELLOW "Camera: " RESET "%f %f %f\n", camera->hsize, camera->vsize, camera->fov);
            print_lighting(&world->light, result, comps->point, comps->eyev, comps->normalv);
            uint32_t pixel_color = color_to_pixel(*result);
            printf(BOLD GREEN "Pixel Color: " RESET "%x\n", pixel_color);
            printf(BOLD MAGENTA "Color from pixel: " RESET);
            print_color(*result);
        }
    }
} */

/* void print_debug_info(t_matrix *inverse_transform, t_tuple local_point, t_tuple local_normal, t_matrix *transpose_inverse_transform, t_tuple world_normal, t_tuple result)
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
    print_tuple_(result);
} */


void print_shape(t_shape s)
{
    printf(YELLOW "Shape\n" RESET);
    printf(BLUE "Transform:\n" RESET);
    print_matrix(s.transform);
    printf(BLUE "Material:\n" RESET);
    print_material(s.material);
    printf(BLUE "Object:\n" RESET);
    if (s.object) {
        // Assuming you have a type identifier or type-specific field
        // For example, if you know it's a sphere:
        t_sphere *sphere = (t_sphere *)s.object;
        printf("Sphere at %p\n", sphere);
        printf("Center: ");
        print_tuple_p(sphere->center);
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
        print_tuple_v(normal);
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

 // Debug print for parsed info
void	print_parsed_info(char **info)
{
	printf("Parsed info:\n");
	for (int i = 0; info[i] != NULL; i++)
	{
		printf("info[%d]: %s\n", i, info[i]);
	}

}

void print_count_elements(char **array)
{
	printf("Number of elements: %d\n", count_elements(array));
}

// Function to print a matrix
void print_matrix(t_matrix *m) {
    for (int i = 0; i < m->y; i++) {
        for (int j = 0; j < m->x; j++) {
            printf("%f ", m->data[i][j]);
        }
        printf("\n");
    }
}


void print_sp(t_shape *shape)
{
    t_sphere    *sp;

    sp = (t_sphere *)(shape)->object;
    printf(YELLOW "Sphere:\n" RESET);
    printf("Shape ID: %d\n", shape->id);
    printf("1. Center: ");
    print_tuple_p(sp->center);
    printf("2. Radius: %f\n", sp->radius);
    printf("3. Color: ");
    print_color(shape->material->color);
}

void print_plane(t_shape *shape)
{
    t_plane    *pl;


    pl = (t_plane *)(shape)->object;
    printf(YELLOW "Plane:\n" RESET);
    printf("Shape ID: %d\n", shape->id);
    printf("1. Point: ");
    print_tuple_p(pl->point);
    printf("3. Normal: ");
    print_tuple_v(pl->normal);
    printf("4. Color: ");
    print_color(shape->material->color);
}

void print_cylinder(t_shape *shape)
{
    t_cylinder    *cy;

    cy = (t_cylinder *)(shape)->object;
    printf(YELLOW "Cylinder:\n" RESET);
    printf("Shape ID: %d\n", shape->id);
    printf("1. Minimum: %f\n", cy->minimum);
    printf("2. Maximum: %f\n", cy->maximum);
    printf("3. Closed: %s\n", cy->closed ? "true" : "false");
    printf("4. Color: ");
    print_color(shape->material->color);
}

void print_object(t_shape *shape)
{
    if (shape->id == SPHERE)
        print_sp(shape);
    else if (shape->id == PLANE)
        print_plane(shape);
    else if (shape->id == CYLINDER)
        print_cylinder(shape);
}

void print_world(t_world *w)
{
	printf(BOLD RED "World:\n" RESET);

    printf(YELLOW "Ambient:\n" RESET);
	printf("1. Ratio: %f\n", w->ambient.ratio);
	printf("2. Color: ");
	print_color(w->ambient.color);

	printf(YELLOW "Camera:\n" RESET);
	printf("1. Position: ");
	print_tuple_p(w->camera.from);
	printf("2. Look at: ");
	print_tuple_p(w->camera.to);
	printf("3. Up: ");
	print_tuple_v(w->camera.up);
	printf("4. FOV: %f\n", w->camera.fov);
	//print_camera(w->camera);

	printf(YELLOW "Light:\n" RESET);
	printf("1. Position: ");
	print_tuple_p(w->light.position);
	printf("2. Intensity: ");
	print_color(w->light.intensity);
	printf("3. Brightness: %f\n", w->light.brightness);

	printf(YELLOW "Objects:\n" RESET);
	for (int i = 0; i < w->count; i++)
	{
		printf(GREEN "Object <%d>:\n" RESET, i);
		print_object(w->objects[i]);
	}




}