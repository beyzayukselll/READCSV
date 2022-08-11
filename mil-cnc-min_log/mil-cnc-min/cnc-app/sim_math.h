#if !defined(SIM_MATH_H)

#if defined(TC_VER) 

#include "TcMath.h"		// twincat

#define SIM_FABS		fabs_
#define	SIM_SQRT		sqrt_
#define SIM_ROUND		round_
#define SIM_ACOS		acos_
#define SIM_ATAN2		atan2_
#define SIM_COS			cos_
#define SIM_SIN			sin_

#else

#include <math.h>

#define SIM_FABS		fabs
#define	SIM_SQRT		sqrt
#define SIM_ROUND		round
#define SIM_ACOS		acos
#define SIM_ATAN2		atan2
#define SIM_COS			cos
#define SIM_SIN			sin

#endif

#include "sim_math_constants.h"
#include "sim_math_utils.h"
#include "sim_math_data_types.h"
#include "sim_math_impl.hpp"

#define SIM_MATH_H
#endif
