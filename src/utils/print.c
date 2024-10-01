#include "structs.h"

typedef struct {
    t_color min;
    t_color max;
    const char* name;
} t_color_range;

t_color_range color_ranges[] = {
    {{0.9, 0.9, 0.9}, {1.0, 1.0, 1.0}, "White"},
    {{0.9, 0.0, 0.0}, {1.0, 0.1, 0.1}, "Red"},
    {{0.0, 0.9, 0.0}, {0.1, 1.0, 0.1}, "Green"},
    {{0.0, 0.0, 0.9}, {0.1, 0.1, 1.0}, "Blue"},
    {{0.9, 0.9, 0.0}, {1.0, 1.0, 0.1}, "Yellow"},
    {{0.9, 0.0, 0.9}, {1.0, 0.1, 1.0}, "Magenta"},
    {{0.0, 0.9, 0.9}, {0.1, 1.0, 1.0}, "Cyan"},
    {{0.4, 0.4, 0.4}, {0.6, 0.6, 0.6}, "Gray"},
    {{0.5, 0.5, 0.5}, {1.0, 1.0, 1.0}, "Light Gray"},
    {{0.0, 0.0, 0.0}, {0.5, 0.5, 0.5}, "Dark Gray"},
    {{0.0, 0.5, 0.0}, {0.2, 1.0, 0.6}, "Light Green"},
    {{0.5, 0.0, 0.0}, {0.7, 0.1, 0.1}, "Dark Red"},
    {{0.0, 0.5, 0.0}, {0.1, 0.7, 0.1}, "Dark Green"},
    {{0.0, 0.0, 0.5}, {0.1, 0.1, 0.7}, "Dark Blue"},
    {{0.5, 0.5, 0.0}, {0.7, 0.7, 0.1}, "Olive"},
    {{0.5, 0.0, 0.5}, {0.7, 0.1, 0.7}, "Purple"},
    {{0.0, 0.5, 0.5}, {0.1, 0.7, 0.7}, "Teal"},
    {{0.8, 0.4, 0.0}, {1.0, 0.6, 0.2}, "Orange"},
    {{0.8, 0.8, 0.8}, {0.9, 0.9, 0.9}, "Silver"},
    {{0.2, 0.2, 0.2}, {0.3, 0.3, 0.3}, "Charcoal"},
    {{0.6, 0.3, 0.0}, {0.8, 0.5, 0.2}, "Brown"},
    {{0.9, 0.6, 0.0}, {1.0, 0.8, 0.2}, "Gold"},
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, "Black"},
    {{0.0, 0.0, 0.0}, {0.2, 0.2, 0.2}, "Very Dark Gray"},
    {{0.2, 0.2, 0.2}, {0.4, 0.4, 0.4}, "Dark Gray"},
    {{0.6, 0.6, 0.6}, {0.8, 0.8, 0.8}, "Light Gray"},
    {{0.0, 0.0, 0.5}, {0.2, 0.2, 1.0}, "Navy"},
    {{0.0, 0.5, 0.5}, {0.2, 1.0, 1.0}, "Aqua"},
    {{0.5, 0.0, 0.0}, {1.0, 0.2, 0.2}, "Maroon"},
    {{0.5, 0.5, 0.0}, {1.0, 1.0, 0.2}, "Lime"},
    {{0.5, 0.0, 0.5}, {1.0, 0.2, 1.0}, "Fuchsia"},
    {{0.0, 0.5, 0.5}, {0.2, 1.0, 1.0}, "Turquoise"},
    {{0.5, 0.5, 0.5}, {0.7, 0.7, 0.7}, "Medium Gray"},
    {{0.7, 0.7, 0.7}, {0.9, 0.9, 0.9}, "Light Silver"},
    {{0.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, "Jet Black"},
    {{0.1, 0.1, 0.1}, {0.3, 0.3, 0.3}, "Coal"},
    {{0.3, 0.3, 0.3}, {0.5, 0.5, 0.5}, "Slate"},
    {{0.5, 0.5, 0.5}, {0.7, 0.7, 0.7}, "Ash"},
    {{0.7, 0.7, 0.7}, {0.9, 0.9, 0.9}, "Platinum"},
    {{0.9, 0.9, 0.9}, {1.0, 1.0, 1.0}, "Snow"}
};

const char* get_color_name(t_color color) {
    int num_ranges = sizeof(color_ranges) / sizeof(color_ranges[0]);
    for (int i = 0; i < num_ranges; i++) {
        if (color.r >= color_ranges[i].min.r && color.r <= color_ranges[i].max.r &&
            color.g >= color_ranges[i].min.g && color.g <= color_ranges[i].max.g &&
            color.b >= color_ranges[i].min.b && color.b <= color_ranges[i].max.b) {
            return color_ranges[i].name;
        }
    }
    return "Unknown Color";
}

void print_color(t_color c)
{
    printf("%f %f %f (%s)\n", c.r, c.g, c.b, get_color_name(c));
}

