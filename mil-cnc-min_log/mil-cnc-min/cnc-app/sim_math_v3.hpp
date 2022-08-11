#include "sim_math_v3.h"

inline v3 operator-(const v3& lhs)
{
	return { -lhs.x, -lhs.y, -lhs.z };
}

inline v3 operator+(const v3& lhs)
{
	return lhs;
}

inline v3 operator*(const v3& lhs, const r64& rhs)
{
	return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
}

inline v3 operator*(const r64& lhs, const v3& rhs)
{
	return rhs * lhs;
}

inline v3 operator/(const v3& lhs, const r64& rhs)
{
	return { lhs.x / rhs, lhs.y / rhs, lhs.z / rhs };
}

inline v3 operator+(const v3& lhs, const v3& rhs)
{
	return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

inline v3 operator-(const v3& lhs, const v3& rhs)
{
	return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}

inline v3 operator+=(v3& lhs, const v3& rhs)
{
	lhs = lhs + rhs;

	return lhs;
}

inline v3 operator-=(v3& lhs, const v3& rhs)
{
	lhs = lhs - rhs;

	return lhs;
}

inline v3 operator*=(v3& lhs, const r64& rhs)
{
	lhs = lhs * rhs;

	return lhs;
}

inline v3 operator/=(v3& lhs, const r64& rhs)
{
	lhs = lhs / rhs;

	return lhs;
}

inline r64 dot(const v3& lhs, const v3& rhs)
{
	return (lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z);
}

inline r64 length_squared(const v3& lhs)
{
	//return dot(lhs, lhs);
	//return (lhs.x * lhs.x + lhs.y * lhs.y + lhs.z * lhs.z);
	return SIM_SQUARE(lhs.x) + SIM_SQUARE(lhs.y) + SIM_SQUARE(lhs.z);
}

inline r64 length(const v3& vector)
{
	return SIM_SQRT(length_squared(vector));
}

inline v3 normalize(const v3& vector)
{
	return vector / length(vector);
}

inline v3 cross(const v3& lhs, const v3& rhs)
{
	return
	{
		lhs[1] * rhs[2] - lhs[2] * rhs[1],
		lhs[2] * rhs[0] - lhs[0] * rhs[2],
		lhs[0] * rhs[1] - lhs[1] * rhs[0]
	};
}

inline void apply_inplace(v3& vector, r64(*op)(r64))
{
	vector.x = op(vector.x);
	vector.y = op(vector.y);
	vector.z = op(vector.z);
}