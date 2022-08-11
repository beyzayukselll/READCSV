#include "sim_math_mat3.h"

mat3 operator*(const v3& lhs, const v3& rhs)
{
	mat3 result = {};

	result[0][0] = lhs[0] * rhs[0];
	result[0][1] = lhs[0] * rhs[1];
	result[0][2] = lhs[0] * rhs[2];
	result[1][0] = lhs[1] * rhs[0];
	result[1][1] = lhs[1] * rhs[1];
	result[1][2] = lhs[1] * rhs[2];
	result[2][0] = lhs[2] * rhs[0];
	result[2][1] = lhs[2] * rhs[1];
	result[2][2] = lhs[2] * rhs[2];

	return result;
}

mat3 operator*(const mat3& lhs, const mat3& rhs)
{
	mat3 result = {};

	result[0][0] = lhs[0][0] * rhs[0][0] + lhs[1][0] * rhs[0][1] + lhs[2][0] * rhs[0][2];
	result[0][1] = lhs[0][1] * rhs[0][0] + lhs[1][1] * rhs[0][1] + lhs[2][1] * rhs[0][2];
	result[0][2] = lhs[0][2] * rhs[0][0] + lhs[1][2] * rhs[0][1] + lhs[2][2] * rhs[0][2];

	result[1][0] = lhs[0][0] * rhs[1][0] + lhs[1][0] * rhs[1][1] + lhs[2][0] * rhs[1][2];
	result[1][1] = lhs[0][1] * rhs[1][0] + lhs[1][1] * rhs[1][1] + lhs[2][1] * rhs[1][2];
	result[1][2] = lhs[0][2] * rhs[1][0] + lhs[1][2] * rhs[1][1] + lhs[2][2] * rhs[1][2];

	result[2][0] = lhs[0][0] * rhs[2][0] + lhs[1][0] * rhs[2][1] + lhs[2][0] * rhs[2][2];
	result[2][1] = lhs[0][1] * rhs[2][0] + lhs[1][1] * rhs[2][1] + lhs[2][1] * rhs[2][2];
	result[2][2] = lhs[0][2] * rhs[2][0] + lhs[1][2] * rhs[2][1] + lhs[2][2] * rhs[2][2];

	return result;
}

v3 operator*(const mat3& lhs, const v3& rhs)
{
	v3 result = {};

	result[0] = rhs[0] * lhs[0][0] + rhs[1] * lhs[0][1] + rhs[2] * lhs[0][2];
	result[1] = rhs[0] * lhs[1][0] + rhs[1] * lhs[1][1] + rhs[2] * lhs[1][2];
	result[2] = rhs[0] * lhs[2][0] + rhs[1] * lhs[2][1] + rhs[2] * lhs[2][2];

	return result;
}

r64 determinant(const mat3& m)
{
	return
		+m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
		- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
		+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
}

mat3 inverse(const mat3& m)
{
	r64 one_over_det = (r64)(1.0) / (
		+m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
		- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
		+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]));

	mat3 result = {};
	result[0][0] = +(m[1][1] * m[2][2] - m[2][1] * m[1][2]) * one_over_det;
	result[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * one_over_det;
	result[2][0] = +(m[1][0] * m[2][1] - m[2][0] * m[1][1]) * one_over_det;
	result[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * one_over_det;
	result[1][1] = +(m[0][0] * m[2][2] - m[2][0] * m[0][2]) * one_over_det;
	result[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * one_over_det;
	result[0][2] = +(m[0][1] * m[1][2] - m[1][1] * m[0][2]) * one_over_det;
	result[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * one_over_det;
	result[2][2] = +(m[0][0] * m[1][1] - m[1][0] * m[0][1]) * one_over_det;

	return result;
}

mat3 transpose(const mat3& m)
{
	mat3 result = {};

	result[0][0] = m[0][0];
	result[0][1] = m[1][0];
	result[0][2] = m[2][0];
	result[1][0] = m[0][1];
	result[1][1] = m[1][1];
	result[1][2] = m[2][1];
	result[2][0] = m[0][2];
	result[2][1] = m[1][2];
	result[2][2] = m[2][2];

	return result;
}

mat3 pseudo_inverse(const mat3& m)
{
	mat3 m_T = transpose(m);

	mat3 result = {};

	result = m_T * inverse(m * m_T);

	return result;
}

void apply_inplace(mat3& m, r64(*op)(r64))
{
	apply_inplace(m.c1, op);
	apply_inplace(m.c2, op);
	apply_inplace(m.c3, op);
}

mat3 operator/(const mat3& lhs, const mat3& rhs)
{
	return lhs * pseudo_inverse(rhs);
}
