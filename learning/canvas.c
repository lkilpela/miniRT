#include "tuple.h"
#include "color.h"

t_canvas create_canvas(int width, int height)
{
    t_canvas c;
    int i = 0;

    c.width = width;
    c.height = height;
    c.pixels = malloc(height * sizeof(t_color *));
    while (i < height)
    {
        c.pixels[i] = malloc(width * sizeof(t_color));
        int j = 0;
        while (j < width)
        {
            c.pixels[i][j] = create_color(0, 0, 0);
            j++;
        }
        i++;
    }
    c.create = create_canvas;
    c.destroy = destroy_canvas;
    c.write_pixel = write_pixel;
    c.pixel_at = pixel_at;
    return c;
}

// Canvas destructor
void destroy_canvas(t_canvas *canvas)
{
    // Free allocated memory
    int i = 0;
    while (i < canvas->height)
    {
        free(canvas->pixels[i]);
        i++;
    }
    free(canvas->pixels);
    canvas->pixels = NULL;
}

// Set pixel color
void write_pixel(t_canvas *canvas, int x, int y, t_color color)
{
    if (x >= 0 && x < canvas->width && y >= 0 && y <= canvas->height)
        canvas->pixels[y][x] = color;
}

// Get pixel color
t_color pixel_at(t_canvas *canvas, int x, int y)
{
    if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
        return canvas->pixels[y][x];
    return create_color(0, 0, 0); // Return black if out of bounds
}

void test_canvas()
{
    t_canvas c = create_canvas(10, 20);
    printf("Canvas width: %d\n", c.width);
    printf("Canvas height: %d\n", c.height);
    printf("Pixel at (0,0): (%f, %f, %f)\n", c.pixels[0][0].red, c.pixels[0][0].green, c.pixels[0][0].blue);

    // Test setting a pixel color
    t_color red = create_color(1, 0, 0);
    write_pixel(&c, 2, 3, red);
    t_color pixel = pixel_at(&c, 2, 3);
    printf("Pixel at (2,3): (%f, %f, %f)\n", pixel.red, pixel.green, pixel.blue);

    // Test out-of-bounds access
    pixel = pixel_at(&c, -1, -1);
    printf("Pixel at (-1,-1): (%f, %f, %f)\n", pixel.red, pixel.green, pixel.blue);

    destroy_canvas(&c);
    printf("Canvas destroyed.\n");
}

char* canvas_to_ppm(t_canvas *canvas) {
    char *ppm = malloc(1000 * sizeof(char)); // Allocate enough space for the header
    sprintf(ppm, "P3\n%d %d\n255\n", canvas->width, canvas->height);
    return ppm;
}

void test_canvas_to_ppm() {
    t_canvas c = create_canvas(5, 3);
    char *ppm = canvas_to_ppm(&c);
    printf("PPM Header:\n%s", ppm);

    // Free allocated memory
    for (int i = 0; i < c.height; i++) {
        free(c.pixels[i]);
    }
    free(c.pixels);
    free(ppm);
}