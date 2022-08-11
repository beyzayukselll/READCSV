#include "servo_master.h"

#include "sim_config.h"
#include <cstdio>

#include "CLI.h"
extern CLI *cli;

char Servo_Master::s_IOMap[4096]; 

struct _1600_t** Servo_Master::outputs;
struct _1A00_t** Servo_Master::inputs;

Servo_Master* Servo_Master::instance = nullptr;

Servo_Master::Servo_Master()
{
}

int Servo_Master::discover_slaves(const char* eth_interface)
{
	if (ec_init(eth_interface))
	{
		if (ec_config_init(FALSE) > 0)
		{
			set_state_pre_operation();

			// skip pre-op state check
			
			// generate PDO map
			outputs = new _1600_t*[ec_slavecount];
			inputs = new _1A00_t*[ec_slavecount];

			// connect hooks
			for (int i = 1; i <= ec_slavecount; ++i)
			{
				ec_slave[i].PO2SOconfig = &Servo_Master::slave_PO2SO_setup_hook;
			}

			// map PDO group
			// ecx_context.manualstatechange = 0;
			// manual state change is `0` by default
			// so its not necessary to set it to safeop manually
			ec_config_map_group(&s_IOMap, 0);

			// set pointers to PDO
			// indices are axis numbers
			for (int i = 1; i <= ec_slavecount; ++i)
			{
				outputs[i - 1] = (struct _1600_t*)ec_slave[i].outputs;
				inputs[i - 1] = (struct _1A00_t*)ec_slave[i].inputs;

				// workaround segmentation fault, not sure of it
				if(outputs[i - 1] == nullptr) (outputs[i - 1] = (_1600_t*)calloc(1, sizeof(_1600_t)));
				if(inputs[i - 1] == nullptr) (inputs[i - 1] = (_1A00_t*)calloc(1, sizeof(_1A00_t)));

				perm_line_t *pl = new perm_line_t;
				pl->generate_line = [i]() -> char* {
					char *line = new char[1024];
					sprintf(line, "WRITE: control_word: 0x%x target_pos: %d, velocity_offset: %d, mode_of_operation: 0x%x",
						outputs[i - 1]->control_word,
						outputs[i - 1]->target_position,
						outputs[i - 1]->velocity_offset,
						outputs[i - 1]->mode_of_operation);
					return line;
				};
				cli->add_perm_line(pl);

				pl = new perm_line_t;
				pl->generate_line = [i]() -> char* {
					char *line = new char[1024];
					sprintf(line, "READ : status_word: 0x%x act_pos: %d, act_vel: %d, mode_of_operation_display: 0x%x",
						inputs[i - 1]->status_word,
						inputs[i - 1]->actual_position,
						inputs[i - 1]->actual_velocity,
		   				inputs[i - 1]->mode_of_operation_display);
					return line;
				};
				cli->add_perm_line(pl);

			}
		}
	}

	// return the number of configured slaves
	return ec_slavecount;
}

// TODO: test it
void Servo_Master::set_state_pre_operation()
{
	ec_slave[0].state = EC_STATE_PRE_OP;
	ec_writestate(0);

	ec_statecheck(0, EC_STATE_PRE_OP, EC_TIMEOUTSTATE );
	ec_readstate();
	
	if(ec_slave[0].state == EC_STATE_PRE_OP)
	{
		cli->log("All slaves set to PREOP state");
		for(int slave_index = 1; slave_index <= ec_slavecount; ++slave_index)
		{
			cli->log("slave %d state %x (%d (PREOP) expected )",
				slave_index, ec_slave[slave_index].state, EC_STATE_PRE_OP);
		}
	}
	else
	{
		cli->log("Error to set PREOP state");
		for(int slave_index = 1; slave_index <= ec_slavecount; ++slave_index)
		{
			cli->log("slave %d state %x (%d (PREOP) expected ) status = (%x) %s",
				slave_index, ec_slave[slave_index].state, EC_STATE_PRE_OP,
				ec_slave[slave_index].ALstatuscode, ec_ALstatuscode2string(ec_slave[slave_index].ALstatuscode));
		}
	}
}

