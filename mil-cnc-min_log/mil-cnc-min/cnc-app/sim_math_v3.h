#if !defined(SIM_MATH_V3_H)

#include "sim_common.h"

struct v3
{
	union
	{
		struct
		{
			r64 x, y, z;
		};
		r64 e[3];
	};

	r64& operator[](int i)
	{
		return e[i];
	}

	const r64& operator[](int i) const
	{
		return e[i];
	}

	void apply_op(r64(*op)(r64))
	{
		x = (op)(x);
		y = (op)(y);
		z = (op)(z);
	}
};

#define SIM_MATH_V3_H
#endif
