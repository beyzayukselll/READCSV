#if !defined(MODULE_2_H)

#include "module_base.h"
#include "module_services.h"
#include "servo_master.h"
#include <deque>
#include <vector>

class Module_2 : public Module_Base
{
public:
	void initialize(Servo_Master_Base *servo_master) override;
	void get_inputs() override;
	void tick() override;
	void set_outputs() override;
	void deinitialize();

private:
	// TODO(batuhan): moving average filter..
	r64 filter(r64* buffer, u32* write_index, r64 val);
	void do_jog_out(Servo_Axis axis, r64 *buffer, u32 *index, Jog_Factor jog_factor);

private:
	union{
		struct {
			i32 x;
			i32 y;
			i32 z;
		};
		i32 data[3];
	} position_offsets;

	// current positions are in encoder increments
	// no offset is applied to them
	union{
		struct {
			i32 x;
			i32 y;
			i32 z;
		};
		i32 data[3];
	} current_positions;

	union{
		struct {
			i32 x;
			i32 y;
			i32 z;
		};
		i32 data[3];
	} current_velocities;

	// current positions as mm
	union{
		struct {
			r64 x;
			r64 y;
			r64 z;
 		};
		r64 data[3];
	} current_positions_mm;

	union{
		struct {
			r64 x;
			r64 y;
			r64 z;
 		};
		r64 data[3];
	} current_velocities_mmps;

public:
	Module_2_Inputs		inputs;
	Module_2_Outputs	outputs;

private:
	std::deque<Job>		m_CurrentJobQueue;

	Servo_Master_Base *m_ServoMaster = nullptr;
	std::vector<Servo_Axis> 	m_Axes;
#define FILTER_BUFFER_SIZE 1000
	r64 m_FilterBufferX[FILTER_BUFFER_SIZE];
	u32 m_FilterBufferXWriteIdx;
	r64 m_FilterBufferY[FILTER_BUFFER_SIZE];
	u32 m_FilterBufferYWriteIdx;
	r64 m_FilterBufferZ[FILTER_BUFFER_SIZE];
	u32 m_FilterBufferZWriteIdx;
};

#define MODULE_2_H
#endif