// TODO: test it
void Servo_Master::set_state_safe_op()
{
	ec_slave[0].state = EC_STATE_SAFE_OP;
	ec_writestate(0);

	ec_statecheck(0, EC_STATE_SAFE_OP, EC_TIMEOUTSTATE );
	ec_readstate();
	if(ec_slave[0].state == EC_STATE_SAFE_OP)
	{
		cli->log("All slaves set to SAFEOP state");
		for(int slave_index = 1; slave_index <= ec_slavecount; ++slave_index)
		{
			cli->log("slave %d state %x (%d (SAFEOP) expected )",
				slave_index, ec_slave[slave_index].state, EC_STATE_SAFE_OP);
		}
	}
	else
	{
		cli->log("Error to set SAFEOP state");
		for(int slave_index = 1; slave_index <= ec_slavecount; ++slave_index)
		{
			cli->log("slave %d state %x (%d (SAFEOP) expected ) status = (%x) %s",
				slave_index, ec_slave[slave_index].state, EC_STATE_SAFE_OP,
				ec_slave[slave_index].ALstatuscode, ec_ALstatuscode2string(ec_slave[slave_index].ALstatuscode));
		}
	}

	ec_receive_processdata(EC_TIMEOUTRET);
	ec_send_processdata();
}

void Servo_Master::set_state_op()
{
	ec_slave[0].state = EC_STATE_OPERATIONAL;
	ec_receive_processdata(EC_TIMEOUTRET);
	ec_send_processdata();
	/* request OP state for all slaves */
	ec_writestate(0);

	ec_statecheck(0, EC_STATE_OPERATIONAL, EC_TIMEOUTSTATE );
	ec_readstate();

	if(ec_slave[0].state == EC_STATE_OPERATIONAL)
	{
		cli->log("All slaves set to OPERATIONAL state");
		for(int slave_index = 1; slave_index <= ec_slavecount; ++slave_index)
		{
			cli->log( "slave %d state %d (%d (OPERATIONAL) expected )",
				slave_index, ec_slave[slave_index].state, EC_STATE_OPERATIONAL);
		}
	}
	else
	{
		cli->log("Error to set OPERATIONAL state");
		for(int slave_index = 1; slave_index <= ec_slavecount; ++slave_index)
		{
			cli->log( "slave %d state %d (%d (OPERATIONAL) expected ) status = (%x) %s",
				slave_index, ec_slave[slave_index].state, EC_STATE_OPERATIONAL,
				ec_slave[slave_index].ALstatuscode, ec_ALstatuscode2string(ec_slave[slave_index].ALstatuscode));
		}
	}
}

int Servo_Master::get_master_state()
{
	ec_readstate();
	return ec_slave[0].state;
}

// TODO
char* Servo_Master::get_error(Servo_Axis axis)
{
	return ec_ALstatuscode2string(ec_slave[axis + 1].ALstatuscode);
}

void Servo_Master::set_mode_of_operation(Servo_Axis axis, i16 mode)
{
	outputs[axis]->mode_of_operation = mode;
}

void Servo_Master::set_control_word(Servo_Axis axis, i16 cw)
{
	outputs[axis]->control_word = cw;
}

u16 Servo_Master::get_status_word(Servo_Axis axis)
{
	return inputs[axis]->status_word;
}

i16 Servo_Master::get_mode_of_operation(Servo_Axis axis)
{
	return inputs[axis]->mode_of_operation_display;
}

