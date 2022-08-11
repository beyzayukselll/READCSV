#include "CLI.h"

#include "module_1.h"
#include "global_data_area.h"
#include "sim_functions.h"
#include "sim_config.h"

#include <iostream>
#include <fstream>

extern CLI *cli;

#define TODO_CFG_JOB_BUFFER_LIMIT		15000
#define TODO_CFG_CORNERING_TOLERANCE	5

void Module_1::initialize(Servo_Master_Base *servo_master)
{
	cli = CLI::get_cli();

	m_ServoMaster = servo_master;
	#if SERVO_COUNT == 3
	 	m_Axes = { AXIS_X, AXIS_Y, AXIS_Z };
	#else
		m_Axes = { AXIS_X };
	#endif

	cli->log("Module_1::initialize()");
	
	m_State = CNC_State::CNC_STATE_IDLE;
	m_NextState = CNC_State::CNC_STATE_IDLE;
}

void Module_1::get_inputs()
{
	Data_Area::get_module_1_inputs(&inputs);
}

void Module_1::set_outputs()
{
	Data_Area::set_module_1_outputs(&outputs);
}

void Module_1::tick()
{
	switch (m_State)
	{
		case CNC_State::CNC_STATE_IDLE:
		{
			switch (m_NextState)
			{
				case CNC_State::CNC_STATE_JOG:
				{
					if (set_all_axes_opmode(Mode_Of_Operation::OP_CSV))
					{
						m_State = CNC_State::CNC_STATE_JOG;
					}
				}
				break;

				case CNC_State::CNC_STATE_CUT:
				{
					if (set_all_axes_opmode(Mode_Of_Operation::OP_CSP))
					{
						cli->log("state is CNC_STATE_CUT");
						
						#if FAKE_SERVO
							if(file == nullptr)
							{
								file = new std::fstream("trajectory_dump.csv", std::ios::out | std::ios::trunc);

								for(int i = 0; i < SERVO_COUNT; ++i)
								{
									*file << "Pos" << i << ";" << "Vel" << i << ";" << "Acc" << i << ";" << "Jerk" << i;
									if(i != SERVO_COUNT - 1) *file << ";";
									else *file << std::endl;
								}
							}
							else
							{
								cli->log("file error !");
							}
						#endif

						m_State = CNC_State::CNC_STATE_CUT;
					}
				}
				break;
				default:
				break;
			}
		}
		break;

		case CNC_State::CNC_STATE_JOG:
		{
			switch (m_NextState)
			{
				case CNC_State::CNC_STATE_IDLE:
				if (set_all_axes_opmode(Mode_Of_Operation::OP_CSP))
				{
					m_State = CNC_State::CNC_STATE_IDLE;
					outputs.state = m_State;
				}
				break;
				default:
				break;
			}
		}
		break;

		case CNC_State::CNC_STATE_CUT:
		{
			if (m_InterpolationIndex == m_JobQueue.size())
			{
				if (m_CurrentInstructionIndex == m_Instructions.size())
				{
					if (inputs.feed_buffer_empty_internal)
					{
						cli->log("module1 to STOP");
						Data_Area::global_job_queue_clear();
						m_JobQueue.clear();

						#if FAKE_SERVO	
							if(file->is_open())
								file->close();
								file = nullptr;
						#endif

						m_State = CNC_State::CNC_STATE_IDLE;
						m_NextState = CNC_State::CNC_STATE_IDLE;
					}
				}
				else
				{
					auto current_instruction = m_Instructions.begin() + m_CurrentInstructionIndex;
					auto next_instruction = current_instruction;
					if (next_instruction != m_Instructions.end())
					{
						next_instruction++;
					}

					Interpolation_Output output = {};
					u64 generated_point_count = 0;
					if (m_InterpolationIndex < TODO_CFG_JOB_BUFFER_LIMIT)
					{
						if (current_instruction->type == Instruction_Type::INSTRUCTION_SPINDLE)
						{
							m_JobQueue.push_back(
								{
									current_instruction->type,
									{ 0, 0, 0 },
									{ 0, 0, 0 },
									{ 0, 0, 0 },
									{ 0, 0, 0 },
									current_instruction->spindle_input.speed,
									current_instruction->spindle_input.direction
								});

							m_InterpolationIndex++;
						}
						else
						{
							bool is_last_instruction = next_instruction == m_Instructions.end();
							bool generate_spline = m_IsMicroSplineEnabled && !is_last_instruction;

							// TODO(batuhan): @ASK if need to set this if microspline is enabled and contouring disabled
							if (m_IsContouringEnabled || m_IsMicroSplineEnabled)
							{
								current_instruction->input.final_feedrate = current_instruction->input.feedrate;
								if (!is_last_instruction)
								{
									next_instruction->input.initial_feedrate = current_instruction->input.final_feedrate;
								}
							}

							if (is_last_instruction)
							{
								current_instruction->input.final_feedrate = 0;
							}

							if (generate_spline)
							{
								// TODO(batuhan): Need to integrate 3D spline library.
								generated_point_count += SIM_trajectory_with_spline(current_instruction->input, next_instruction->input, &output, TODO_CFG_CORNERING_TOLERANCE);

								// TODO(batuhan): Can we get rid of this check, it's here just to be safe for now.
								if (generated_point_count)
								{
									next_instruction->input.start_point = output.tool_path.back();
								}
							}
							// TODO(batuhan): @ASK There is this check but i think it's just put there because of z-axis spline block. can't we just do "else"?
							if (generated_point_count == 0)
							// else
							{
								if(!m_IsContouringEnabled)
								{
									current_instruction->input.initial_feedrate = 0;
									current_instruction->input.final_feedrate = 0;
								}

								switch (current_instruction->type)
								{
									case Instruction_Type::INSTRUCTION_LINESEGMENT:
									{
										generated_point_count = SIM_linear_interpolation(current_instruction->input, &output);
									}
									break;

									case Instruction_Type::INSTRUCTION_ARCSEGMENT:
									{
										generated_point_count = SIM_circular_interpolation(current_instruction->input, &output);
									}
									break;
								}
							}

							cli->log("generated_point_count: %d", generated_point_count);
							m_CurrentInstructionIndex++;
							m_InterpolationIndex += generated_point_count;

							#if FAKE_SERVO
								if(file->is_open())
									for(int i = 0; i < generated_point_count; i++)
									{
										*file << output.tool_path[i].x << ";"
											<< output.velocities[i].x << ";"
											<< output.accelerations[i].x << ";"
											<< output.jerks[i].x << ";"
											<< output.tool_path[i].y << ";"
											<< output.velocities[i].y << ";"
											<< output.accelerations[i].y << ";"
											<< output.jerks[i].y << ";"
											<< output.tool_path[i].z << ";"
											<< output.velocities[i].z << ";"
											<< output.accelerations[i].z << ";"
											<< output.jerks[i].z << std::endl;
									}
							#endif

							for (u64 i = 0; i < generated_point_count; ++i)
							{
								m_JobQueue.push_back(
									{
										current_instruction->type,
										output.tool_path[i],
										output.velocities[i],
										output.accelerations[i],
										output.jerks[i],
										0,
										Spindle_Direction::STOP
									});

							}
						}
					}
				}
			}
		
			if(!m_JobQueue.empty())
			{
				int written = Data_Area::global_job_queue_write(&m_JobQueue, 100);
				m_InterpolationIndex -= written;
				// cli->log("written: %d", written);
				outputs.state = m_State;

			}

			if(m_NextState == CNC_State::CNC_STATE_IDLE)
			{
				if(outputs.state != CNC_State::CNC_STATE_IDLE)
				{
					cli->log("module2 to STOP");
					outputs.state = CNC_State::CNC_STATE_IDLE;
					Data_Area::global_job_queue_clear();
					m_Instructions.clear();
					m_CurrentInstructionIndex = 0;
					m_JobQueue.clear();
					m_InterpolationIndex = 0;
					return;
				}
			}
		}
		break;
	}
}

