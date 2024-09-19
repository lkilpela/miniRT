In the `minirt` project, the formulas and operations for tuples and vectors are used to perform basic mathematical calculations necessary for 3D graphics processing. Below is a summary of the purpose and usage of each operation:

1. **Add**:
   - **Purpose**: Adds the corresponding components of two tuples or vectors.
   - **Usage**: `t_tuple result = add(a, b);`
   - **Example**: `(x1, y1, z1) + (x2, y2, z2) = (x1 + x2, y1 + y2, z1 + z2)`

2. **Subtract**:
   - **Purpose**: Subtracts the corresponding components of one tuple or vector from another.
   - **Usage**: `t_tuple result = subtract(a, b);`
   - **Example**: `(x1, y1, z1) - (x2, y2, z2) = (x1 - x2, y1 - y2, z1 - z2)`

3. **Dot Product**:
   - **Purpose**: Computes the sum of the products of the corresponding components of two vectors.
   - **Usage**: `double result = dot(a, b);`
   - **Example**: `(x1, y1, z1) • (x2, y2, z2) = x1*x2 + y1*y2 + z1*z2`

4. **Cross Product**:
   - **Purpose**: Computes a vector that is perpendicular to two given vectors.
   - **Usage**: `t_tuple result = cross(a, b);`
   - **Example**: `(x1, y1, z1) × (x2, y2, z2) = (y1*z2 - z1*y2, z1*x2 - x1*z2, x1*y2 - y1*x2)`

5. **Negate**:
   - **Purpose**: Negates each component of a tuple or vector.
   - **Usage**: `t_tuple result = negate(a);`
   - **Example**: `-(x, y, z) = (-x, -y, -z)`

6. **Normalize**:
   - **Purpose**: Converts a vector to a unit vector (a vector with magnitude 1) by dividing each component by the vector's magnitude.
   - **Usage**: `t_tuple result = normalize(a);`
   - **Example**: `normalize((x, y, z)) = (x/m, y/m, z/m)` where `m` is the magnitude of the vector.

7. **Magnitude**:
   - **Purpose**: Computes the length of a vector.
   - **Usage**: `double result = magnitude(a);`
   - **Example**: `magnitude((x, y, z)) = sqrt(x^2 + y^2 + z^2)`

8. **Scalar Multiplication**:
   - **Purpose**: Multiplies each component of a tuple or vector by a scalar value.
   - **Usage**: `t_tuple result = scalar_multiply(a, scalar);`
   - **Example**: `scalar * (x, y, z) = (scalar*x, scalar*y, scalar*z)`

These operations are fundamental and necessary for performing vector calculations in computer graphics, especially in calculating lighting, shadows, and geometric transformations in 3D space.