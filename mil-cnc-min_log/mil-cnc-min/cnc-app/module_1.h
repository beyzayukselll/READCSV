#if !defined(MODULE_1_H)

#include "module_base.h"
#include "module_services.h"

#include "servo_master.h"
#include <vector>

class Module_1 : public Module_Base
{
public:
	void initialize(Servo_Master_Base *servo_master) override;
	void get_inputs() override;
	void tick() override;
	void set_outputs() override;

private:
	// if returns true, all axes have the requested mode
	bool set_all_axes_opmode(Mode_Of_Operation requested_mode);
	void checkorders();

public:
	Module_1_Inputs				inputs;
	Module_1_Outputs			outputs;

private:
	CNC_State					m_State;
	CNC_State					m_NextState;
	std::deque<Job>				m_JobQueue;
	std::vector<Instruction>	m_Instructions;

	Servo_Master_Base *m_ServoMaster = nullptr;

	std::vector<Servo_Axis>		m_Axes;
	int							m_InterpolationIndex;
	int							m_CurrentInstructionIndex;
	bool						m_IsContouringEnabled = true;
	bool						m_IsMicroSplineEnabled = true;

	std::fstream *file = nullptr;

public:
	void start_cut();
	void stop_cut();
	
	std::vector<Servo_Axis>& get_axes();

	void load_test_trajectory();
};

#define MODULE_1_H
#endif