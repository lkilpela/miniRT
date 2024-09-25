#include "shapes.h"

/* TRANSLATION
** Return a 4x4 translation matrix
** Set the translation values:
** - in the last column of the 4x4 matrix,
** which shifts points by (x, y, z) when the matrix is applied.
** translation(5, -3, 2), the matrix will be:
| 1  0  0  5  |
| 0  1  0  -3 |
| 0  0  1  2  |
| 0  0  0  1  |
            ^ set translation values
*/
t_matrix	*translation(float x, float y, float z)
{
	t_matrix	*m;
	
	m = identity_matrix(4);
	m->data[0][3] = x;
	m->data[1][3] = y;
	m->data[2][3] = z;
	return (m);
}

/* SCALING
** Return a 4x4 scaling matrix
*/
t_matrix	*scaling(float x, float y, float z)
{
	t_matrix	*m;

	m = identity_matrix(4);
	m->data[0][0] = x;
	m->data[1][0] = 0;
	m->data[2][0] = 0;
	m->data[3][0] = 0;
	m->data[0][1] = 0;
	m->data[1][1] = y;
	m->data[2][1] = 0;
	m->data[3][1] = 0;
	m->data[0][2] = 0;
	m->data[1][2] = 0;
	m->data[2][2] = z;
	m->data[3][2] = 0;
	m->data[0][3] = 0;
	m->data[1][3] = 0;
	m->data[2][3] = 0;
	m->data[3][3] = 1;
	return (m);
}

/* SHEARING
** The effect of making straight lines not slanted.
** For example: x is initially 2, but moving x in proportion to y adds 1 times y (or 3) to x (2) 
and produces a new x of 5.
** Check test_shearing() for more examples
*/
t_matrix	*shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
	t_matrix	*m;

	m = identity_matrix(4);
	m->data[0][1] = xy; // x moved in proportion to y
	m->data[0][2] = xz; // x moved in proportion to z
	m->data[1][0] = yx; // y moved in proportion to x
	m->data[1][2] = yz; // y moved in proportion to z
	m->data[2][0] = zx; // z moved in proportion to x
	m->data[2][1] = zy; // z moved in proportion to y
	return (m);
	}

/* DEFINING VIEW TRANSFORMATION 
** Pretends the eye moves instead of the world
** - Specify where you want the eye to be in the scene (from)
** - Specify where you want the eye to look at (to)
** - Specify the direction of the up vector (up)
** - Return a view transformation matrix
*/
t_matrix	*view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple forward;
	t_tuple left;
	t_tuple true_up;
	t_matrix *orientation;

	forward = normalize(subtract(to, from));
	left = cross(forward, normalize(up));
	true_up = cross(left, forward);
	orientation = identity_matrix(4);
	orientation->data[0][0] = left.x;
	orientation->data[0][1] = left.y;
	orientation->data[0][2] = left.z;
	orientation->data[1][0] = true_up.x;
	orientation->data[1][1] = true_up.y;
	orientation->data[1][2] = true_up.z;
	orientation->data[2][0] = -forward.x;
	orientation->data[2][1] = -forward.y;
	orientation->data[2][2] = -forward.z;
	return (multiply_matrices(orientation,
			translation(-from.x, -from.y, -from.z)));
}

/* CHAINING TRANSFORMATIONS
** Apply a series of transformations to a shape
*/
void chaining_transformations(t_shape *shape,
							t_matrix *translation_matrix, 
							t_matrix *scaling_matrix,
							t_matrix *combine_rotations)
{
	// Combine transformations: scaling -> rotation -> translation
	t_matrix *combined_matrix = multiply_matrices(combine_rotations, scaling_matrix);
	t_matrix *final_matrix = multiply_matrices(translation_matrix, combined_matrix);

	// Apply the combined transformation to the shape
	t_matrix *new_transform = multiply_matrices(shape->transform, final_matrix);

	// Free the old transformation matrix if necessary
	free(shape->transform);
	shape->transform = new_transform;

	// Free intermediate matrices
	free(combined_matrix);
	free(final_matrix);
}