int Servo_Master::slave_PO2SO_setup_hook(u16 slave)
{
	cli->log("slave %d setup hook", slave);

	// Select RX pdo
	u8  u8val = 0;
	i8 i8val = 0;
	u16 u16val = 0;
	u32 u32val = 0;
	int ret = 0;


#pragma region ENCODER_CONF

	u32val = TODO_CFG_ENCODER_RESOLUTION;
	ret = ec_SDOwrite(slave, 0x608F, 0x01, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x608F, 0x01, u32val, ret);	
	
	u32val = TODO_CFG_GEAR_RATIO; // GEAR RATIO
	ret = ec_SDOwrite(slave, 0x6091, 0x01, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x6091, 0x01, u32val, ret);

	u32val = TODO_CFG_FEED_CONSTANT; // FEED CONSTANT
	ret = ec_SDOwrite(slave, 0x6092, 0x01, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x6092, 0x01, u32val, ret);

	u32val = 0;
	int len = 4;
	ret = ec_SDOread(slave, 0x6093, 0x01, FALSE, &len, &u32val, EC_TIMEOUTRXM);
	cli->log("[READ] addr: 0x%x, subindex: 0x%x, data: %d, ret: 0x%x", 0x6093, 0x01, u32val, ret);

	u32val = 0;
	len = 4;
	ret = ec_SDOread(slave, 0x6093, 0x02, FALSE, &len, &u32val, EC_TIMEOUTRXM);
	cli->log("[READ] addr: 0x%x, subindex: 0x%x, data: %d, ret: 0x%x", 0x6093, 0x02, u32val, ret);

	u32val = TODO_CFG_PROFILE_VELOCITY; // PROFILE VELOCITY
	ret = ec_SDOwrite(slave, 0x6081, 0x00, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x6081, 0x00, u32val, ret);

	// INTERPOLATION TIME PERIOD
	u8val = TODO_CFG_INTERP_TIME_PERIOD;
	ret = ec_SDOwrite(slave, 0x60c2, 0x01, FALSE, sizeof(u8), &u8val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: %d, ret: 0x%x", 0x60c2, 0x01, u8val, ret);

	u8val = 0;
	len = 1;
	ret = ec_SDOread(slave, 0x60c2, 0x01, FALSE, &len, &u8val, EC_TIMEOUTRXM);
	cli->log("[READ] addr: 0x%x, subindex: 0x%x, data: %d, ret: 0x%x", 0x60c2, 0x01, u8val, ret);
	
	// INTERPOLATION TIME PERIOD INDEX
	i8val = TODO_CFG_INTERP_TIME_PERIOD_INDEX;
	ret = ec_SDOwrite(slave, 0x60c2, 0x02, FALSE, sizeof(i8), &i8val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: %d, ret: 0x%x", 0x60c2, 0x02, i8val, ret);

	i8val = 0;
	len = 1;
	ret = ec_SDOread(slave, 0x60c2, 0x02, FALSE, &len, &i8val, EC_TIMEOUTRXM);
	cli->log("[READ] addr: 0x%x, subindex: 0x%x, data: %d, ret: 0x%x", 0x60c2, 0x02, i8val, ret);


#pragma endregion

#pragma region PDO_MAPPING
	// DEACTIVATE RX PDO
	u8val = 0x00;
	ret = ec_SDOwrite(slave, 0x1C12, 0x00, FALSE, sizeof(u8), &u8val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1C12, 0x00, u8val, ret);

	// DEACTIVATE TX PDO
	u8val = 0x00;
	ret = ec_SDOwrite(slave, 0x1C13, 0x00, FALSE, sizeof(u8), &u8val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1C13, 0x00, u8val, ret);

	// CLEAR RX PDO MAPPING
	u8val = 0x00;
	ret = ec_SDOwrite(slave, 0x1600, 0x00, FALSE, sizeof(u8), &u8val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1600, 0x00, u8val, ret);

	// RX SELECT CONTROL WORD
	u32val = 0x60400010;
	ret = ec_SDOwrite(slave, 0x1600, 0x01, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1600, 0x01, u32val, ret);

	// RX SELECT TARGET POSITION
	u32val = 0x607A0020;
	ret = ec_SDOwrite(slave, 0x1600, 0x02, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1600, 0x02, u32val, ret);

	// RX SELECT TARGET VELOCITY
	// u32val = 0x60FF0020;
	// ret = ec_SDOwrite(slave, 0x1600, 0x03, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	// cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1600, 0x03, u32val, ret);

	// RX SELECT VELOCITY FEED FORWARD (INSTEAD OF TARGET VELOCITY FOR NOW)
	u32val = 0x60B10020;
	ret = ec_SDOwrite(slave, 0x1600, 0x03, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1600, 0x03, u32val, ret);

	// RX SELECT MODE OF OPERATION
	u32val = 0x60600008;
	ret = ec_SDOwrite(slave, 0x1600, 0x04, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1600, 0x04, u32val, ret);

	// RX PADDING (REQUIRED)
	u32val = 0x00000008;
	ret = ec_SDOwrite(slave, 0x1600, 0x05, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1600, 0x05, u32val, ret);

	// ! IT FAILS IF I ADD MORE FIELD TO THE MAPPING
	// u32val = 0x60B10020;
	// ret = ec_SDOwrite(slave, 0x1600, 0x06, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	// cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1600, 0x06, u32val, ret);

	// RX SET COUNT
	u8val = 0x05;
	ret = ec_SDOwrite(slave, 0x1600, 0x00, FALSE, sizeof(u8), &u8val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1600, 0x00, u8val, ret);

	// CLEAR TX PDO MAPPING
	u8val = 0x00;
	ret = ec_SDOwrite(slave, 0x1A00, 0x00, FALSE, sizeof(u8), &u8val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1A00, 0x00, u8val, ret);

	// TX SELECT STATUS WORD
	u32val = 0x60410010;
	ret = ec_SDOwrite(slave, 0x1A00, 0x01, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1A00, 0x01, u32val, ret);

	// TX SELECT ACTUAL POSITION
	u32val = 0x60640020;
	ret = ec_SDOwrite(slave, 0x1A00, 0x02, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1A00, 0x02, u32val, ret);

	// TX SELECT ACTUAL VELOCITY
	u32val = 0x606C0020;
	ret = ec_SDOwrite(slave, 0x1A00, 0x03, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1A00, 0x03, u32val, ret);

	// TX SELECT MODE OF OPERATION DISPLAY
	u32val = 0x60610008;
	ret = ec_SDOwrite(slave, 0x1A00, 0x04, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1A00, 0x04, u32val, ret);

	// TX PADDING (REQUIRED)
	u32val = 0x00000008;
	ret = ec_SDOwrite(slave, 0x1A00, 0x05, FALSE, sizeof(u32), &u32val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1A00, 0x05, u32val, ret);

	// TX SET COUNT
	u8val = 0x05;
	ret = ec_SDOwrite(slave, 0x1A00, 0x00, FALSE, sizeof(u8), &u8val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1A00, 0x00, u8val, ret);

	// SELECT RX PDO
	u16val = 0x1600;
	ret = ec_SDOwrite(slave, 0x1C12, 0x01, FALSE, sizeof(u16), &u16val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1C12, 0x01, u16val, ret);

	// SELECT TX PDO
	u16val = 0x1A00;
	ret = ec_SDOwrite(slave, 0x1C13, 0x01, FALSE, sizeof(u16), &u16val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1C13, 0x01, u16val, ret);

	// ACTIVATE RX PDO
	u8val = 0x01;
	ret = ec_SDOwrite(slave, 0x1C12, 0x00, FALSE, sizeof(u8), &u8val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1C12, 0x00, u8val, ret);

	// ACTIVATE TX PDO
	u8val = 0x01;
	ret = ec_SDOwrite(slave, 0x1C13, 0x00, FALSE, sizeof(u8), &u8val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x1C13, 0x00, u8val, ret);
#pragma endregion

#pragma region MODE_OF_OPERATION
	u8val = 0x01;
	ret = ec_SDOwrite(slave, 0x6060, 0x00, TRUE, sizeof(u8), &u8val, EC_TIMEOUTRXM);
	cli->log("[WRITE] addr: 0x%x, subindex: 0x%x, data: 0x%x, ret: 0x%x", 0x6060, 0x00, u8val, ret);
#pragma endregion

	cli->log("slave %d setup hook done", slave);

	return 0;
}

i32 Servo_Master::get_actual_position(Servo_Axis axis)
{
	return inputs[axis]->actual_position;
}

void Servo_Master::set_target_position(Servo_Axis axis, i32 position)
{
	outputs[axis]->target_position = position;
}

i32 Servo_Master::get_actual_velocity(Servo_Axis axis)
{
	return inputs[axis]->actual_velocity;
}

void Servo_Master::set_velocity_offset(Servo_Axis axis, i32 velocity)
{
	outputs[axis]->velocity_offset = velocity;
}

void Servo_Master::publish_pdo()
{
	ec_send_processdata();
}

void Servo_Master::receive_pdo()
{
	ec_receive_processdata(EC_TIMEOUT);
}

Servo_Master* Servo_Master::get_instance()
{
	if (instance == NULL)
	{
		instance = new Servo_Master();
	}
	return instance;
}