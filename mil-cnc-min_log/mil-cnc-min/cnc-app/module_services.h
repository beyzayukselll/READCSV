#if !defined(MODULE_SERVICES_H)

#include "sim_common.h"
#include "sim_config.h"
#include "sim_instruction.h"

#include <atomic>

#pragma pack(push, 1)
struct Module_1_Inputs
{
	// * from module 2
	std::atomic<bool>				feed_buffer_empty_internal;

	// * from module 3
	std::atomic<CNC_State> 			state;
	std::atomic<i16>				servo_x_power;
	std::atomic<i16>				servo_y_power;
	std::atomic<i16>				servo_z_power;
	std::atomic<Spindle_Direction>	spindle_direction;
	std::atomic<i16>				spindle_speed;
	std::atomic<i16>				spindle_speed_factor;
	std::atomic<Jog_Factor>			jog_factor_x;
	std::atomic<Jog_Factor>			jog_factor_y;
	std::atomic<Jog_Factor>			jog_factor_z;
	std::atomic<bool>				go_zero;
	std::atomic<bool>				reset_axis;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Module_1_Outputs
{
	std::atomic<CNC_State>			state;
	std::atomic<Jog_Factor>			jog_factor_x;
	std::atomic<Jog_Factor>			jog_factor_y;
	std::atomic<Jog_Factor>			jog_factor_z;
	std::atomic<i16>				spindle_speed;
	std::atomic<Spindle_Direction>	spindle_direction;
	std::atomic<i16>				servo_x_power;
	std::atomic<i16>				servo_y_power;
	std::atomic<i16>				servo_z_power;
	std::atomic<i16>				spindle_speed_factor;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Module_2_Inputs
{
	// * from module 1
	std::atomic<CNC_State>			state;
	std::atomic<Jog_Factor>			jog_factor_x;
	std::atomic<Jog_Factor>			jog_factor_y;
	std::atomic<Jog_Factor>			jog_factor_z;
	std::atomic<i16>				spindle_speed;
	std::atomic<Spindle_Direction>	spindle_direction;

	// * from module 3
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Module_2_Outputs
{
	std::atomic<bool>				feed_buffer_empty_internal;
	std::atomic<r64>				axis_x_pos;
	std::atomic<r64>				axis_y_pos;
	std::atomic<r64>				axis_z_pos;
	std::atomic<r64>				axis_x_vel;
	std::atomic<r64>				axis_y_vel;
	std::atomic<r64>				axis_z_vel;
	std::atomic<i32>				axis_x_pos_act;
	std::atomic<i32>				axis_y_pos_act;
	std::atomic<i32>				axis_z_pos_act;
	std::atomic<i32>				axis_x_vel_act;
	std::atomic<i32>				axis_y_vel_act;
	std::atomic<i32>				axis_z_vel_act;
	std::atomic<i16>				servo_x_power;
	std::atomic<i16>				servo_y_power;
	std::atomic<i16>				servo_z_power;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Module_3_Inputs
{
	// * from module 2
	std::atomic<r64>				axis_x_pos;
	std::atomic<r64>				axis_y_pos;
	std::atomic<r64>				axis_z_pos;
	std::atomic<r64>				axis_x_vel;
	std::atomic<r64>				axis_y_vel;
	std::atomic<r64>				axis_z_vel;
	std::atomic<i32>				axis_x_pos_act;
	std::atomic<i32>				axis_y_pos_act;
	std::atomic<i32>				axis_z_pos_act;
	std::atomic<i32>				axis_x_vel_act;
	std::atomic<i32>				axis_y_vel_act;
	std::atomic<i32>				axis_z_vel_act;
	std::atomic<i16>				servo_x_power;
	std::atomic<i16>				servo_y_power;
	std::atomic<i16>				servo_z_power;

	// * from module 1
	std::atomic<CNC_State>			state;
	std::atomic<Jog_Factor>			jog_factor_x;
	std::atomic<Jog_Factor>			jog_factor_y;
	std::atomic<Jog_Factor>			jog_factor_z;
	std::atomic<Spindle_Direction> 	spindle_direction;
	std::atomic<i16>				spindle_speed;
	std::atomic<i16>				spindle_speed_factor;
};
#pragma pack(pop)


#pragma pack(push, 1)
struct Module_3_Outputs
{
	std::atomic<CNC_State> 			state;
	std::atomic<i16>				servo_x_power;
	std::atomic<i16>				servo_y_power;
	std::atomic<i16>				servo_z_power;
	std::atomic<Spindle_Direction>	spindle_direction;
	std::atomic<i16>				spindle_speed;
	std::atomic<i16>				spindle_speed_factor;
	std::atomic<Jog_Factor>			jog_factor_x;
	std::atomic<Jog_Factor>			jog_factor_y;
	std::atomic<Jog_Factor>			jog_factor_z;

	// ! find a way to handle this shits
	std::atomic<bool>				reset_axis;
	std::atomic<bool>				go_zero;
};
#pragma pack(pop)

#define MODULE_SERVICES_H
#endif