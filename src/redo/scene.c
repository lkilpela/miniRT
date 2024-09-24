#include "structs.h"

void add_object(t_world *world, t_sphere *object)
{
    world->spheres = realloc(world->spheres, (world->count + 1) * sizeof(t_sphere));
    world->spheres[world->count] = *object;
    world->count++;
}

// Function to create and return a world with a light source and objects for shadow testing
t_world *create_shadow_test_scene()
{
    t_world *world = default_world();

    // Set the light source
    world->light = point_light(point(-10.0, 10.0, -10.0), color(1.0, 1.0, 1.0));

    // Create and configure the floor sphere
    t_sphere floor = sphere();
    floor.transform = scaling(10, 0.01, 10);
    floor.material = material();
    floor.material.color = color(1.0, 0.9, 0.9); // Light pink color
    floor.material.specular = 0;
    add_object(world, &floor);

    // Create and configure the shadow-casting sphere
    t_sphere shadow_sphere = sphere();
    shadow_sphere.transform = translation(0, 1, 0);
    shadow_sphere.material = material();
    shadow_sphere.material.color = color(0.1, 0.1, 0.1); // Dark gray color
    add_object(world, &shadow_sphere);

    return world;
}

// Function to create and return a world with a light source and objects
t_world *get_world()
{
    t_world *world = default_world();

    // Set the light source
    world->light = point_light(point(20.0, 16.0, 0.0), color(1.0, 1.0, 1.0));

    // Create and configure the earth sphere
    t_sphere earth = sphere();
    earth.material = material();
    earth.material.color = color(0.0, 0.0, 1.0); // Blue color
    add_object(world, &earth);

    // Create and configure the moon sphere
    t_sphere moon = sphere();
    moon.transform = multiply_matrices(translation(1.25, 1.25, 0.0), scaling(0.25, 0.25, 0.25));
    moon.material = material();
    moon.material.color = color(0.8, 0.8, 0.8); // Gray color
    moon.material.shininess = 10.0;
    add_object(world, &moon);

    return world;
}

// Function to create the scene
t_world *create_hand_dog_scene()
{
    t_world *world = default_world();

    // Create a light source
    world->light = point_light(point(-10, 10, -10), color(1, 1, 1));

    // Create spheres to form a hand making a dog barking shadow
    // Palm
    t_sphere palm = sphere();
    palm.transform = multiply_matrices(translation(0, 0, 0), scaling(1, 0.5, 0.5));
    palm.material = material();
    palm.material.color = color(0.8, 0.6, 0.4); // Brown color
    add_object(world, &palm);

    // Thumb
    t_sphere thumb = sphere();
    thumb.transform = multiply_matrices(translation(-1.2, 0.5, 0), scaling(0.3, 0.3, 0.3));
    thumb.material = material();
    thumb.material.color = color(0.9, 0.1, 0.1); // Red color
    add_object(world, &thumb);

    // Index finger
    t_sphere index_finger = sphere();
    index_finger.transform = multiply_matrices(translation(0.5, 1.0, 0), scaling(0.3, 0.8, 0.3));
    index_finger.material = material();
    index_finger.material.color = color(0.1, 0.9, 0.1); // Green color
    add_object(world, &index_finger);

    // Middle finger
    t_sphere middle_finger = sphere();
    middle_finger.transform = multiply_matrices(translation(0, 1.2, 0), scaling(0.3, 1.0, 0.3));
    middle_finger.material = material();
    middle_finger.material.color = color(0.1, 0.1, 0.9); // Blue color
    add_object(world, &middle_finger);

    // Ring finger
    t_sphere ring_finger = sphere();
    ring_finger.transform = multiply_matrices(translation(-0.5, 1.0, 0), scaling(0.3, 0.8, 0.3));
    ring_finger.material = material();
    ring_finger.material.color = color(0.9, 0.9, 0.1); // Yellow color
    add_object(world, &ring_finger);

    // Pinky finger
    t_sphere pinky_finger = sphere();
    pinky_finger.transform = multiply_matrices(translation(-1.0, 0.8, 0), scaling(0.3, 0.6, 0.3));
    pinky_finger.material = material();
    pinky_finger.material.color = color(0.9, 0.1, 0.9); // Magenta color
    add_object(world, &pinky_finger);

    // Dog's head
    t_sphere dog_head = sphere();
    dog_head.transform = multiply_matrices(translation(1.5, 0.5, 0), scaling(0.5, 0.5, 0.5));
    dog_head.material = material();
    dog_head.material.color = color(0.5, 0.5, 0.5); // Gray color
    add_object(world, &dog_head);

    // Dog's ear 1
    t_sphere dog_ear1 = sphere();
    dog_ear1.transform = multiply_matrices(translation(1.8, 1.0, -0.3), scaling(0.2, 0.4, 0.2));
    dog_ear1.material = material();
    dog_ear1.material.color = color(0.3, 0.2, 0.1); // Dark brown color
    add_object(world, &dog_ear1);

    // Dog's ear 2
    t_sphere dog_ear2 = sphere();
    dog_ear2.transform = multiply_matrices(translation(1.8, 1.0, 0.3), scaling(0.2, 0.4, 0.2));
    dog_ear2.material = material();
    dog_ear2.material.color = color(0.3, 0.2, 0.1); // Dark brown color
    add_object(world, &dog_ear2);

    return world;
}

