#if !defined(SIM_INSTRUCTION_H)

#include "sim_functions.h"

enum Spindle_Direction
{
	CW = -1,
	STOP = 0,
	CCW = 1
};

enum Instruction_Type
{
	INSTRUCTION_LINESEGMENT,
	INSTRUCTION_ARCSEGMENT,
	INSTRUCTION_DWELL,
	INSTRUCTION_SPINDLE,
	INSTRUCTION_COOLANT
};

enum Jog_Factor
{
	JOG_BACKWARD = -2,
	JOG_BACKWARD_HALF = -1,
	JOG_STOP = 0,
	JOG_FORWARD_HALF = 1,
	JOG_FORWARD = 2
};

enum CNC_State : unsigned int
{
	CNC_STATE_IDLE = 0,
	CNC_STATE_JOG = 1,
	CNC_STATE_CUT = 2
};

struct Spindle_Input
{
	u16						speed;
	Spindle_Direction		direction;
};

struct Instruction
{
	Instruction_Type		type;
	Interpolation_Input		input;
	Spindle_Input			spindle_input;
};

struct Job
{
	Instruction_Type		type;
	v3						tool_path;
	v3						velocity;
	v3						acceleration;
	v3						jerk;
	u16						speed;
	Spindle_Direction		spindle_direction;
};

#define SIM_INSTRUCTION_H
#endif