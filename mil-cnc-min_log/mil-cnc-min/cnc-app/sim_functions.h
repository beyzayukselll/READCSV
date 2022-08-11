#if !defined(SIM_FUNCTIONS_H)

#include "sim_math_data_types.h"
#include <deque>
#include <vector>

enum Ref_Plane_Type
{
	PLANE_XY = 0,
	PLANE_YZ = 1,
	PLANE_XZ = 2
};

enum  Arc_Segment_Direction
{
	// NOTE(batuhan): used as coefficient in circular_interpolation so don't change.
	DIRECTION_CW = -1,
	DIRECTION_CCW = 1
};

struct Interpolation_Input
{
	v3						start_point;
	v3						end_point;
	v3						center_point;
	r64						feedrate;
	r64						start_length;
	r64						acceleration;
	r64						deceleration;
	r64						initial_feedrate;
	r64						final_feedrate;
	r64						helix;
	u64						number_of_turns;
	Ref_Plane_Type			plane;
	Arc_Segment_Direction	direction;
};

struct Interpolation_Output
{
	std::deque<v3>			tool_path;
	std::deque<v3>			jerks; // haha
	std::deque<v3>			velocities;
	std::deque<v3>			accelerations;
};

struct Trapezoidal_Acceleration_Output
{
	std::vector<r64>		displacement_variation;
	std::vector<r64>		velocity_variation;
	std::vector<r64>		acceleration_variation;
	std::vector<r64>		jerk_variation;
	std::vector<r64>		delta;
};

struct Circle_Intersection_Output
{
	bool					valid;
	r64						x3[2];
	r64						y3[2];
};

u64 SIM_linear_interpolation(const Interpolation_Input& input, Interpolation_Output* result);
u64 SIM_circular_interpolation(const Interpolation_Input& input, Interpolation_Output* result);
u64 SIM_trajectory_with_spline(const Interpolation_Input& input, const Interpolation_Input& next_input, Interpolation_Output* result, const r64 cornering_tolerance);

//v3 SIM_find_spline_endpoint_linesegment(const interpolation_input& input, bool end, const r64 cornering_tolerance);
//v3 SIM_find_spline_endpoint_arcsegment(const interpolation_input& input, bool ELEVEN, const r64 cornering_tolerance);
//void SIM_convert_2D_to_3D(const v3& start_point, const v3& end_point, const v3& corner_point, r64* sp_x, r64* sp_y, r64* ep_x, r64* ep_y, r64* angle_before, r64* angle_after, mat3 *R);
//circle_intersection_output SIM_circcirc(r64 x0, r64 y0, r64 r0, r64 x1, r64 y1, r64 r1);

#define SIM_FUNCTIONS_H
#endif