// Function to create the scene
t_world *create_dog_scene()
{
    t_world *world = default_world();

    // Create a light source
    world->light = point_light(point(-10, 10, -10), color(1, 1, 1));

    // Create spheres to form a dog-like shape
    t_sphere body = sphere();
    body.transform = multiply_matrices(translation(0, 0, 0), scaling(1, 0.5, 0.5));
    body.material = material();
    body.material.color = color(0.5, 0.5, 0.5);

    t_sphere head = sphere();
    head.transform = multiply_matrices(translation(1.5, 0.5, 0), scaling(0.5, 0.5, 0.5));
    head.material = material();
    head.material.color = color(0.5, 0.5, 0.5);

    t_sphere ear1 = sphere();
    ear1.transform = multiply_matrices(translation(1.8, 1.0, -0.3), scaling(0.2, 0.4, 0.2));
    ear1.material = material();
    ear1.material.color = color(0.5, 0.5, 0.5);

    t_sphere ear2 = sphere();
    ear2.transform = multiply_matrices(translation(1.8, 1.0, 0.3), scaling(0.2, 0.4, 0.2));
    ear2.material = material();
    ear2.material.color = color(0.5, 0.5, 0.5);

    t_sphere leg1 = sphere();
    leg1.transform = multiply_matrices(translation(-0.5, -0.5, -0.3), scaling(0.2, 0.5, 0.2));
    leg1.material = material();
    leg1.material.color = color(0.5, 0.5, 0.5);

    t_sphere leg2 = sphere();
    leg2.transform = multiply_matrices(translation(-0.5, -0.5, 0.3), scaling(0.2, 0.5, 0.2));
    leg2.material = material();
    leg2.material.color = color(0.5, 0.5, 0.5);


    t_sphere leg3 = sphere();
    leg3.transform = multiply_matrices(translation(0.5, -0.5, -0.3), scaling(0.2, 0.5, 0.2));
    leg3.material = material();
    leg3.material.color = color(0.5, 0.5, 0.5);

    t_sphere leg4 = sphere();
    leg4.transform = multiply_matrices(translation(0.5, -0.5, 0.3), scaling(0.2, 0.5, 0.2));
    leg4.material = material();
    leg4.material.color = color(0.5, 0.5, 0.5);

    t_sphere tail = sphere();
    tail.transform = multiply_matrices(translation(-1.5, 0, 0), scaling(0.2, 0.2, 0.5));
    tail.material = material();
    tail.material.color = color(0.5, 0.5, 0.5);

    // Add spheres to the world
    world->spheres = calloc(10, sizeof(t_sphere));
    world->spheres[0] = body;
    world->spheres[1] = head;
    world->spheres[2] = ear1;
    world->spheres[3] = ear2;
    world->spheres[4] = leg1;
    world->spheres[5] = leg2;
    world->spheres[6] = leg3;
    world->spheres[7] = leg4;
    world->spheres[8] = tail;
    world->count = 9;

    return world;
}


// Function to create the scene
t_world *create_scene()
{
    t_world *world = default_world();

    // Floor
    t_sphere floor = sphere();
    floor.transform = scaling(10, 0.01, 10);
    floor.material = material();
    floor.material.color = color(1, 0.9, 0.9);
    floor.material.specular = 0;

    // Left wall
    t_sphere left_wall = sphere();
    left_wall.transform = multiply_matrices(
        multiply_matrices(
            multiply_matrices(
                translation(0, 0, 5),
                rotation_y(-M_PI / 4)
            ),
            rotation_x(M_PI / 2)
        ),
        scaling(10, 0.01, 10)
    );
    left_wall.material = floor.material;

    // Right wall
    t_sphere right_wall = sphere();
    right_wall.transform = multiply_matrices(
        multiply_matrices(
            multiply_matrices(
                translation(0, 0, 5),
                rotation_y(M_PI / 4)
            ),
            rotation_x(M_PI / 2)
        ),
        scaling(10, 0.01, 10)
    );
    right_wall.material = floor.material;

    // Middle sphere
    t_sphere middle = sphere();
    middle.transform = translation(-0.5, 1, 0.5);
    middle.material = material();
    middle.material.color = color(0.1, 1, 0.5);
    middle.material.diffuse = 0.7;
    middle.material.specular = 0.3;

    // Right sphere
    t_sphere right = sphere();
    right.transform = multiply_matrices(
        translation(1.5, 0.5, -0.5),
        scaling(0.5, 0.5, 0.5)
    );
    right.material = material();
    right.material.color = color(0.5, 1, 0.1);
    right.material.diffuse = 0.7;
    right.material.specular = 0.3;

    // Left sphere
    t_sphere left = sphere();
    left.transform = multiply_matrices(
        translation(-1.5, 0.33, -0.75),
        scaling(0.33, 0.33, 0.33)
    );
    left.material = material();
    left.material.color = color(1, 0.8, 0.1);
    left.material.diffuse = 0.7;
    left.material.specular = 0.3;

    // Add spheres to the world
    world->spheres = calloc(6, sizeof(t_sphere));
    world->spheres[0] = floor;
    world->spheres[1] = left_wall;
    world->spheres[2] = right_wall;
    world->spheres[3] = middle;
    world->spheres[4] = right;
    world->spheres[5] = left;
    world->count = 6;


    return world;
}