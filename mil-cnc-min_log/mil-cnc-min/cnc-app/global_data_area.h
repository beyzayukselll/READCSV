#if !defined(GLOBAL_DATA_AREA_H)

#include "module_services.h"
#include "sim_instruction.h"
#include "sim_utils.h"
#include <deque>
#include <mutex>
#include <cstring>

// namespace ?
struct Data_Area
{
	static Module_1_Inputs			g_Module_1_Inputs;
	static Module_1_Outputs			g_Module_1_Outputs;
	static Module_2_Inputs			g_Module_2_Inputs;
	static Module_2_Outputs			g_Module_2_Outputs;
	static Module_3_Inputs			g_Module_3_Inputs;
	static Module_3_Outputs			g_Module_3_Outputs;

	// TODO(batuhan): Move somewhere else
	static std::mutex			g_TrajectoryBufferMutex; //guards g_TrajectoryBuffer
	static std::deque<Job>		g_TrajectoryBuffer;

	// TODO(batuhan): Compressable functions
	static u64 global_job_queue_write(std::deque<Job>* src, u64 len)
	{
		u64 copy_size = 0;

		if (src)
		{
			std::lock_guard<std::mutex> lock(g_TrajectoryBufferMutex);
			copy_size = SIM_MIN(len, src->size());
			g_TrajectoryBuffer.insert(g_TrajectoryBuffer.end(), src->begin(), src->begin() + copy_size);
			src->erase(src->begin(), src->begin() + copy_size);
		}

		return copy_size;
	}

	static u64 global_job_queue_read(std::deque<Job>* out, u64 len)
	{
		u64 copy_size = 0;

		if (out)
		{
			std::lock_guard<std::mutex> lock(g_TrajectoryBufferMutex);
			copy_size = SIM_MIN(len, g_TrajectoryBuffer.size());
			out->insert(out->end(), g_TrajectoryBuffer.begin(), g_TrajectoryBuffer.begin() + copy_size);
			g_TrajectoryBuffer.erase(g_TrajectoryBuffer.begin(), g_TrajectoryBuffer.begin() + copy_size);
		}

		return copy_size;
	}

	static void global_job_queue_clear()
	{
		std::lock_guard<std::mutex> lock(g_TrajectoryBufferMutex);
		g_TrajectoryBuffer.clear();
	}

	static void get_module_1_inputs(Module_1_Inputs* out)
	{
		(*out).feed_buffer_empty_internal.store(g_Module_1_Inputs.feed_buffer_empty_internal);	
		(*out).state.store(g_Module_1_Inputs.state);
		(*out).servo_x_power.store(g_Module_1_Inputs.servo_x_power);
		(*out).servo_y_power.store(g_Module_1_Inputs.servo_y_power);
		(*out).servo_z_power.store(g_Module_1_Inputs.servo_z_power);
		(*out).spindle_direction.store(g_Module_1_Inputs.spindle_direction);
		(*out).spindle_speed.store(g_Module_1_Inputs.spindle_speed);
		(*out).spindle_speed_factor.store(g_Module_1_Inputs.spindle_speed_factor);
		(*out).jog_factor_x.store(g_Module_1_Inputs.jog_factor_x);
		(*out).jog_factor_y.store(g_Module_1_Inputs.jog_factor_y);
		(*out).jog_factor_z.store(g_Module_1_Inputs.jog_factor_z);
		(*out).go_zero.store(g_Module_1_Inputs.go_zero);
		(*out).reset_axis.store(g_Module_1_Inputs.reset_axis);
	}

	static void get_module_2_inputs(Module_2_Inputs* out)
	{
		(*out).state.store(g_Module_2_Inputs.state);
		(*out).jog_factor_x.store(g_Module_2_Inputs.jog_factor_x);
		(*out).jog_factor_y.store(g_Module_2_Inputs.jog_factor_y);
		(*out).jog_factor_z.store(g_Module_2_Inputs.jog_factor_z);
		(*out).spindle_direction.store(g_Module_2_Inputs.spindle_direction);
		(*out).spindle_speed.store(g_Module_2_Inputs.spindle_speed);
	}