bool Module_1::set_all_axes_opmode(Mode_Of_Operation requested_mode)
{
	bool result = true;

	for (auto axis : m_Axes)
	{
		if (m_ServoMaster->get_mode_of_operation(axis) != requested_mode)
		{
			m_ServoMaster->set_mode_of_operation(axis, requested_mode);
			result = false;
		}
	}

	return result;
}

void Module_1::start_cut()
{
	m_NextState = CNC_State::CNC_STATE_CUT;
}

void Module_1::stop_cut()
{
	m_NextState = CNC_State::CNC_STATE_IDLE;
}

std::vector<Servo_Axis>& Module_1::get_axes()
{
	return m_Axes;
}

void Module_1::load_test_trajectory()
{
	Instruction ins;
	
	ins.type = Instruction_Type::INSTRUCTION_LINESEGMENT;
	ins.input.start_point = { 0, 0, 0 };
	ins.input.end_point = { 10, 10, 10 };
	ins.input.feedrate = 5;
	ins.input.acceleration = 2000;
	ins.input.deceleration = 2000;

	m_Instructions.push_back(ins);

	ins.input.start_point = { 10, 10, 10 };
	ins.input.end_point = { 0, 0, 0 };
	ins.input.feedrate = 10;
	ins.input.acceleration = 2000;
	ins.input.deceleration = 2000;

	m_Instructions.push_back(ins);

	cli->log("trajectory loaded");
}
