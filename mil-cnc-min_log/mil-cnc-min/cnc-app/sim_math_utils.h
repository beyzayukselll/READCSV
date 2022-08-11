#if !defined(SIM_MATH_UTILS_H)

#include "sim_math_constants.h"

// NOTE(batuhan): 0 is considered positive
#define SIM_SIGN(x)					(((x) >= 0) ? 1 : -1)
#define SIM_SQUARE(a)				((a) * (a))
#define SIM_CUBE(a)					(SIM_SQUARE((a)) * (a))
#define SIM_FOURTH_POWER(a)			(SIM_CUBE((a)) * (a))
#define SIM_FIFTH_POWER(a)			(SIM_FOURTH_POWER((a)) * (a))
#define SIM_DEG_2_RAD(x)			((x) * SIM_DEG_2_RAD_FAC)
#define SIM_RAD_2_DEG(x)			((x) * SIM_RAD_2_DEG_FAC)

inline static
r64 sim_normalize_degree(r64 degree)
{
	r64 result = degree;

	while (result <= 0.0)	result += 360.0;
	while (result > 360.0)	result -= 360.0;

	return degree;
}

inline static 
r64 sim_normalize_radian(r64 radian)
{
	r64 result = radian;

	while (result <= 0.0)		result += SIM_TWO_PI;
	while (result > SIM_TWO_PI)	result -= SIM_TWO_PI;

	return radian;
}

#define SIM_MATH_UTILS_H
#endif