	static void get_module_3_inputs(Module_3_Inputs* out)
	{
		(*out).axis_x_pos.store(g_Module_3_Inputs.axis_x_pos);
		(*out).axis_x_pos_act.store(g_Module_3_Inputs.axis_x_pos_act);
		(*out).axis_x_vel.store(g_Module_3_Inputs.axis_x_vel);
		(*out).axis_x_vel_act.store(g_Module_3_Inputs.axis_x_vel_act);
		(*out).axis_y_pos.store(g_Module_3_Inputs.axis_y_pos);
		(*out).axis_y_pos_act.store(g_Module_3_Inputs.axis_y_pos_act);
		(*out).axis_y_vel.store(g_Module_3_Inputs.axis_y_vel);
		(*out).axis_y_vel_act.store(g_Module_3_Inputs.axis_y_pos_act);
		(*out).axis_z_pos.store(g_Module_3_Inputs.axis_z_pos);
		(*out).axis_z_pos_act.store(g_Module_3_Inputs.axis_z_pos_act);
		(*out).axis_z_vel.store(g_Module_3_Inputs.axis_z_vel);
		(*out).axis_z_vel_act.store(g_Module_3_Inputs.axis_z_vel_act);
		(*out).servo_x_power.store(g_Module_3_Inputs.servo_x_power);
		(*out).servo_y_power.store(g_Module_3_Inputs.servo_y_power);
		(*out).servo_z_power.store(g_Module_3_Inputs.servo_z_power);
		(*out).state.store(g_Module_3_Inputs.state);
		(*out).jog_factor_x.store(g_Module_3_Inputs.jog_factor_x);
		(*out).jog_factor_y.store(g_Module_3_Inputs.jog_factor_y);
		(*out).jog_factor_z.store(g_Module_3_Inputs.jog_factor_z);
		(*out).spindle_direction.store(g_Module_3_Inputs.spindle_direction);
		(*out).spindle_speed.store(g_Module_3_Inputs.spindle_speed);
		(*out).spindle_speed_factor.store(g_Module_3_Inputs.spindle_speed_factor);
	}

	static void set_module_1_outputs(Module_1_Outputs* in)
	{
		// ! store outputs
		g_Module_1_Outputs.state.store(in->state);
		g_Module_1_Outputs.jog_factor_x.store(in->jog_factor_x);
		g_Module_1_Outputs.jog_factor_y.store(in->jog_factor_y);
		g_Module_1_Outputs.jog_factor_z.store(in->jog_factor_z);
		g_Module_1_Outputs.spindle_speed.store(in->spindle_speed);
		g_Module_1_Outputs.spindle_direction.store(in->spindle_direction);
		g_Module_1_Outputs.servo_x_power.store(in->servo_x_power);
		g_Module_1_Outputs.servo_y_power.store(in->servo_y_power);
		g_Module_1_Outputs.servo_z_power.store(in->servo_z_power);
		g_Module_1_Outputs.spindle_speed_factor.store(in->spindle_speed_factor);

		// ! update inputs (module 1 to module 2)
		g_Module_2_Inputs.state.store(g_Module_1_Outputs.state);
		g_Module_2_Inputs.jog_factor_x.store(g_Module_1_Outputs.jog_factor_x);
		g_Module_2_Inputs.jog_factor_y.store(g_Module_1_Outputs.jog_factor_y);
		g_Module_2_Inputs.jog_factor_z.store(g_Module_1_Outputs.jog_factor_z);
		g_Module_2_Inputs.spindle_speed.store(g_Module_1_Outputs.spindle_speed);
		g_Module_2_Inputs.spindle_direction.store(g_Module_1_Outputs.spindle_direction);

		// ! update inputs (module 1 to module 3)
		g_Module_3_Inputs.state.store(g_Module_1_Outputs.state);
		g_Module_3_Inputs.jog_factor_x.store(g_Module_1_Outputs.jog_factor_x);
		g_Module_3_Inputs.jog_factor_y.store(g_Module_1_Outputs.jog_factor_y);
		g_Module_3_Inputs.jog_factor_z.store(g_Module_1_Outputs.jog_factor_z);
		g_Module_3_Inputs.spindle_speed.store(g_Module_1_Outputs.spindle_speed);
		g_Module_3_Inputs.spindle_direction.store(g_Module_1_Outputs.spindle_direction);
		{
			// TODO(ertugrul) : its going to be changed 
			g_Module_3_Inputs.spindle_speed_factor.store(10);
		}
	}

