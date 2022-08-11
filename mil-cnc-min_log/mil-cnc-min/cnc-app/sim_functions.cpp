#include "sim_functions.h"
#include "sim_math.h"
#include "sim_utils.h"
#include <vector>
#include <algorithm>

static
void SIM_trapezoidal_acceleration(const Interpolation_Input& input, const r64 travel_distance_of_tool, Trapezoidal_Acceleration_Output* result)
{
	#define JERK				100000 // mm/s^3
	#define TIMESTEP			0.001
	#define ONE_OVER_TIMESTEP	1000
	#define ONE_OVER_SIX		0.166666667

	auto jerk = SIM_MIN(input.acceleration * ONE_OVER_TIMESTEP, input.deceleration * ONE_OVER_TIMESTEP);
	jerk = SIM_MIN(jerk, JERK);
	auto jerk_abs = SIM_FABS(jerk);

	//#pragma region ACCELERATION
	auto initial_feedrate_diff = (input.feedrate - input.initial_feedrate);
	auto sign_of_acc = SIM_SIGN(initial_feedrate_diff);
	auto acceleration = sign_of_acc * SIM_FABS(input.acceleration);
	auto acceleration_sign = SIM_SIGN(acceleration);
	auto J1 = acceleration_sign * jerk_abs;
	auto J3 = J1;
	auto one_over_J1 = 1.0 / J1;
	auto one_over_J3 = 1.0 / J3;
	auto T1 = 0.0;
	auto T2 = 0.0;
	auto T3 = 0.0;
	auto N1 = 0.0;
	auto N2 = 0.0;
	auto N3 = 0.0;
	auto acceleration_result = 0.0;
	auto acceleration_result_sign = 1;
	// TODO(batuhan): This is not going to work -- double comparison
	if (input.feedrate != input.initial_feedrate)
	{
		T1 = acceleration * one_over_J1;
		T3 = acceleration * one_over_J3;
		T2 = ((initial_feedrate_diff) / acceleration) - (T1);

		if (T2 < 0.0)
		{
			T2 = 0.0;
			acceleration = acceleration_sign * SIM_SQRT(J1 * initial_feedrate_diff);
			T1 = acceleration * one_over_J1;
			T3 = acceleration * one_over_J3;
		}
		acceleration_result = acceleration;
		acceleration_result_sign = SIM_SIGN(acceleration_result);

		N1 = SIM_ROUND(SIM_FABS(T1) * ONE_OVER_TIMESTEP);
		N3 = SIM_ROUND(SIM_FABS(T3) * ONE_OVER_TIMESTEP);
		N2 = SIM_ROUND(T2 * ONE_OVER_TIMESTEP);
	}
	//#pragma endregion

	//#pragma region DECELERATION
	auto final_feedrate_diff = (input.feedrate - input.final_feedrate);
	auto sign_of_dec = SIM_SIGN(final_feedrate_diff);
	auto deceleration = sign_of_dec * SIM_FABS(input.deceleration);
	auto deceleration_sign = SIM_SIGN(deceleration);
	auto J5 = deceleration_sign * jerk_abs;
	auto J7 = J5;
	auto one_over_J5 = 1.0 / J5;
	auto one_over_J7 = 1.0 / J7;
	auto N5 = 0.0;
	auto N6 = 0.0;
	auto N7 = 0.0;
	auto T5 = 0.0;
	auto T6 = 0.0;
	auto T7 = 0.0;
	auto deceleration_result = 0.0;
	auto deceleration_result_sign = 1;
	// TODO(batuhan): This is not going to work -- double comparison
	if (input.feedrate != input.final_feedrate)
	{
		T5 = deceleration * one_over_J5;
		T7 = deceleration * one_over_J7;
		T6 = (final_feedrate_diff / deceleration) - (T5);

		if (T6 < 0)
		{
			T6 = 0.0;
			deceleration = deceleration_sign * SIM_SQRT(J5 * (final_feedrate_diff));
			T5 = deceleration * one_over_J5;
			T7 = deceleration * one_over_J7;
		}
		deceleration_result = deceleration;
		deceleration_result_sign = SIM_SIGN(deceleration_result);

		N5 = SIM_ROUND(SIM_FABS(T5) * ONE_OVER_TIMESTEP);
		N6 = SIM_ROUND(T6 * ONE_OVER_TIMESTEP);
		N7 = SIM_ROUND(SIM_FABS(T7) * ONE_OVER_TIMESTEP);
	}
	//#pragma endregion

	auto a1 = 0.0;
	auto a2 = 0.0;
	auto a3 = 0.0;

	if (N1 != 0)
	{
		auto two_J1 = 2 * J1;
		a1 = SIM_ONE_HALF / acceleration_result;
		a2 = acceleration_result / two_J1;
		a3 = (acceleration_result * input.initial_feedrate / (two_J1)) - (SIM_SQUARE(input.initial_feedrate) / (2 * acceleration_result));
	}

	if (N5 != 0)
	{
		auto two_J5 = 2 * J5;
		a1 += SIM_ONE_HALF / deceleration_result;
		a2 += deceleration_result / two_J5;
		a3 += (deceleration_result * input.final_feedrate / (two_J5)) - (SIM_SQUARE(input.final_feedrate) / (2 * deceleration_result));
	}

	auto feedrate = input.feedrate;
	auto T4 = (1.0 / input.feedrate) * (travel_distance_of_tool - (a1 * SIM_SQUARE(input.feedrate) + a2 * input.feedrate + a3));
	auto N4 = 0;
	if (T4 <= 0)
	{
		T4 = 0;
		feedrate = (-a2 + SIM_SQRT(SIM_SQUARE(a2) - (4.0 * a1 * (a3 - travel_distance_of_tool)))) / (2.0 * a1);
		initial_feedrate_diff = feedrate - input.initial_feedrate;

		T2 = (initial_feedrate_diff / acceleration_result) - (acceleration_result * one_over_J1);
		if (T2 < 0)
		{
			T2 = 0;
			acceleration_result = acceleration_result_sign * SIM_SQRT(J1 * initial_feedrate_diff);
			T1 = acceleration_result * one_over_J1;
			T3 = T1;
		}
		N1 = SIM_ROUND(SIM_FABS(T1) * ONE_OVER_TIMESTEP);
		N3 = N1;
		N2 = SIM_ROUND(T2 * ONE_OVER_TIMESTEP);

		final_feedrate_diff = feedrate - input.final_feedrate;
		T6 = (final_feedrate_diff / deceleration_result) - (deceleration_result * one_over_J5);
		if (T6 < 0)
		{
			T6 = 0;
			deceleration_result = deceleration_result_sign * SIM_SQRT(J5 * final_feedrate_diff);
			T5 = deceleration_result * one_over_J5;
			T7 = T5;
		}
		N5 = SIM_ROUND(SIM_FABS(T5) * ONE_OVER_TIMESTEP);
		N7 = N5;
		N6 = SIM_ROUND(T6 * ONE_OVER_TIMESTEP);
	}
	N4 = (int)(SIM_ROUND(T4 * ONE_OVER_TIMESTEP));

	auto f1s = input.initial_feedrate;
	auto l1s = input.start_length;
	for (i64 k = 1; k <= N1; ++k)
	{
		const auto k_times_timestep = k * TIMESTEP;
		l1s = input.start_length + input.initial_feedrate * k_times_timestep + (J1 * SIM_CUBE(k_times_timestep)) * ONE_OVER_SIX;
		result->displacement_variation.push_back(l1s);

		f1s = input.initial_feedrate + (J1 * SIM_SQUARE(k_times_timestep)) * SIM_ONE_HALF;
		result->velocity_variation.push_back(f1s);

		result->acceleration_variation.push_back(J1 * k_times_timestep);
		result->jerk_variation.push_back(J1);
	}

	auto f2s = f1s;
	auto l2s = l1s;
	for (i64 k = 1; k <= N2; ++k)
	{
		const auto k_times_timestep = k * TIMESTEP;
		l2s = l1s + f1s * k_times_timestep + acceleration_result * SIM_SQUARE(k_times_timestep) * SIM_ONE_HALF;
		result->displacement_variation.push_back(l2s);

		f2s = f1s + acceleration_result * k_times_timestep;
		result->velocity_variation.push_back(f2s);

		result->acceleration_variation.push_back(acceleration_result);
		result->jerk_variation.push_back(0);
	}

	auto f3s = f2s;
	auto l3s = l2s;
	for (i64 k = 1; k <= N3; ++k)
	{
		const auto k_times_timestep = k * TIMESTEP;
		l3s = l2s + f2s * k_times_timestep + acceleration_result * SIM_SQUARE(k_times_timestep) * SIM_ONE_HALF - (J3 * SIM_CUBE(k_times_timestep)) * ONE_OVER_SIX;
		result->displacement_variation.push_back(l3s);

		f3s = f2s + acceleration_result * k_times_timestep - (J3 * SIM_SQUARE(k_times_timestep)) * SIM_ONE_HALF;
		result->velocity_variation.push_back(f3s);

		result->acceleration_variation.push_back(acceleration_result - J3 * k_times_timestep);
		result->jerk_variation.push_back(-J3);
	}

	auto f4s = f3s;
	auto l4s = l3s;
	for (i64 k = 1; k <= N4; ++k)
	{
		const auto k_times_timestep = k * TIMESTEP;
		l4s = l3s + f3s * k_times_timestep;
		result->displacement_variation.push_back(l4s);

		f4s = f3s;
		result->velocity_variation.push_back(f4s);

		result->acceleration_variation.push_back(0);
		result->jerk_variation.push_back(0);
	}

	auto f5s = f4s;
	auto l5s = l4s;
	for (i64 k = 1; k <= N5; ++k)
	{
		const auto k_times_timestep = k * TIMESTEP;
		l5s = l4s + f4s * k_times_timestep - (J5 * SIM_CUBE(k_times_timestep)) * ONE_OVER_SIX;
		result->displacement_variation.push_back(l5s);

		f5s = f4s - (J5 * SIM_SQUARE(k_times_timestep) * SIM_ONE_HALF);
		result->velocity_variation.push_back(f5s);

		result->acceleration_variation.push_back(-J5 * k_times_timestep);
		result->jerk_variation.push_back(-J5);
	}

	auto f6s = f5s;
	auto l6s = l5s;
	for (i64 k = 1; k <= N6; ++k)
	{
		const auto k_times_timestep = k * TIMESTEP;
		l6s = l5s + f5s * k_times_timestep - deceleration_result * SIM_SQUARE(k_times_timestep) * SIM_ONE_HALF;
		result->displacement_variation.push_back(l6s);

		f6s = f5s - deceleration_result * k_times_timestep;
		result->velocity_variation.push_back(f6s);

		result->acceleration_variation.push_back(-deceleration_result);
		result->jerk_variation.push_back(0);
	}

	auto f7s = f6s;
	auto l7s = l6s;
	for (i64 k = 1; k <= N7; ++k)
	{
		const auto k_times_timestep = k * TIMESTEP;
		l7s = l6s + f6s * k_times_timestep - (deceleration_result * (SIM_SQUARE(k_times_timestep)) * SIM_ONE_HALF) + (J7 * SIM_CUBE(k_times_timestep) * ONE_OVER_SIX);
		result->displacement_variation.push_back(l7s);

		f7s = f6s - deceleration * k_times_timestep + (J7 * SIM_SQUARE(k_times_timestep)) * SIM_ONE_HALF;
		result->velocity_variation.push_back(f7s);

		result->acceleration_variation.push_back(-deceleration_result + J7 * k_times_timestep);
		result->jerk_variation.push_back(J7);
	}

	auto kkkk = 1.0;
	if (result->displacement_variation.back() != travel_distance_of_tool)
	{
		kkkk = (result->displacement_variation.back() - input.start_length) / travel_distance_of_tool;
	}

	for (auto& it : result->displacement_variation)
	{
		r64 delta = it - input.start_length;
		it = (delta) / kkkk + input.start_length;
		result->delta.push_back(delta);
	}
}

