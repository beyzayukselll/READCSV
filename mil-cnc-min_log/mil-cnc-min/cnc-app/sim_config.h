#if !defined(SIM_CONFIG_H)

#include "sim_common.h"

/*
typedef struct
{
	r64 feed_rate_limit = 100.0;
	r64 acceleration_limit = 2000.0;
	r64 deceleration_limit = 2000.0;
	r64 jerk_limit = 100000.0;
	
	struct
	{
		r64 cornering_tolerance = 5.0;
		r64 cornering_tolerance_factor_increment = 0.2;
		r64 travel_time_limit = 1.0;
	} splining_configuration;

} machine_configuration;
*/

#define TODO_CFG_ENCODER_RESOLUTION 		(8192)	// 13 bit resolution
#define TODO_CFG_FEED_CONSTANT 				(5e3) 	// 5000 micrometers
#define TODO_CFG_GEAR_RATIO 				(1)		// 1:1 gear ratio
#define TODO_CFG_PROFILE_VELOCITY 			(1e3)
#define TODO_CFG_POSITION_FACTOR_NUM 		(TODO_CFG_ENCODER_RESOLUTION * TODO_CFG_GEAR_RATIO)
#define TODO_CFG_POSITION_FACTOR_DEN 		(TODO_CFG_FEED_CONSTANT)
#define TODO_CFG_INTERP_TIME_PERIOD 		(1)		// 2
#define TODO_CFG_INTERP_TIME_PERIOD_INDEX 	(-3)	// ms

#define INTERFACE_NAME "enp3s0"

#define FAKE_SERVO 		true

#define SERVO_COUNT  	3

#define SIM_CONFIG_H
#endif