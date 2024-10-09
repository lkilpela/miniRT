/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkilpela <lkilpela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 23:28:53 by jlu               #+#    #+#             */
/*   Updated: 2024/10/09 15:25:19 by lkilpela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

// Forward Declarations
typedef struct s_shape	t_shape;
typedef struct s_tuple	t_tuple;

/* MATRIX STRUCT */
typedef struct s_matrix
{
	float	data[4][4];
	int		x; // cols
	int		y; // rows
}				t_matrix;

/* MATRIX_MATH.C */
t_matrix	multiply_matrices(t_matrix a, t_matrix b);
t_tuple		matrix_multiply_tuple(t_matrix m, t_tuple t);
bool		float_equals(float a, float b, float epsilon);

/* MATRIX.C */
t_matrix	create_matrix(int x, int y);
float		get_matrix_element(t_matrix matrix, int row, int col);
t_matrix	identity_matrix(void);
t_matrix	transpose_matrix(t_matrix a);
t_matrix	submatrix(t_matrix a, int row, int col);

/* MATRIX1.C */
t_matrix	inverse(t_matrix m);

/* TRANSFORMATIONS.C */
t_matrix	translation(float x, float y, float z);
t_matrix	scaling(float x, float y, float z);
t_matrix	rotation(t_tuple axis, t_tuple u);
void		chaining_transformations(t_shape *shape,
				t_matrix combine_rotations,
				t_matrix scaling_matrix,
				t_matrix translation_matrix);
#endif