u64 SIM_linear_interpolation(const Interpolation_Input& input, Interpolation_Output* result)
{
	const auto& sp = input.start_point;
	const auto& ep = input.end_point;

	r64 travel_distance_of_tool = length(ep - sp);
	v3 delta = ep - sp;
	
	Trapezoidal_Acceleration_Output mid_res = {};
	SIM_trapezoidal_acceleration(input, travel_distance_of_tool, &mid_res);

	for (int i = 0; i < mid_res.displacement_variation.size(); ++i)
	{
		result->tool_path.emplace_back(sp + delta * (mid_res.displacement_variation[i] - input.start_length) / travel_distance_of_tool);
		result->jerks.emplace_back(delta * (mid_res.jerk_variation[i] / travel_distance_of_tool));
		result->velocities.emplace_back(delta * (mid_res.velocity_variation[i] / travel_distance_of_tool));
		result->accelerations.emplace_back(delta * (mid_res.acceleration_variation[i] / travel_distance_of_tool));
	}

	// return size of interpolation
	return mid_res.displacement_variation.size();
}

u64 SIM_circular_interpolation(const Interpolation_Input& input, Interpolation_Output* result)
{
	v3 sp = input.start_point;
	v3 ep = input.end_point;
	v3 cp = input.center_point;

	switch (input.plane)
	{
		case Ref_Plane_Type::PLANE_YZ:
		{
			sp.x = sp.y;
			sp.y = sp.z;
			sp.z = sp.x;

			ep.x = ep.y;
			ep.y = ep.z;
			ep.z = ep.x;

			cp.x = cp.y;
			cp.y = cp.z;
			cp.z = cp.x;
		}
		break;

		case Ref_Plane_Type::PLANE_XZ:
		{
			sp.x = sp.x;
			sp.y = sp.z;
			sp.z = sp.y;

			ep.x = ep.x;
			ep.y = ep.z;
			ep.z = ep.y;

			cp.x = cp.x;
			cp.y = cp.z;
			cp.z = cp.y;
		}
		break;
	}

	v3 Oprime_sp = sp - cp;
	v3 Oprime_ep = ep - cp;

	r64 R_sp = SIM_SQRT(dot(Oprime_sp, Oprime_sp));
	r64 R_ep = SIM_SQRT(dot(Oprime_ep, Oprime_ep));
	r64 k = R_ep / R_sp;

	v3 UA = Oprime_sp / R_sp;
	Oprime_ep /= k;

	r64 theta = SIM_ACOS(dot(Oprime_ep, Oprime_sp) / (length(Oprime_ep) * length(Oprime_sp)));

	v3 Oprime_cross = cross(Oprime_sp, Oprime_ep);
	v3 normal_vec = Oprime_cross / (length(Oprime_cross));

	if (Oprime_cross.x == 0 &&
		Oprime_cross.y == 0 &&
		Oprime_cross.z == 0)
	{
		Oprime_cross.z = -1;
	}

	v3 UB = -cross(UA, normal_vec);
	mat3 R = { UA, UB, normal_vec };
	mat3 R_transpose = transpose(R);

	v3 Un = R_transpose * normal_vec;
	v3 planar_A = R_transpose * Oprime_sp;
	v3 planar_B = R_transpose * Oprime_ep;

	if (normal_vec.z < 0)
	{
		SIM_SWAP(planar_A, planar_B);
	}

	// in radians
	r64 theta_start = SIM_ATAN2(planar_A[1], planar_A[0]);
	r64 theta_end = SIM_ATAN2(planar_B[1], planar_B[0]);
	//theta_start = SIM_RAD_2_DEG(theta_start);
	//theta_end = SIM_RAD_2_DEG(theta_end);

	if (input.direction == Arc_Segment_Direction::DIRECTION_CW)
	{
		SIM_SWAP(theta_start, theta_end);
	}
	theta_start = sim_normalize_radian(theta_start);
	theta_end = sim_normalize_radian(theta_end);
	if (theta_end < theta_start) theta_end += SIM_TWO_PI;

	r64 xs = R_sp * SIM_COS(theta_start);
	r64 ys = R_sp * SIM_SIN(theta_start);
	r64 xe = R_ep * SIM_COS(theta_start);
	r64 ye = R_ep * SIM_SIN(theta_start);

	r64 travel_distance_of_tool = R_sp * (theta_end - theta_start);

	Trapezoidal_Acceleration_Output mid_res = {};
	SIM_trapezoidal_acceleration(input, travel_distance_of_tool, &mid_res);

	for (auto& it : mid_res.delta)
	{
		it /= R_sp;
	}

	r64 angle = SIM_ATAN2(sp.y - cp.y, sp.x - cp.x);

	u64 old_size = result->tool_path.size();

	for (int i = 0; i < mid_res.displacement_variation.size(); ++i)
	{
		r64 pos_dv = angle + ((mid_res.displacement_variation[i] - input.start_length) * input.direction / R_sp);
		r64 pos_dv_cos = R_sp * SIM_COS(pos_dv);
		r64 pos_dv_sin = R_sp * SIM_SIN(pos_dv);

		r64 vel_dv = mid_res.velocity_variation[i] / R_sp * input.direction;
		r64 acc_dv = mid_res.acceleration_variation[i] / R_sp * input.direction;
		r64 jerk_dv = mid_res.jerk_variation[i] / R_sp * input.direction;

		result->tool_path.push_back({
			pos_dv_cos + cp.x,
			pos_dv_sin + cp.y,
			cp.z });

		result->velocities.push_back({
			-pos_dv_sin * vel_dv,
			+pos_dv_cos * vel_dv,
			0.0 });

		result->accelerations.push_back({
			-result->velocities.back().y * vel_dv - pos_dv_sin * acc_dv,
			+result->velocities.back().x * vel_dv + pos_dv_cos * acc_dv,
			0.0 });

		result->jerks.push_back({
			-result->accelerations.back().y * vel_dv - 2.0 * result->velocities.back().y * acc_dv - pos_dv_sin * jerk_dv,
			+result->accelerations.back().x * vel_dv + 2.0 * result->velocities.back().x * acc_dv + pos_dv_cos * jerk_dv,
			0.0 });
	}

	// NOTE(batuhan): Matlab reverses twice for some conditions, we reverse once
	bool is_reverse = (normal_vec.z < 0 && input.direction == Arc_Segment_Direction::DIRECTION_CCW) ||
		(normal_vec.z >= 0 && input.direction == Arc_Segment_Direction::DIRECTION_CW);
	if (is_reverse)
	{
		std::reverse(result->tool_path.begin() + old_size, result->tool_path.end());
	}

	switch (input.plane)
	{
		case Ref_Plane_Type::PLANE_YZ:
		{
			// wtf..
			for (u64 i = old_size; i < result->tool_path.size(); ++i)
			{
				// three-way swap (final should be z-x-y)
				SIM_SWAP(result->tool_path[i].x, result->tool_path[i].y);
				SIM_SWAP(result->tool_path[i].x, result->tool_path[i].z);

				SIM_SWAP(result->velocities[i].x, result->velocities[i].y);
				SIM_SWAP(result->velocities[i].x, result->velocities[i].z);

				SIM_SWAP(result->accelerations[i].x, result->accelerations[i].y);
				SIM_SWAP(result->accelerations[i].x, result->accelerations[i].z);

				SIM_SWAP(result->jerks[i].x, result->jerks[i].y);
				SIM_SWAP(result->jerks[i].x, result->jerks[i].z);
			}
		}
		break;

		case Ref_Plane_Type::PLANE_XZ:
		{
			for (u64 i = old_size; i < result->tool_path.size(); ++i)
			{
				SIM_SWAP(result->tool_path[i].y, result->tool_path[i].z);
				SIM_SWAP(result->velocities[i].y, result->velocities[i].z);
				SIM_SWAP(result->accelerations[i].y, result->accelerations[i].z);
				SIM_SWAP(result->jerks[i].y, result->jerks[i].z);
			}
		}
		break;
	}

	// return size of interpolation
	return mid_res.displacement_variation.size();
}

