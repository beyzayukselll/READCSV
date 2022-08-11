#if !defined(SIM_MATH_MAT3_H)

#include "sim_common.h"
#include "sim_math_v3.h"

// columnwise-mat3x3 matrix
struct mat3
{
	union
	{
		struct
		{
			v3 c1, c2, c3;
		};
		v3 c[3];
	};

	v3& operator[](int i)
	{
		return c[i];
	}

	const v3& operator[](int i) const
	{
		return c[i];
	}

	void apply_op(r64(*op)(r64))
	{
		c1.apply_op(op);
		c2.apply_op(op);
		c3.apply_op(op);
	}
};

#define SIM_MATH_MAT3_H
#endif