	static void set_module_2_outputs(Module_2_Outputs* in)
	{
		// ! store outputs
		g_Module_2_Outputs.feed_buffer_empty_internal.store(in->feed_buffer_empty_internal);
		g_Module_2_Outputs.axis_x_pos.store(in->axis_x_pos);
		g_Module_2_Outputs.axis_x_pos_act.store(in->axis_x_pos_act);
		g_Module_2_Outputs.axis_x_vel.store(in->axis_x_vel);
		g_Module_2_Outputs.axis_x_vel_act.store(in->axis_x_vel_act);
		g_Module_2_Outputs.axis_y_pos.store(in->axis_y_pos);
		g_Module_2_Outputs.axis_y_pos_act.store(in->axis_y_pos_act);
		g_Module_2_Outputs.axis_y_vel.store(in->axis_y_vel);
		g_Module_2_Outputs.axis_y_vel_act.store(in->axis_y_vel_act);
		g_Module_2_Outputs.axis_z_pos.store(in->axis_z_pos);
		g_Module_2_Outputs.axis_z_pos_act.store(in->axis_z_pos_act);
		g_Module_2_Outputs.axis_z_vel.store(in->axis_z_vel);
		g_Module_2_Outputs.axis_z_vel_act.store(in->axis_z_vel_act);
		g_Module_2_Outputs.servo_x_power.store(in->servo_x_power);
		g_Module_2_Outputs.servo_y_power.store(in->servo_y_power);
		g_Module_2_Outputs.servo_z_power.store(in->servo_z_power);
	
		// ! update inputs (module 2 to module 1)
		g_Module_1_Inputs.feed_buffer_empty_internal.store(g_Module_2_Outputs.feed_buffer_empty_internal);

		// ! update inputs (module 2 to module 3)
		g_Module_3_Inputs.axis_x_pos.store(g_Module_2_Outputs.axis_x_pos);
		g_Module_3_Inputs.axis_x_pos_act.store(g_Module_2_Outputs.axis_x_pos_act);
		g_Module_3_Inputs.axis_x_vel.store(g_Module_2_Outputs.axis_x_vel);
		g_Module_3_Inputs.axis_x_vel_act.store(g_Module_2_Outputs.axis_x_vel_act);
		g_Module_3_Inputs.axis_y_pos.store(g_Module_2_Outputs.axis_y_pos);
		g_Module_3_Inputs.axis_y_pos_act.store(g_Module_2_Outputs.axis_y_pos_act);
		g_Module_3_Inputs.axis_y_vel.store(g_Module_2_Outputs.axis_y_vel);
		g_Module_3_Inputs.axis_y_vel_act.store(g_Module_2_Outputs.axis_y_vel_act);
		g_Module_3_Inputs.axis_z_pos.store(g_Module_2_Outputs.axis_z_pos);
		g_Module_3_Inputs.axis_z_pos_act.store(g_Module_2_Outputs.axis_z_pos_act);
		g_Module_3_Inputs.axis_z_vel.store(g_Module_2_Outputs.axis_z_vel);
		g_Module_3_Inputs.axis_z_vel_act.store(g_Module_2_Outputs.axis_z_vel_act);
		g_Module_3_Inputs.servo_x_power.store(g_Module_2_Outputs.servo_x_power);
		g_Module_3_Inputs.servo_y_power.store(g_Module_2_Outputs.servo_y_power);
		g_Module_3_Inputs.servo_z_power.store(g_Module_2_Outputs.servo_z_power);
	}

	static void set_module_3_outputs(Module_3_Outputs* in)
	{
		// ! store outputs
		g_Module_3_Outputs.state.store(in->state);
		g_Module_3_Outputs.servo_x_power.store(in->servo_x_power);
		g_Module_3_Outputs.servo_y_power.store(in->servo_y_power);
		g_Module_3_Outputs.servo_z_power.store(in->servo_z_power);
		g_Module_3_Outputs.spindle_direction.store(in->spindle_direction);
		g_Module_3_Outputs.spindle_speed.store(in->spindle_speed);
		g_Module_3_Outputs.spindle_speed_factor.store(in->go_zero);
		g_Module_3_Outputs.jog_factor_x.store(in->jog_factor_x);
		g_Module_3_Outputs.jog_factor_y.store(in->jog_factor_y);
		g_Module_3_Outputs.jog_factor_z.store(in->jog_factor_z);
		g_Module_3_Outputs.reset_axis.store(in->reset_axis);
		g_Module_3_Outputs.go_zero.store(in->go_zero);
		
		// ! update inputs (module 3 to module 1)
		g_Module_1_Inputs.state.store(g_Module_3_Outputs.state);
		g_Module_1_Inputs.servo_x_power.store(g_Module_3_Outputs.servo_x_power);
		g_Module_1_Inputs.servo_y_power.store(g_Module_3_Outputs.servo_y_power);
		g_Module_1_Inputs.servo_z_power.store(g_Module_3_Outputs.servo_z_power);
		g_Module_1_Inputs.jog_factor_x.store(g_Module_3_Outputs.jog_factor_x);
		g_Module_1_Inputs.jog_factor_y.store(g_Module_3_Outputs.jog_factor_y);
		g_Module_1_Inputs.jog_factor_z.store(g_Module_3_Outputs.jog_factor_z);
		g_Module_1_Inputs.spindle_direction.store(g_Module_3_Outputs.spindle_direction);
		g_Module_1_Inputs.spindle_speed.store(g_Module_3_Outputs.spindle_speed);
		g_Module_1_Inputs.spindle_speed_factor.store(g_Module_3_Outputs.spindle_speed_factor);
		g_Module_1_Inputs.go_zero.store(g_Module_3_Outputs.go_zero);
		g_Module_1_Inputs.reset_axis.store(g_Module_3_Outputs.reset_axis);

		// ! update inputs (module 3 to module 2)	
	}

};



#define GLOBAL_DATA_AREA_H
#endif