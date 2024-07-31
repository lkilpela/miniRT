#include "tuple.h"

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
    return c;
}
void write_pixel(t_canvas *canvas, int x, int y, t_color color)
{
    if (x >= 0 && x < canvas->width && y >= 0 && y <= canvas->height)
        canvas->pixels[y][x] = color;
}

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

    // Free allocated memory
    for (int i = 0; i < c.height; i++)
    {
        free(c.pixels[i]);
    }
    free(c.pixels);
}

void test_write_pixel()
{
    t_canvas c = create_canvas(10, 20);
    t_color red = create_color(1, 0, 0);
    write_pixel(&c, 2, 3, red);
    t_color result = pixel_at(&c, 2, 3);
    printf("Pixel at (2,3): (%f, %f, %f)\n", result.red, result.green, result.blue);

    // Free allocated memory
    for (int i = 0; i < c.height; i++) {
        free(c.pixels[i]);
    }
    free(c.pixels);
}