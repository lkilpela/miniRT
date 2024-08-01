#include "color.h"
#include "tuple.h"

char* canvas_to_ppm(t_canvas *canvas)
{
    // Calculate the size needed for the PPM header
    int header_size = snprintf(NULL, 0, "P3\n%d %d\n255\n", canvas->width, canvas->height);
    
    // Calculate the size needed for the pixel data
    int pixel_data_size = 0;
    for (int y = 0; y < canvas->height; y++) {
        for (int x = 0; x < canvas->width; x++) {
            t_color pixel = canvas->pixels[y][x];
            pixel_data_size += snprintf(NULL, 0, "%f %f %f ", pixel.red, pixel.green, pixel.blue);
        }
        pixel_data_size += 1; // For the newline character at the end of each row
    }

    // Allocate the required memory
    char *ppm = malloc((header_size + pixel_data_size + 1) * sizeof(char)); // +1 for the null terminator
    if (!ppm) {
        perror("Failed to allocate memory");
        return NULL;
    }

    // Write the PPM header
    sprintf(ppm, "P3\n%d %d\n255\n", canvas->width, canvas->height);

    // Write the pixel data
    char *ptr = ppm + header_size;
    int line_length = 0;
    for (int y = 0; y < canvas->height; y++) {
        for (int x = 0; x < canvas->width; x++) {
            t_color pixel = canvas->pixels[y][x];
            int len = snprintf(ptr, 12, "%f %f %f ", pixel.red, pixel.green, pixel.blue);
            if (line_length + len > 70) {
                *ptr++ = '\n';
                line_length = 0;
            }
            ptr += len;
            line_length += len;
        }
        *ptr++ = '\n';
        line_length = 0;
    }

    // Ensure the file ends with a newline character
    if (*(ptr - 1) != '\n') {
        *ptr++ = '\n';
    }
    *ptr = '\0';

    return ppm;
}

// Helper function to compare strings
int compare_strings(const char *str1, const char *str2) {
    return strcmp(str1, str2) == 0;
}

// Helper function to check if a string ends with a newline character
int ends_with_newline(const char *str) {
    size_t len = strlen(str);
    return len > 0 && str[len - 1] == '\n';
}

void free_canvas(t_canvas *c) {
    free(c->pixels);
    free(c);
}

void test_constructing_ppm_pixel_data() {
    t_canvas *c = create_canvas(5, 3);
    t_color c1 = create_color(1.5, 0, 0);
    t_color c2 = create_color(0, 0.5, 0);
    t_color c3 = create_color(-0.5, 0, 1);

    c->write_pixel(c, 0, 0, c1);
    c->write_pixel(c, 2, 1, c2);
    c->write_pixel(c, 4, 2, c3);

    char *ppm = canvas_to_ppm(c);

    const char *expected = 
        "P3\n5 3\n255\n"
        "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
        "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";

    if (!compare_strings(ppm, expected)) {
        printf("test_constructing_ppm_pixel_data failed\n");
    } else {
        printf("test_constructing_ppm_pixel_data passed\n");
    }

    free(ppm);
    free_canvas(c);
}

void test_splitting_long_lines_in_ppm_files() {
    t_canvas *c = canvas(10, 2);
    t_color color = create_color(1, 0.8, 0.6);

    for (int y = 0; y < c->height; y++) {
        for (int x = 0; x < c->width; x++) {
            write_pixel(c, x, y, color);
        }
    }

    char *ppm = canvas_to_ppm(c);

    const char *expected = 
        "P3\n10 2\n255\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
        "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
        "153 255 204 153 255 204 153 255 204 153 255 204 153\n";

    if (!compare_strings(ppm, expected)) {
        printf("test_splitting_long_lines_in_ppm_files failed\n");
    } else {
        printf("test_splitting_long_lines_in_ppm_files passed\n");
    }

    free(ppm);
    free_canvas(c);
}

void test_ppm_files_terminated_by_newline() {
    t_canvas *c = create_canvas(5, 3);
    char *ppm = canvas_to_ppm(c);

    if (!ends_with_newline(ppm)) {
        printf("test_ppm_files_terminated_by_newline failed\n");
    } else {
        printf("test_ppm_files_terminated_by_newline passed\n");
    }

    free(ppm);
    free_canvas(c);
}

int main() {
    test_constructing_ppm_pixel_data();
    test_splitting_long_lines_in_ppm_files();
    test_ppm_files_terminated_by_newline();
    return 0;
}