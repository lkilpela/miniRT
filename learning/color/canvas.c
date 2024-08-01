#include "/Users/lumikilpelainen/workspace/miniRT/learning/tuple.h"
#include "color.h"

t_canvas *create_canvas(int width, int height)
{
    t_canvas *c;
    int i = 0;

    c = malloc(sizeof(t_canvas));
    if (!c) return NULL; // Check for allocation failure
    c->width = width;
    c->height = height;
    c->pixels = malloc(width * height * sizeof(t_color));
    if (!c->pixels) 
    {
        free(c); // Free previously allocated memory
        return NULL; // Check for allocation failure
    }
    while (i < height)
    {
        int j = 0;
        while (j < width)
        {
            c->pixels[i * width + j] = create_color(0, 0, 0);
            j++;
        }
        i++;
    }
    c->create = create_canvas;
    c->destroy = destroy_canvas;
    c->write_pixel = write_pixel;
    c->pixel_at = pixel_at;
    return c;
}

// Canvas destructor
void destroy_canvas(t_canvas *canvas)
{
    if (canvas) 
    {
        free(canvas->pixels); // Free allocated memory for pixels
        free(canvas); // Free the canvas itself
    }
}

// Set pixel color
void write_pixel(t_canvas *canvas, int x, int y, t_color color)
{
    if (x >= 0 && x < canvas->width && y >= 0 && y <= canvas->height)
        canvas->pixels[y * canvas->width + x] = color;
}

// Get pixel color
t_color pixel_at(t_canvas *canvas, int x, int y)
{
    if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
        return canvas->pixels[y * canvas->width + x];
    return create_color(0, 0, 0); // Return black if out of bounds
}

void test_canvas()
{
    t_canvas *c = create_canvas(10, 20);
    if (!c) {
        printf("Failed to create canvas.\n");
        return;
    }
    printf("Canvas width: %d\n", c->width);
    printf("Canvas height: %d\n", c->height);
    printf("Pixel at (0,0): (%f, %f, %f)\n", c->pixels[0].red, c->pixels[0].green, c->pixels[0].blue);

    // Test setting a pixel color
    t_color red = create_color(1, 0, 0);
    write_pixel(&c, 2, 3, red);
    t_color pixel = pixel_at(&c, 2, 3);
    printf("Pixel at (2,3): (%f, %f, %f)\n", pixel.red, pixel.green, pixel.blue);

    // Test out-of-bounds access
    pixel = pixel_at(&c, -1, -1);
    printf("Pixel at (-1,-1): (%f, %f, %f)\n", pixel.red, pixel.green, pixel.blue);

    c->destroy(c);
    printf("Canvas destroyed.\n");
}