void print_hit_data(int x, int y, t_computations comps, t_color result, t_ray r, t_intersection *hit_p) {
    if ((x == 0 && y == 0) || // Top-Left Corner
        (x == WIDTH - 1 && y == 0) || // Top-Right Corner
        (x == 0 && y == HEIGHT - 1) || // Bottom-Left Corner
        (x == WIDTH - 1 && y == HEIGHT - 1) || // Bottom-Right Corner
        (x == 200 && y == 100) ||        // Specific point
        (x == 100 && y == 50) ||         // Specific point
        (x == 300 && y == 150) ||        // Specific point
        (x == WIDTH / 2 && y == HEIGHT / 2) || // Center
        (x == WIDTH / 2 && y == 0) ||    // Middle of top edge
        (x == WIDTH / 2 && y == HEIGHT - 1) || // Middle of bottom edge
        (x == 0 && y == HEIGHT / 2) ||   // Middle of left edge
        (x == WIDTH - 1 && y == HEIGHT / 2)) // Middle of right edge
    {
        printf(YELLOW "Hit at key pixel: (%d, %d)\n" RESET "t = %f\n", x, y, comps.t);
        printf(YELLOW "Color at hit: " RESET);
        print_color(result);
        uint32_t pixel_color = color_to_pixel(result);
        printf(YELLOW "Pixel Color: " RESET "%x\n", pixel_color);
        printf(YELLOW "RAY: \n" RESET);
        printf(GREEN "Origin: " RESET);
        print_tuple_p(r.origin);
        printf(GREEN "Direction: " RESET);
        print_tuple_v(r.direction);
        printf(YELLOW "Intersection Point: " RESET);
        print_tuple_p(position(r, hit_p->t));
        printf("-------------------------------------------------------\n");
    }
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

void print_lighting_shadow(t_material *material, t_light *light, t_tuple point, t_tuple eyev, t_tuple normalv, bool in_shadow)
{
    printf(GREEN "Material: \n" RESET);
    print_material(material);
    printf(GREEN "Light position: \n" RESET);
    print_tuple_p(light->position);
    printf(GREEN "Point: \n" RESET);
    print_tuple_p(point);
    printf(GREEN "Eye vector: \n" RESET);
    print_tuple_v(eyev);
    printf(GREEN "Normal vector: \n" RESET);
    print_tuple_v(normalv);
    printf(GREEN "In shadow: \n" RESET);
    printf("%s\n", in_shadow ? "true" : "false");
}

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
            print_lighting_shadow(comps->shape->material, &world->light, comps->over_point, comps->eyev, comps->normalv, comps->inside);
            printf(BOLD MAGENTA "Color from pixel: " RESET);
            print_color(*result);
            uint32_t pixel_color = color_to_pixel(*result);
            printf(BOLD GREEN "Pixel Color: " RESET "%x\n", pixel_color);

        }
    }
}

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
void print_matrix(t_matrix *m)
{
    if (!m)
    {
        printf("Matrix is NULL\n");
        return;
    }

    for (int i = 0; i < m->y; i++)
    {
        for (int j = 0; j < m->x; j++)
        {
            printf("%f ", get_matrix_element(m, i, j));
        }
        printf("\n");
    }
    printf("\n");
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
    printf("4. Transform: \n");
    print_matrix(shape->transform);
}

void print_plane(t_shape *shape)
{
    t_plane    *pl;

    pl = (t_plane *)(shape)->object;
    printf(YELLOW "Plane:\n" RESET);
    printf("Shape ID: %d\n", shape->id);
    printf("1. Point: ");
    print_tuple_p(pl->p);
    printf("3. Normal: ");
    print_tuple_v(pl->normal);
    printf("4. Color: ");
    print_color(shape->material->color);
    printf("5. Transform: \n");
    print_matrix(shape->transform);
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
    printf("5. Transform: \n");
    print_matrix(shape->transform);
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

void print_world(t_world *w, t_ray r, int x, int y)
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
    t_intersections xs = intersect_world(w, r);
    t_intersection *hit_p = hit(&xs);
    printf(GREEN "Intersections count: %d\n" RESET, xs.count);
    if (hit_p)
    {
        if ((x == w->camera.hsize / 2 && y == w->camera.vsize / 2) ||
            (x == 0 && y == 0) ||
            (x == w->camera.hsize - 1 && y == 0) ||
            (x == 0 && y == w->camera.vsize - 1) ||
            (x == w->camera.hsize - 1 && y == w->camera.vsize - 1))
        {
            printf(YELLOW "Hit at key pixel (%d, %d): " RESET "t = %f\n", x, y, hit_p->t);
            printf(YELLOW "RAY: " RESET);
            print_tuple_v(r.direction);
            printf(YELLOW "Point: " RESET);
            print_tuple_p(position(r, hit_p->t));
        }
    }
}