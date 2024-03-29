

#include "matrix_utils.h"


void get_identity_matrix(float(&mat)[16])
{
    for (size_t i = 0; i < 16; i++)
        mat[i] = 0;

    /*
matrix layout:

[0 4  8 12]
[1 5  9 13]
[2 6 10 14]
[3 7 11 15]
*/


    mat[0] = 1;
    mat[5] = 1;
    mat[10] = 1;
    mat[15] = 1;

}


void get_perspective_matrix(float fovy, float aspect, float znear, float zfar, float (&mat)[16])
{
    // https://www.opengl.org/sdk/docs/man2/xhtml/gluPerspective.xml
    const float pi = 4.0f*atanf(1.0);
    
    // Convert fovy to radians, then divide by 2
    float       f = 1.0f / tan(fovy/360.0f*pi);
    
    mat[0] = f/aspect; mat[4] = 0; mat[8] = 0;                              mat[12] = 0;
    mat[1] = 0;        mat[5] = f; mat[9] = 0;                              mat[13] = 0;
    mat[2] = 0;        mat[6] = 0; mat[10] = (zfar + znear)/(znear - zfar); mat[14] = (2.0f*zfar*znear)/(znear - zfar);
    mat[3] = 0;        mat[7] = 0; mat[11] = -1;                            mat[15] = 0;
}

void get_look_at_matrix(float eyex, float eyey, float eyez,
                        float centrex, float centrey, float centrez,
                        float upx, float upy, float upz,
                        float (&mat)[16])
{
    // https://www.opengl.org/sdk/docs/man2/xhtml/gluLookAt.xml
    vertex_3 f, up, s, u;
    
    f.x = centrex - eyex;
    f.y = centrey - eyey;
    f.z = centrez - eyez;
    f.normalize();
    
    up.x = upx;
    up.y = upy;
    up.z = upz;
    up.normalize();
    
    s = f.cross(up);
    s.normalize();
    
    u = s.cross(f);
    u.normalize();
    
    mat[0] = s.x;  mat[4] = s.y;  mat[8] = s.z;   mat[12] = 0;
    mat[1] = u.x;  mat[5] = u.y;  mat[9] = u.z;   mat[13] = 0;
    mat[2] = -f.x; mat[6] = -f.y; mat[10] = -f.z; mat[14] = 0;
    mat[3] = 0;    mat[7] = 0;    mat[11] = 0;    mat[15] = 1;
    
    float translate[16];
    translate[0] = 1; translate[4] = 0; translate[8] = 0;  translate[12] = -eyex;
    translate[1] = 0; translate[5] = 1; translate[9] = 0;  translate[13] = -eyey;
    translate[2] = 0; translate[6] = 0; translate[10] = 1; translate[14] = -eyez;
    translate[3] = 0; translate[7] = 0; translate[11] = 0; translate[15] = 1;
    
    float temp[16];
    multiply_4x4_matrices(mat, translate, temp);
    
    for(size_t i = 0; i < 16; i++)
        mat[i] = temp[i];
}

void multiply_4x4_matrix_by_4_vector(const float(&in_a)[16], const float(&in_b)[4], float(&out)[4])
{
    float temp[4];

    for (int i = 0; i < 4; i++)
    {
        temp[i] = 0.0;

        for (int j = 0; j < 4; j++)
        {
            temp[i] += in_a[i*4 + j] * in_b[j];
        }
    }

    for (size_t i = 0; i < 4; i++)
        out[i] = temp[i];
}

