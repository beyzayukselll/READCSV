#include "CLI.h"

#include "module_2.h"
#include "global_data_area.h"
#include "sim_config.h"

#include <iostream>

extern CLI *cli;

#define READ_CNT					50
#define ENCODER_RESOLUTION			8192
#define SCREW_LEAD					5.0
#define MIN_TO_						600000
#define NOMINAL_TORQUE				2.37
#define INERTIA						0.000109
#define SIM_TWO_PI					6.283185307179586
#define DEFAULT_JOG_SPEED_MMPS		2.0
#define JOG_FACTOR_MAX				2
#define pos_to_encoder_inc(a)		(i64)((a) * 1000)	// (i64)(((a) * ENCODER_RESOLUTION) / SCREW_LEAD)
#define mmps_to_rpm(a)				(i64)((a) * 1000) 			// (i64)(((a) * MIN_TO_) / SCREW_LEAD)
#define acc_to_torque(a)			// (i16)((a) * (((INERTIA * SIM_TWO_PI) / SCREW_LEAD) * (1000.0 / NOMINAL_TORQUE)))
#define encoder_inc_to_pos(a)		a // (r64)(((r64)(a) * SCREW_LEAD) / ENCODER_RESOLUTION) 
#define rpm_to_mmps(a)				a // (r64)(((r64)(a) * SCREW_LEAD) / MIN_TO_)
#define torque_to_acc(a)			// (r64)((r64)(a) / (((INERTIA * SIM_TWO_PI) / SCREW_LEAD) * (1000.0 / NOMINAL_TORQUE)))

void Module_2::initialize(Servo_Master_Base *servo_master)
{
	m_ServoMaster = servo_master;

	cli->log("Module_2::initialize()");

	#if SERVO_COUNT == 3
	 	m_Axes = { AXIS_X, AXIS_Y, AXIS_Z };
	#else
		m_Axes = { AXIS_X };
	#endif

	m_FilterBufferXWriteIdx = 0;
	m_FilterBufferYWriteIdx = 0;
	m_FilterBufferZWriteIdx = 0;

	m_ServoMaster->set_state_op();

	cli->log("master :  0x%x", m_ServoMaster->get_master_state()); 

	for (auto axis : m_Axes)
	{
		m_ServoMaster->receive_pdo();
		m_ServoMaster->set_control_word(axis, 0x6);
		m_ServoMaster->publish_pdo();
		osal_usleep(10000);

		cli->log("statusword : 0x%x", m_ServoMaster->get_status_word(axis));

		m_ServoMaster->receive_pdo();
		//position_offsets.x = m_ServoMaster->get_actual_position(axis);
		position_offsets.data[axis] = m_ServoMaster->get_actual_position(axis);
		m_ServoMaster->set_target_position(axis, position_offsets.data[axis]);
		m_ServoMaster->publish_pdo();
		osal_usleep(10000);

		m_ServoMaster->receive_pdo();
		m_ServoMaster->set_control_word(axis, 0x80);
		m_ServoMaster->publish_pdo();
		osal_usleep(10000);

		cli->log("statusword : 0x%x", m_ServoMaster->get_status_word(axis));

		m_ServoMaster->receive_pdo();
		m_ServoMaster->set_control_word(axis, 0x6);
		m_ServoMaster->publish_pdo();
		osal_usleep(10000);

		cli->log("statusword : 0x%x", m_ServoMaster->get_status_word(axis));

		m_ServoMaster->receive_pdo();
		m_ServoMaster->set_mode_of_operation(axis, 0x08);
		m_ServoMaster->publish_pdo();
		osal_usleep(10000);

		cli->log("statusword : 0x%x", m_ServoMaster->get_status_word(axis));

		m_ServoMaster->receive_pdo();
		m_ServoMaster->set_control_word(axis, 0xf);
		m_ServoMaster->publish_pdo();
		osal_usleep(10000);
		cli->log("statusword : 0x%x", m_ServoMaster->get_status_word(axis));
	}
}

void Module_2::get_inputs()
{
	Data_Area::get_module_2_inputs(&inputs);
}

void Module_2::set_outputs()
{
	Data_Area::set_module_2_outputs(&outputs);
}

