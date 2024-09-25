#include "structs.h"

void add_object(t_world *world, t_shape* object)
{
    world->object = realloc(world->object, (world->count + 1) * sizeof(t_shape));
    world->object[world->count] = *object;
    world->count++;
}

// Function to create the scene
t_world *create_scene()
{
    t_world *world = default_world();

    // Plane
    t_shape *pl = plane();
    pl->material.color = color(1, 0.9, 0.9);
    add_object(world, pl);

    // Middle sphere
    t_shape*middle = sphere();
    middle->transform = translation(-0.5, 1, 0.5);
    middle->material = material();
    middle->material.color = color(0.1, 1, 0.5);
    middle->material.diffuse = 0.7;
    middle->material.specular = 0.3;
    add_object(world, middle);

    // Right sphere
    t_shape* right = sphere();
    right->transform = multiply_matrices(
        translation(1.5, 0.5, -0.5),
        scaling(0.5, 0.5, 0.5)
    );
    right->material = material();
    right->material.color = color(0.5, 1, 0.1);
    right->material.diffuse = 0.7;
    right->material.specular = 0.3;
    add_object(world, right);

    // Left sphere
    t_shape *left = sphere();
    left->transform = multiply_matrices(
        translation(-1.5, 0.33, -0.75),
        scaling(0.33, 0.33, 0.33)
    );
    left->material = material();
    left->material.color = color(1, 0.8, 0.1);
    left->material.diffuse = 0.7;
    left->material.specular = 0.3;
    add_object(world, left);

    return world;
}