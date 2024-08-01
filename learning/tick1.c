#include <stdio.h>
#include <stdlib.h>
#include "tuple.h"
#include "color.h"

typedef struct s_projectile
{
    t_tuple position;
    t_tuple velocity;
}              t_projectile;

typedef struct s_environment
{
    t_tuple gravity;
    t_tuple wind;
}               t_environment;


t_canvas canvas_create(int width, int height)
{
    t_canvas canvas;
    canvas.width = width;
    canvas.height = height;
    canvas.pixels = (t_color *)malloc(width * height * sizeof(t_color));
    for (int i = 0; i < width * height; i++)
    {
        canvas.pixels[i] = create_color(0, 0, 0); // Initialize all pixels to black
    }
    return canvas;
}

void canvas_write_pixel(t_canvas *canvas, int x, int y, t_color color)
{
    if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
    {
        canvas->pixels[y * canvas->width + x] = color;
    }
}

char* canvas_to_ppm(t_canvas *canvas)
{
    int header_size = snprintf(NULL, 0, "P3\n%d %d\n255\n", canvas->width, canvas->height);
    int pixel_data_size = 0;
    for (int y = 0; y < canvas->height; y++)
    {
        for (int x = 0; x < canvas->width; x++)
        {
            t_color pixel = canvas->pixels[y * canvas->width + x];
            pixel_data_size += snprintf(NULL, 0, "%d %d %d ", (int)(pixel.red * 255), (int)(pixel.green * 255), (int)(pixel.blue * 255));
        }
        pixel_data_size += 1; // For the newline character at the end of each row
    }

    char *ppm = malloc((header_size + pixel_data_size + 1) * sizeof(char)); // +1 for the null terminator
    if (!ppm)
    {
        perror("Failed to allocate memory");
        return NULL;
    }

    sprintf(ppm, "P3\n%d %d\n255\n", canvas->width, canvas->height);

    char *ptr = ppm + header_size;
    for (int y = 0; y < canvas->height; y++)
    {
        for (int x = 0; x < canvas->width; x++)
        {
            t_color pixel = canvas->pixels[y * canvas->width + x];
            ptr += sprintf(ptr, "%d %d %d ", (int)(pixel.red * 255), (int)(pixel.green * 255), (int)(pixel.blue * 255));
        }
        *ptr++ = '\n';
    }

    return ppm;
}

t_projectile tick(t_environment env, t_projectile proj)
{
    t_tuple new_position = add(proj.position, proj.velocity);
    t_tuple new_velocity = add(add(proj.velocity, env.gravity), env.wind);
    t_projectile new_proj = {new_position, new_velocity};
    return new_proj;
}

int main()
{
    t_tuple init_position = point(0, 1, 0);
    t_tuple init_velocity = normalize(vector(1, 1.8, 0));
    t_projectile p = {init_position, init_velocity};
    t_environment e = {vector(0, -0.1, 0), vector(-0.01, 0, 0)};
    t_canvas canvas = canvas_create(900, 550);

    int ticks = 0;
    while (p.position.y > 0)
    {
        int x = (int)p.position.x;
        int y = canvas.height - (int)p.position.y; // Convert to canvas coordinates
        canvas_write_pixel(&canvas, x, y, create_color(1, 1, 1)); // Plot the point as white
        p = tick(e, p);
        ticks++;
    }

    char *ppm = canvas_to_ppm(&canvas);
    FILE *file = fopen("trajectory.ppm", "w");
    if (file)
    {
        fputs(ppm, file);
        fclose(file);
    }
    free(ppm);
    free(canvas.pixels);

    return 0;
}