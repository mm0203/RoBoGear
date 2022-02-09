#include "GLMath.h"
#include <memory.h>
#include <stdio.h>

void Vec3Add(float* out, float* v1, float* v2)
{
	out[0] = v1[0] + v2[0];
	out[1] = v1[1] + v2[1];
	out[2] = v1[2] + v2[2];
}
void Vec3Subtract(float* out, float* v1, float* v2)
{
	out[0] = v1[0] - v2[0];
	out[1] = v1[1] - v2[1];
	out[2] = v1[2] - v2[2];
}
void Vec3Scale(float* out, float* v, float scale)
{
	out[0] = v[0] * scale;
	out[1] = v[1] * scale;
	out[2] = v[2] * scale;
}
void Vec3Cross(float* out, float* v1, float* v2)
{
	out[0] = v1[1] * v2[2] - v1[2] * v2[1];
	out[1] = v1[2] * v2[0] - v1[0] * v2[2];
	out[2] = v1[0] * v2[1] - v1[1] * v2[0];
}
void Vec3Normalize(float* out, float* v)
{
	float len = sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	out[0] = v[0] / len;
	out[1] = v[1] / len;
	out[2] = v[2] / len;
}
void Vec3TransformCoord(float* out, float* v, float* m)
{
	if (out == v) { printf("[error]GLMath::Vec3TransformCoord -> out == v\n"); return; }
	out[0] = v[0] * m[0] + v[1] * m[4] + v[2] * m[ 8] + m[12];
	out[1] = v[0] * m[1] + v[1] * m[5] + v[2] * m[ 9] + m[13];
	out[2] = v[0] * m[2] + v[1] * m[6] + v[2] * m[10] + m[14];
}
float Vec3Length(float* v)
{
	return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

void MatrixMultiply(float* out, float* m1, float* m2)
{
	if (out == m1) { printf("[error]GLMath::MatrixMultiply -> out == m1\n"); return; }
	if (out == m2) { printf("[error]GLMath::MatrixMultiply -> out == m2\n"); return; }

	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			int idx = j * 4 + i;
			out[idx] = 0.0f;
			for (int k = 0; k < 4; ++k)
			{
				out[idx] += m1[j * 4 + k] * m2[k * 4 + i];
			}
		}
	}
}
void MatrixRotationY(float* out, float rad)
{
	float c = cosf(rad);
	float s = sinf(rad);
	float m[] = {
		  c, 0.f,   s, 0.f,
		0.f, 1.f, 0.f, 0.f,
		 -s, 0.f,   c, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
	memcpy(out, m, sizeof(m));
}
void MatrixRotationAxis(float* out, float rad, float* v)
{
	float s = sinf(rad);
	float c = cosf(rad);
	float mc = 1.0f - c;
	float xx = v[0] * v[0];
	float yy = v[1] * v[1];
	float zz = v[2] * v[2];
	float xy = v[0] * v[1];
	float xz = v[0] * v[2];
	float yz = v[1] * v[2];
	float sx = v[0] * s;
	float sy = v[1] * s;
	float sz = v[2] * s;

	float m[] = {
		xx * mc + c,	xy * mc - sz,	xz * mc + sy,	0.0f,
		xy * mc + sz,	yy * mc + c,	yz * mc - sx,	0.0f,
		xz * mc - sy,	yz * mc + sx,	zz * mc + c,	0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
	memcpy(out, m, sizeof(m));
}