void multiply_4x4_matrices(const float (&in_a)[16], const float (&in_b)[16], float (&out)[16])
{
    /*
    matrix layout:
    
    [0 4  8 12]
    [1 5  9 13]
    [2 6 10 14]
    [3 7 11 15]
    */
    
    out[0] =  in_a[0] * in_b[0] +  in_a[4] * in_b[1] +  in_a[8] *  in_b[2] +  in_a[12] * in_b[3];
    out[1] =  in_a[1] * in_b[0] +  in_a[5] * in_b[1] +  in_a[9] *  in_b[2] +  in_a[13] * in_b[3];
    out[2] =  in_a[2] * in_b[0] +  in_a[6] * in_b[1] +  in_a[10] * in_b[2] +  in_a[14] * in_b[3];
    out[3] =  in_a[3] * in_b[0] +  in_a[7] * in_b[1] +  in_a[11] * in_b[2] +  in_a[15] * in_b[3];
    out[4] =  in_a[0] * in_b[4] +  in_a[4] * in_b[5] +  in_a[8] *  in_b[6] +  in_a[12] * in_b[7];
    out[5] =  in_a[1] * in_b[4] +  in_a[5] * in_b[5] +  in_a[9] *  in_b[6] +  in_a[13] * in_b[7];
    out[6] =  in_a[2] * in_b[4] +  in_a[6] * in_b[5] +  in_a[10] * in_b[6] +  in_a[14] * in_b[7];
    out[7] =  in_a[3] * in_b[4] +  in_a[7] * in_b[5] +  in_a[11] * in_b[6] +  in_a[15] * in_b[7];
    out[8] =  in_a[0] * in_b[8] +  in_a[4] * in_b[9] +  in_a[8] *  in_b[10] + in_a[12] * in_b[11];
    out[9] =  in_a[1] * in_b[8] +  in_a[5] * in_b[9] +  in_a[9] *  in_b[10] + in_a[13] * in_b[11];
    out[10] = in_a[2] * in_b[8] +  in_a[6] * in_b[9] +  in_a[10] * in_b[10] + in_a[14] * in_b[11];
    out[11] = in_a[3] * in_b[8] +  in_a[7] * in_b[9] +  in_a[11] * in_b[10] + in_a[15] * in_b[11];
    out[12] = in_a[0] * in_b[12] + in_a[4] * in_b[13] + in_a[8] *  in_b[14] + in_a[12] * in_b[15];
    out[13] = in_a[1] * in_b[12] + in_a[5] * in_b[13] + in_a[9] *  in_b[14] + in_a[13] * in_b[15];
    out[14] = in_a[2] * in_b[12] + in_a[6] * in_b[13] + in_a[10] * in_b[14] + in_a[14] * in_b[15];
    out[15] = in_a[3] * in_b[12] + in_a[7] * in_b[13] + in_a[11] * in_b[14] + in_a[15] * in_b[15];
}

/*
void multiply_4x4_matrices(float (&in_a)[16], float (&in_b)[16], float (&out)[16])
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            out[4*i + j] = 0;
            
            for (int k = 0; k < 4; k++)
                out[4*i + j] += in_a[4*k + j] * in_b[4*i + k];
        }
    }
}
*/


void init_perspective_camera(float fovy, float aspect, float znear, float zfar,
    float eyex, float eyey, float eyez,
    float centrex, float centrey, float centrez,
    float upx, float upy, float upz,
    float(&projection_modelview_mat)[16],
    float(&projection_mat)[16],
    float(&modelview_mat)[16])
{
 //   float projection_mat[16];
    get_perspective_matrix(fovy, aspect, znear, zfar, projection_mat);
    
 //   float modelview_mat[16];
    get_look_at_matrix(eyex, eyey, eyez, // Eye position.
                       centrex, centrey, centrez, // Look at position (not direction).
                       upx, upy, upz,  // Up direction vector.
                       modelview_mat);
    
    multiply_4x4_matrices(projection_mat, modelview_mat, projection_modelview_mat);
}

vertex_3 get_screen_coords_from_world_coords(const vertex_3 p,
    const vertex_3 c,
    const float(&projection_mat)[16],
    const float(&modelview_mat)[16],
    const int width,
    const int height)
{
    vertex_3 v = p - c;

    if (v.z != 0)
    {
        v.x /= v.z;
        v.y /= v.z;
        v.z /= v.z;
    }

    float point[4];
    point[0] = c.x + v.x;
    point[1] = c.y + v.y;
    point[2] = c.z + v.z;
    point[3] = 0;

    float out0[4];
    float out1[4];

    //multiply_4x4_matrix_by_4_vector(projection_mat, point, out0);
    //multiply_4x4_matrix_by_4_vector(modelview_mat, out0, out1);

    multiply_4x4_matrix_by_4_vector(modelview_mat, point, out0);
    multiply_4x4_matrix_by_4_vector(projection_mat, out0, out1);

 //   float mat[16]; 
 //   multiply_4x4_matrices(projection_mat, modelview_mat, mat);
 //   multiply_4x4_matrix_by_4_vector(mat, point, out);




    return  vertex_3(
        round(((1.0f + out1[0]) * 0.5f) * (float)width),
        round(((1.0f - out1[1]) * 0.5f) * (float)height), 
        0.0f);
}

float lin_interp(float v0, float v1, float t)
{
    return (1 - t) * v0 + t * v1;
}

vertex_3 lin_interp(vertex_3 v0, vertex_3 v1, float t)
{
    float x = lin_interp(v0.x, v1.x, t);
    float y = lin_interp(v0.y, v1.y, t);
    float z = lin_interp(v0.z, v1.z, t);

    return vertex_3(x, y, z);
}