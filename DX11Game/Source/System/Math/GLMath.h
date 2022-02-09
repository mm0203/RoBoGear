#ifndef __GL_MATH_H__
#define __GL_MATH_H__

#include <math.h>

void Vec3Add(float* out, float* v1, float* v2);
void Vec3Subtract(float* out, float* v1, float* v2);
void Vec3Scale(float* out, float* v, float scale);
void Vec3Cross(float* out, float* v1, float* v2);
void Vec3Normalize(float* out, float* v);
void Vec3TransformCoord(float* out, float* v, float* m);
float Vec3Length(float* v);

void MatrixMultiply(float* out, float* m1, float* m2);
void MatrixRotationY(float* out, float rad);
void MatrixRotationAxis(float* out, float rad, float* v);


#endif