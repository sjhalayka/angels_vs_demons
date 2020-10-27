

#ifndef matrix_utils_h
#define matrix_utils_h

#include <stdio.h>
#include "primitives.h"

void get_identity_matrix(float(&mat)[16]);

void get_perspective_matrix(float fovy, float aspect, float znear, float zfar, float (&mat)[16]);

void get_look_at_matrix(float eyex, float eyey, float eyez, float centrex, float centrey, float centrez, float upx, float upy, float upz, float (&mat)[16]);

void multiply_4x4_matrices(const float (&in_a)[16], const float (&in_b)[16], float (&out)[16]);

// http://www.math-cs.gordon.edu/courses/cps343/presentations/Matrix_Mult.pdf
void multiply_4x4_matrix_by_4_vector(const float(&in_a)[16], const float(&in_b)[4], float(&out)[4]);

void init_perspective_camera(float fovy, float aspect, float znear, float zfar,
                             float eyex, float eyey, float eyez,
                             float centrex, float centrey, float centrez,
                             float upx, float upy, float upz,
                             float (&projection_modelview_mat)[16],
                             float (&projection_mat)[16],
                             float (&modelview_mat)[16]);


vertex_3 get_screen_coords_from_world_coords(const vertex_3 p, 
                                             const vertex_3 c, 
                                             const float(&projection_mat)[16], 
                                             const float(&model_view)[16],
                                             const int width, 
                                             const int height);


float lin_interp(float v0, float v1, float t);

vertex_3 lin_interp(vertex_3 v0, vertex_3 v1, float t);

#endif
