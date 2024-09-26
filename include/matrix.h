#ifndef MATRIX_H
#define MATRIX_H

// Forward Declarations
typedef struct s_shape	t_shape;
typedef struct s_tuple	t_tuple;

/* MATRIX STRUCT */
typedef struct s_matrix
{
	float **data;
	int x; // cols
	int y; // rows
}				t_matrix;

/* MATRIX.C */
t_matrix	*allocate_matrix(int y, int x);
t_matrix	*create_matrix(int x, int y, float values[y][x]);
float		get_matrix_element(t_matrix *matrix, int row, int col);
t_matrix	*multiply_matrices(t_matrix *a, t_matrix *b);
t_tuple		matrix_multiply_tuple(t_matrix *m, t_tuple t);
t_matrix	*identity_matrix(int size);
t_matrix	*transpose_matrix(t_matrix *a);
float		determinant_2x2(t_matrix *a);
float		determinant(t_matrix *m);
t_matrix	*submatrix(t_matrix *a, int row, int col);
float		minor(t_matrix *a, int row, int col);
float		cofactor(t_matrix *a, int row, int col);
t_matrix	*inverse(t_matrix *m);
bool		float_equals(float a, float b, float epsilon);

/* TRANSFORMATIONS.C */
t_matrix	*translation(float x, float y, float z);
t_matrix	*scaling(float x, float y, float z);
t_matrix	*rotation_x(float radians);
t_matrix	*shearing(float xy, float xz, float yx, float yz, float zx, float zy);
t_matrix	*view_transform(t_tuple from, t_tuple to, t_tuple up);
void		*chaining_transformations(t_shape *shape,
							t_matrix *translation_matrix,
							t_matrix *scaling_matrix,
							t_matrix *combine_rotations);

/* ROTATION.C*/
t_matrix	*rotation_x(float radians);
t_matrix	*rotation_y(float radians);
t_matrix	*rotation_z(float radians);
t_matrix	*combine_rotations(float radians_x,
                            float radians_y,
                            float radians_z);

/* MATRIX_UTILS.C */
void	*check_memory_fail(void *ptr, t_matrix *m);
void	destroy_matrix(t_matrix *m);

// bool	matrices_are_equal(t_matrix *a, t_matrix *b);

#endif