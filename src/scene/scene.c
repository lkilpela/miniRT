#include "structs.h"

t_world *create_scene(char *filename)
{
	t_world *w;

	w = default_world();

	parse_scene(filename, w);
	
	print_world(w);

	return (w);
}