void Module_2::tick()
{
	if (m_ServoMaster->get_master_state() == EC_STATE_OPERATIONAL)
	{
		m_ServoMaster->receive_pdo();
	}

	switch (inputs.state)
	{
		case CNC_State::CNC_STATE_IDLE:
		{
			memset(m_FilterBufferX, 0, sizeof(m_FilterBufferX));
			memset(m_FilterBufferY, 0, sizeof(m_FilterBufferY));
			memset(m_FilterBufferZ, 0, sizeof(m_FilterBufferZ));
			m_CurrentJobQueue.clear();

			for (auto axis : m_Axes)
			{
				current_velocities_mmps.data[axis] = 0;
				current_velocities.data[axis] = 0;
				m_ServoMaster->set_target_position(axis, current_positions.data[axis] + position_offsets.data[axis]);
				m_ServoMaster->set_velocity_offset(axis, current_velocities.data[axis]);
			}

			outputs.feed_buffer_empty_internal = true;
		}
		break;

		case CNC_State::CNC_STATE_JOG:
		{
			//switch(inputs.spindle_direction)
			do_jog_out(AXIS_X, m_FilterBufferX, &m_FilterBufferXWriteIdx, inputs.jog_factor_x);
			do_jog_out(AXIS_Y, m_FilterBufferY, &m_FilterBufferYWriteIdx, inputs.jog_factor_y);
			do_jog_out(AXIS_Z, m_FilterBufferZ, &m_FilterBufferZWriteIdx, inputs.jog_factor_z);
		}
		break;

		case CNC_State::CNC_STATE_CUT:
		{
			outputs.feed_buffer_empty_internal = false;

			if (m_CurrentJobQueue.size() == 0)
			{
				int read = Data_Area::global_job_queue_read(&m_CurrentJobQueue, READ_CNT);
			}

			if (m_CurrentJobQueue.size() > 0)
			{
				while (m_CurrentJobQueue.front().type == INSTRUCTION_SPINDLE)
				{
					auto& current_job = m_CurrentJobQueue.front();
					m_CurrentJobQueue.pop_front();
				}

				for (auto axis : m_Axes)
				{
					// TODO(ertugrul): maybe i should write it directly to output ?
					current_positions_mm.data[axis] = m_CurrentJobQueue.front().tool_path.e[axis];
					current_positions.data[axis] = pos_to_encoder_inc(m_CurrentJobQueue.front().tool_path.e[axis]);
					current_velocities_mmps.data[axis] = m_CurrentJobQueue.front().velocity.e[axis];
					current_velocities.data[axis] = mmps_to_rpm(m_CurrentJobQueue.front().velocity.e[axis]);
					m_ServoMaster->set_target_position(axis, current_positions.data[axis] + position_offsets.data[axis]);
					m_ServoMaster->set_velocity_offset(axis, current_velocities.data[axis]);
					//m_ServoMaster->set_target_acceleration(axis, acc_to_torque(m_CurrentJobQueue.front().acceleration.e[axis]));
				}

				m_CurrentJobQueue.pop_front();
			}
			else
			{
				for (auto axis : m_Axes)
				{
					m_ServoMaster->set_velocity_offset(axis, 0);
				}

				outputs.feed_buffer_empty_internal = true;
			}
		}
		break;
	}

	if (m_ServoMaster->get_master_state() == EC_STATE_OPERATIONAL)
	{
		m_ServoMaster->publish_pdo();
	}
	
	{
		// * set current data
		outputs.axis_x_pos = current_positions_mm.x;
		outputs.axis_x_pos_act = current_positions.x;
		outputs.axis_x_vel = current_velocities_mmps.x;
		outputs.axis_x_vel_act = current_velocities.x;
		outputs.axis_y_pos = current_positions_mm.y;
		outputs.axis_y_pos_act = current_positions.y;
		outputs.axis_y_vel = current_velocities_mmps.y;
		outputs.axis_y_vel_act = current_velocities.y;
		outputs.axis_z_pos = current_positions_mm.z;
		outputs.axis_z_pos_act = current_positions.z;
		outputs.axis_z_vel = current_velocities_mmps.z;
		outputs.axis_z_vel_act = current_velocities.z;
		outputs.servo_x_power = 1;
		outputs.servo_y_power = 1;
		outputs.servo_z_power = 1;
	}
}

r64 Module_2::filter(r64* buffer, u32* write_index, r64 val)
{
	r64 result = 0.0;

	buffer[*write_index] = val;
	*write_index = (*write_index + 1) % FILTER_BUFFER_SIZE;
	for (u64 i = 0; i < FILTER_BUFFER_SIZE; ++i)
	{
		result += buffer[i];
	}

	return result / FILTER_BUFFER_SIZE;
}

inline
void Module_2::do_jog_out(Servo_Axis axis, r64* buffer, u32* index, Jog_Factor jog_factor)
{
	r64 t = 0.0;
	t = filter(buffer,
			   index,
			   (DEFAULT_JOG_SPEED_MMPS * (r64)jog_factor / JOG_FACTOR_MAX));
	m_ServoMaster->set_velocity_offset(axis, t);
}


void Module_2::deinitialize()
{
	for( auto axis: m_Axes )
	{
		m_ServoMaster->receive_pdo();
		m_ServoMaster->set_control_word(axis, 0x06);
		m_ServoMaster->publish_pdo();
		osal_usleep(10000);

		m_ServoMaster->receive_pdo();
		m_ServoMaster->set_control_word(axis, 0x80);
		m_ServoMaster->publish_pdo();
		osal_usleep(10000);

		m_ServoMaster->receive_pdo();
		m_ServoMaster->set_control_word(axis, 0x06);
		m_ServoMaster->publish_pdo();
		osal_usleep(10000);

		m_ServoMaster->set_state_safe_op();
	}
}