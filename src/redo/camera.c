#include "structs.h"

# define BPP sizeof(int32_t) /* Only support RGBA */
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
    destroy_matrix(inverse_transform);
    return ray(origin, direction);
}

// Convert t_color to uint32_t pixel
uint32_t color_to_pixel(t_color color)
{
	/*
    int r;
	int g;
	int b;

	r = (int)(fmin(1.0, fmax(0.0, color.r)) * 255.0);
	g = (int)(fmin(1.0, fmax(0.0, color.g)) * 255.0);
	b = (int)(fmin(1.0, fmax(0.0, color.b)) * 255.0);
	return ((uint32_t)(r << 24 | g << 16 | b << 8 ));*/
    return ((int)(color.r * 255) << 24) | ((int)(color.g * 255) << 16) |  ((int)(color.b * 255) << 8) | 0xFF;
}

// Convert uint32_t pixel to t_color
t_color color_from_pixel(uint32_t pixel)
{
    t_color color;
    color.r = fmin(1.0, ((pixel >> 24) & 0xFF) / 255.0);
    color.g = fmin(1.0, ((pixel >> 16) & 0xFF)/ 255.0);
    color.b = fmin(1.0, ((pixel >> 8) & 0xFF) / 255.0);
    return color;
}

// Get the pixel color at (x, y) in an MLX42 image
uint32_t pixel_at(mlx_image_t *img, int x, int y)
{
    uint8_t* s = &img->pixels[(y * img->width + x) * BPP];
    return (s[0] << 24) | (s[1] << 16) | (s[2] << 8);
}

// Create an image and set pixels
void    render(mlx_image_t *img, t_camera *camera, t_world *world)
{
    //printf("Camera: %f %f %f\n", camera->hsize, camera->vsize, camera->field_of_view);

    for (int y = 0; y < camera->vsize; y++) 
    {
        for (int x = 0; x < camera->hsize; x++)
        {
            if (x >= camera->hsize || y >= camera->vsize)
            {
                fprintf(stderr, "Pixel coordinates out of bounds: (%d, %d)\n", x, y);
                continue;
            }            
            t_ray r = ray_for_pixel(camera, x, y);
            t_color color = color_at(world, r, x, y, camera);
            //print_color(color);
            uint32_t pixel_color = color_to_pixel(color);
            //printf("Pixel Color: %x\n", pixel_color);
            mlx_put_pixel(img, x, y, pixel_color);

            /*
            //Print ray directions at key pixels
            if ((x == camera->hsize / 2 && y == camera->vsize / 2) || // Center
                (x == 0 && y == 0) || // Top-Left Corner
                (x == camera->hsize - 1 && y == 0) || // Top-Right Corner
                (x == 0 && y == camera->vsize - 1) || // Bottom-Left Corner
                (x == camera->hsize - 1 && y == camera->vsize - 1))
                { // Bottom-Right Corner
                    printf("Key Pixel (%d, %d):\n", x, y);
                    printf("Ray: \n");
                    print_tuple(r.origin);
                    print_tuple(r.direction);
                } */
        }
    }
}
/*
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

void test_render()
{
     // Initialize the MLX42 library
    mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "MLX42 Window", true);
    if (!mlx) {
        fprintf(stderr, "MLX42 initialization failed\n");
        exit(1);
    }

    // Test: Rendering a world with a camera
    t_world *w = default_world();
    t_camera c = camera(11, 11, M_PI / 2);
    setup_camera(&c);
    t_tuple from = point(0, 0, -5);
    t_tuple to = point(0, 0, 0);
    t_tuple up = vector(0, 1, 0);
    c.transform = view_transform(from, to, up);
    
    // Debug: Print camera setup
    //printf("Camera setup:\n");
    //printf("hsize: %f, vsize: %f, field_of_view: %f\n", c.hsize, c.vsize, c.field_of_view);
    //printf("transform: \n");
    //print_matrix(c.transform);

    mlx_image_t *img = render(&c, w, mlx);
    //printf("mlx_image_t: %d %d\n", img->width, img->height);
    uint32_t pixel_color = pixel_at(img, 5, 5);
    printf("Test_Pixel Color: %x\n", pixel_color);
    t_color color1 = color_from_pixel(pixel_color);
    print_color(color1); // Color: 0.380392 0.474510 0.282353
    t_color expected = color(0.38066, 0.47583, 0.2855);
    assert(color_equal(color1, expected, EPSILON));
    printf("Passed: Rendering a world with a camera\n");

    //mlx_delete_image(mlx, img);
    //mlx_terminate(mlx);
}*/
