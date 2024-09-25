#include "structs.h"

t_world *create_scene(char *filename)
{
	t_world *world = default_world();

	parse_scene(filename, world);
	
	setup_camera(&world->camera);

}