u64 SIM_trajectory_with_spline(const Interpolation_Input& input, const Interpolation_Input& next_input, Interpolation_Output* result, const r64 cornering_tolerance)
{
	constexpr r64 spline_travel_time_increment = 0.1;
	constexpr r64 max_spline_travel_time = 1.0;
	r64 current_spline_travel_time = spline_travel_time_increment;

	constexpr r64 cornering_tolerance_factor_increment = 0.2;
	constexpr int ctf_iter_count = (int)(1.0 / cornering_tolerance_factor_increment);
	constexpr auto jmax = 100000;

	// calculate the angles
	r64 angleBeforeCornerPoint = SIM_ATAN2(input.end_point.y - input.start_point.y, input.end_point.x - input.start_point.x);
	r64 angleAfterCornerPoint = SIM_ATAN2(next_input.end_point.y - next_input.start_point.y, next_input.end_point.x - next_input.start_point.x);

	Interpolation_Output mid_res;
	bool spline_fit = false;
	r64 check_two = 0.01;
	std::vector<r64> check_one(11, 1.0);

	// spline
	while ((*std::max_element(check_one.begin(), check_one.end()) > 0.0 || check_two > 0.01)
		&& current_spline_travel_time < max_spline_travel_time
		&& !spline_fit)
	{
		for (int ctf_iter = 1; ctf_iter <= ctf_iter_count; ++ctf_iter)
		{
			// trying to keep spline sharper
			auto ctf = cornering_tolerance_factor_increment * ctf_iter;

			// calculate spline start point
			auto q0x = input.end_point.x - (SIM_COS(angleBeforeCornerPoint) * ctf * cornering_tolerance);
			auto q0y = input.end_point.y - (SIM_SIN(angleBeforeCornerPoint) * ctf * cornering_tolerance);

			// calculate spline end point
			auto q1x = next_input.start_point.x + (SIM_COS(angleAfterCornerPoint) * ctf * cornering_tolerance);
			auto q1y = next_input.start_point.y + (SIM_SIN(angleAfterCornerPoint) * ctf * cornering_tolerance);

			// spline start speed
			auto v0x = input.final_feedrate * SIM_COS(angleBeforeCornerPoint);
			auto v0y = input.final_feedrate * SIM_SIN(angleBeforeCornerPoint);

			// spline end speed
			auto v1x = next_input.initial_feedrate * SIM_COS(angleAfterCornerPoint);
			auto v1y = next_input.initial_feedrate * SIM_SIN(angleAfterCornerPoint);

			// spline start acceleration (it should be zero if it's line to line spline)
			auto a0x = 0.0; // input.acceleration * SIM_COS(angleBeforeCornerPoint);
			auto a0y = 0.0; // input.acceleration* SIM_SIN(angleBeforeCornerPoint);

			// spline end acceleration (it should be zero if it's line to line spline)
			auto a1x = 0.0; // next_input.acceleration * SIM_COS(angleAfterCornerPoint);
			auto a1y = 0.0; // next_input.acceleration * SIM_SIN(angleAfterCornerPoint);

			// travel time
			auto Tx = current_spline_travel_time;
			auto Ty = current_spline_travel_time;

			int maximum_time_index = (int)(current_spline_travel_time * 1000.0);

			mid_res = {};

			// begin
			for (int time_index = 0; time_index <= maximum_time_index; ++time_index)
			{
				// time
				r64 t = (r64)time_index / 1000.0;

				// positions
				auto xp = (q0x + t * v0x + (a0x * SIM_SQUARE(t)) / 2.0 -
					(SIM_FIFTH_POWER(t) * (6.0 * q0x - 6.0 * q1x + 3.0 * Tx * v0x + 3.0 * Tx * v1x + (SIM_SQUARE(Tx) * a0x) / 2.0 -
					(SIM_SQUARE(Tx) * a1x) / 2.0)) / SIM_FIFTH_POWER(Tx) - (SIM_CUBE(t) * (10.0 * q0x - 10.0 * q1x + 6.0 * Tx * v0x + 4.0 * Tx * v1x +
					(3.0 * SIM_SQUARE(Tx) * a0x) / 2.0 - (SIM_SQUARE(Tx) * a1x) / 2.0)) / SIM_CUBE(Tx) + (SIM_FOURTH_POWER(t) *
					(15.0 * q0x - 15.0 * q1x + 8.0 * Tx * v0x + 7.0 * Tx * v1x + (3.0 * SIM_SQUARE(Tx) * a0x) / 2.0 - SIM_SQUARE(Tx) * a1x)) / SIM_FOURTH_POWER(Tx));

				auto yp = (q0y + t * v0y + (a0y * SIM_SQUARE(t)) / 2.0 -
					(SIM_FIFTH_POWER(t) * (6.0 * q0y - 6.0 * q1y + 3.0 * Ty * v0y + 3.0 * Ty * v1y + (SIM_SQUARE(Ty) * a0y) / 2.0 -
					(SIM_SQUARE(Ty) * a1y) / 2.0)) / SIM_FIFTH_POWER(Ty) - (SIM_CUBE(t) * (10.0 * q0y - 10.0 * q1y + 6.0 * Ty * v0y + 4.0 * Ty * v1y +
					(3.0 * SIM_SQUARE(t) * a0y) / 2.0 - (SIM_SQUARE(Ty) * a1y) / 2.0)) / SIM_CUBE(Ty) + (SIM_FOURTH_POWER(t) *
					(15.0 * q0y - 15.0 * q1y + 8.0 * Ty * v0y + 7.0 * Ty * v1y + (3.0 * SIM_SQUARE(Ty) * a0y) / 2.0 - SIM_SQUARE(Ty) * a1y)) / SIM_FOURTH_POWER(Ty));

				// velocities
				auto xv = (v0x + a0x * t - (5.0 * SIM_FOURTH_POWER(t) * (6.0 * q0x - 6.0 * q1x + 3.0 * Tx * v0x + 3.0 * Tx * v1x +
					(SIM_SQUARE(Tx) * a0x) / 2.0 - (SIM_SQUARE(Tx) * a1x) / 2.0)) / SIM_FIFTH_POWER(Tx) - (3.0 * SIM_SQUARE(t) * (10.0 * q0x - 10.0 * q1x + 6.0 * Tx * v0x + 4.0 * Tx * v1x +
					(3.0 * SIM_SQUARE(Tx) * a0x) / 2.0 - (SIM_SQUARE(Tx) * a1x) / 2.0)) / SIM_CUBE(Tx) + (4.0 * SIM_CUBE(t) * (15.0 * q0x - 15.0 * q1x + 8.0 * Tx * v0x + 7.0 * Tx * v1x +
					(3.0 * SIM_SQUARE(Tx) * a0x) / 2.0 - SIM_SQUARE(Tx) * a1x)) / SIM_FOURTH_POWER(Tx));

				auto yv = (v0y + a0y * t - (5.0 * SIM_FOURTH_POWER(t) * (6.0 * q0y - 6.0 * q1y + 3.0 * Ty * v0y + 3.0 * Ty * v1y +
					(SIM_SQUARE(Ty) * a0y) / 2.0 - (SIM_SQUARE(Ty) * a1y) / 2.0)) / SIM_FIFTH_POWER(Ty) - (3.0 * SIM_SQUARE(t) * (10.0 * q0y - 10.0 * q1y + 6.0 * Ty * v0y + 4.0 * Ty * v1y +
					(3.0 * SIM_SQUARE(Ty) * a0y) / 2.0 - (SIM_SQUARE(Ty) * a1y) / 2.0)) / SIM_CUBE(Ty) + (4.0 * SIM_CUBE(t) * (15.0 * q0y - 15.0 * q1y + 8.0 * Ty * v0y + 7.0 * Ty * v1y +
					(3.0 * SIM_SQUARE(Ty) * a0y) / 2.0 - SIM_SQUARE(Ty) * a1y)) / SIM_FOURTH_POWER(Ty));

				// accelerations
				auto xa = (a0x - (20.0 * SIM_CUBE(t) * (6.0 * q0x - 6.0 * q1x + 3.0 * Tx * v0x + 3.0 * Tx * v1x + (SIM_SQUARE(Tx) * a0x) / 2.0 - (SIM_SQUARE(Tx) * a1x) / 2.0)) / SIM_FIFTH_POWER(Tx) +
					(12.0 * SIM_SQUARE(t) * (15.0 * q0x - 15.0 * q1x + 8.0 * Tx * v0x + 7.0 * Tx * v1x + (3.0 * SIM_SQUARE(Tx) * a0x) / 2.0 - SIM_SQUARE(Tx) * a1x)) / SIM_FOURTH_POWER(Tx) -
					(6.0 * t * (10.0 * q0x - 10.0 * q1x + 6.0 * Tx * v0x + 4.0 * Tx * v1x + (3.0 * SIM_SQUARE(Tx) * a0x) / 2.0 - (SIM_SQUARE(Tx) * a1x) / 2.0)) / SIM_CUBE(Tx));

				auto ya = (a0y - (20.0 * SIM_CUBE(t) * (6.0 * q0y - 6.0 * q1y + 3.0 * Ty * v0y + 3.0 * Ty * v1y + (SIM_SQUARE(Ty) * a0y) / 2.0 - (SIM_SQUARE(Ty) * a1y) / 2.0)) / SIM_FIFTH_POWER(Ty) +
					(12.0 * SIM_SQUARE(t) * (15.0 * q0y - 15.0 * q1y + 8.0 * Ty * v0y + 7.0 * Ty * v1y + (3.0 * SIM_SQUARE(Ty) * a0y) / 2.0 - SIM_SQUARE(Ty) * a1y)) / SIM_FOURTH_POWER(Ty) -
					(6.0 * t * (10.0 * q0y - 10.0 * q1y + 6.0 * Ty * v0y + 4.0 * Ty * v1y + (3.0 * SIM_SQUARE(Ty) * a0y) / 2.0 - (SIM_SQUARE(Ty) * a1y) / 2.0)) / SIM_CUBE(Ty));

				// jerks
				auto xj = ((24.0 * t * (15.0 * q0x - 15.0 * q1x + 8.0 * Tx * v0x + 7.0 * Tx * v1x + (3.0 * SIM_SQUARE(Tx) * a0x) / 2.0 - SIM_SQUARE(Tx) * a1x)) / SIM_FOURTH_POWER(Tx) -
					(60.0 * SIM_SQUARE(t) * (6.0 * q0x - 6.0 * q1x + 3.0 * Tx * v0x + 3.0 * Tx * v1x + (SIM_SQUARE(Tx) * a0x) / 2.0 - (SIM_SQUARE(Tx) * a1x) / 2.0)) / SIM_FIFTH_POWER(Tx) -
					(6.0 * (10.0 * q0x - 10.0 * q1x + 6.0 * Tx * v0x + 4.0 * Tx * v1x + (3.0 * SIM_SQUARE(Tx) * a0x) / 2.0 - (SIM_SQUARE(Tx) * a1x) / 2.0)) / SIM_CUBE(Tx));

				auto yj = ((24.0 * t * (15.0 * q0y - 15.0 * q1y + 8.0 * Ty * v0y + 7.0 * Ty * v1y + (3.0 * SIM_SQUARE(Ty) * a0y) / 2.0 - SIM_SQUARE(Ty) * a1y)) / SIM_FOURTH_POWER(Ty) -
					(60.0 * SIM_SQUARE(t) * (6.0 * q0y - 6.0 * q1y + 3.0 * Ty * v0y + 3.0 * Ty * v1y + (SIM_SQUARE(Ty) * a0y) / 2.0 - (SIM_SQUARE(Ty) * a1y) / 2.0)) / SIM_FIFTH_POWER(Ty) -
					(6.0 * (10.0 * q0y - 10.0 * q1y + 6.0 * Ty * v0y + 4.0 * Ty * v1y + (3.0 * SIM_SQUARE(Ty) * a0y) / 2.0 - (SIM_SQUARE(Ty) * a1y) / 2.0)) / SIM_SQUARE(Ty));


				mid_res.tool_path.push_back({ xp, yp, input.end_point.z });
				mid_res.velocities.push_back({ xv, yv, 0.0 });
				mid_res.accelerations.push_back({ xa, ya, 0.0 });
				mid_res.jerks.push_back({ xj, yj, 0.0 });
			} // end for X(t), X'(t), X''(t), X'''(t)

			r64 sum = 0.0;

			for (int i = 0; i < maximum_time_index; ++i)
			{
				// NOTE(batuhan): Our mat3 is column-wise but it doesn't matter (det(A) = det(A^T)).
				r64 Area_PP1P2 = SIM_ONE_HALF * SIM_FABS(determinant({ mid_res.tool_path[i].x, mid_res.tool_path[i].y, 1, q0x, q0y, 1, input.end_point.x, input.end_point.y, 1 }));
				r64 Area_PP2P3 = SIM_ONE_HALF * SIM_FABS(determinant({ mid_res.tool_path[i].x, mid_res.tool_path[i].y, 1, input.end_point.x, input.end_point.y, 1, q1x, q1y, 1 }));
				r64 Area_PP3P1 = SIM_ONE_HALF * SIM_FABS(determinant({ mid_res.tool_path[i].x, mid_res.tool_path[i].y, 1, q1x, q1y, 1, q0x, q0y, 1 }));
				r64 Area_P1P2P3 = SIM_ONE_HALF * SIM_FABS(determinant({ q0x, q0y, 1, input.end_point.x, input.end_point.y, 1, q1x, q1y, 1 }));
				sum += ((Area_PP1P2 + Area_PP2P3 + Area_PP3P1) - Area_P1P2P3) / Area_P1P2P3;
			} // end for sum

			r64 vx_min = std::min_element(
				mid_res.velocities.begin(), mid_res.velocities.end(),
				[](auto const& a, auto const& b) { return a.x < b.x; })->x;

			r64 vx_max = std::max_element(
				mid_res.velocities.begin(), mid_res.velocities.end(),
				[](auto const& a, auto const& b) { return a.x < b.x; })->x;

			r64 vy_min = std::min_element(
				mid_res.velocities.begin(), mid_res.velocities.end(),
				[](auto const& a, auto const& b) { return a.y < b.y; })->y;

			r64 vy_max = std::max_element(
				mid_res.velocities.begin(), mid_res.velocities.end(),
				[](auto const& a, auto const& b) { return a.y < b.y; })->y;

			r64 ax_min = std::min_element(
				mid_res.accelerations.begin(), mid_res.accelerations.end(),
				[](auto const& a, auto const& b) { return a.x < b.x; })->x;

			r64 ax_max = std::max_element(
				mid_res.accelerations.begin(), mid_res.accelerations.end(),
				[](auto const& a, auto const& b) { return a.x < b.x; })->x;

			r64 ay_min = std::min_element(
				mid_res.accelerations.begin(), mid_res.accelerations.end(),
				[](auto const& a, auto const& b) { return a.y < b.y; })->y;

			r64 ay_max = std::max_element(
				mid_res.accelerations.begin(), mid_res.accelerations.end(),
				[](auto const& a, auto const& b) { return a.y < b.y; })->y;

			r64 jx_min = std::min_element(
				mid_res.jerks.begin(), mid_res.jerks.end(),
				[](auto const& a, auto const& b) { return a.x < b.x; })->x;

			r64 jx_max = std::max_element(
				mid_res.jerks.begin(), mid_res.jerks.end(),
				[](auto const& a, auto const& b) { return a.x < b.x; })->x;

			r64 jy_min = std::min_element(
				mid_res.jerks.begin(), mid_res.jerks.end(),
				[](auto const& a, auto const& b) { return a.y < b.y; })->y;

			r64 jy_max = std::max_element(
				mid_res.jerks.begin(), mid_res.jerks.end(),
				[](auto const& a, auto const& b) { return a.y < b.y; })->y;

			check_two = sum / (maximum_time_index);
			check_one =
			{
				(vx_max - input.feedrate) / input.feedrate,
				(vy_max - input.feedrate) / input.feedrate,
				(-vx_min - input.feedrate) / input.feedrate,
				(-vy_min - input.feedrate) / input.feedrate,
				(ax_max - input.acceleration) / input.acceleration,
				(ay_max - input.acceleration) / input.acceleration,
				(-ax_min - input.deceleration) / input.deceleration,
				(-ay_min - input.deceleration) / input.deceleration,
				(jx_max - jmax) / jmax,
				(jy_max - jmax) / jmax,
				(-jx_min - jmax) / jmax,
				(-jy_min - jmax) / jmax
			};

			auto check_one_max = *std::max_element(check_one.begin(), check_one.end());
			auto check_one_min_spec = *std::min_element(check_one.begin() + 1, check_one.end(), [](auto const& a, auto const& b) { return SIM_FABS(a) < SIM_FABS(b); });

			if (check_two < 1e-2 &&
  				check_one_max <= 0.0 &&
				check_one_min_spec <= 0.3)
			{
				spline_fit = true;
				break;
			}
		} // end for ctf iteration
		current_spline_travel_time += spline_travel_time_increment;
	} // end while(check)

	u64 point_count = 0;

	if (spline_fit)
	{
		Interpolation_Input linear_path;
		linear_path = input;
		linear_path.end_point = mid_res.tool_path[0];

		point_count += SIM_linear_interpolation(linear_path, result);

		// not pushing the first and last point of spline to prevent duplication ( [begin() + 1] to [end()] )
		result->tool_path.insert(result->tool_path.end(), mid_res.tool_path.begin() + 1, mid_res.tool_path.end());
		result->velocities.insert(result->velocities.end(), mid_res.velocities.begin() + 1, mid_res.velocities.end());
		result->accelerations.insert(result->accelerations.end(), mid_res.accelerations.begin() + 1, mid_res.accelerations.end());
		result->jerks.insert(result->jerks.end(), mid_res.jerks.begin() + 1, mid_res.jerks.end());

		point_count += mid_res.tool_path.size() - 1;
	}

	return point_count;
}
