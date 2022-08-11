#if !defined(SERVO_MASTER_H)

#include "servo_master_base.h"
#include "ethercat.h"

enum Mode_Of_Operation
{
	OP_PP = 1,
	OP_CSP = 8,
	OP_CSV = 9,
};

// from master to slave (RxPDO)
#pragma pack(push, 1)
struct _1600_t
{
	uint16  control_word;
    int32   target_position;
    int32   velocity_offset;
    int8    mode_of_operation;
	uint8 	reserved_1;
};
#pragma pack(pop)

// from slave to master (TxPDO)
#pragma pack(push, 1)
struct _1A00_t
{
	uint16  status_word;
	int32   actual_position;
	int32   actual_velocity;
	int16   mode_of_operation_display;
};
#pragma pack(pop)

// could be singleton
class Servo_Master : public Servo_Master_Base
{
public:
	// returns number of slaves found
	virtual int discover_slaves(const char *eth_interface) override;

	virtual void set_state_pre_operation() override;
	virtual void set_state_safe_op() override;
	virtual void set_state_op() override;

	virtual int get_master_state() override;
	
	virtual char* get_error(Servo_Axis axis) override;

	virtual void set_mode_of_operation(Servo_Axis axis, i16 mode) override;
	virtual void set_control_word(Servo_Axis axis, i16 cw) override;
	virtual u16 get_status_word(Servo_Axis axis) override;
	virtual i16 get_mode_of_operation(Servo_Axis axis) override;
	virtual i32 get_actual_position(Servo_Axis axis) override;
	virtual void set_target_position(Servo_Axis axis, i32 position) override;
	virtual i32 get_actual_velocity(Servo_Axis axis) override;
	virtual void set_velocity_offset(Servo_Axis axis, i32 velocity) override;
	virtual void publish_pdo() override;
	virtual void receive_pdo() override;

	static Servo_Master* get_instance();

private:
	static struct _1600_t **outputs;
	static struct _1A00_t **inputs;

	static Servo_Master* instance;
	
private:
	static int slave_PO2SO_setup_hook(u16 slave);
	static char s_IOMap[4096];

private:
	Servo_Master();
	Servo_Master(const Servo_Master&) = delete;
	Servo_Master(const Servo_Master&&) = delete;
	Servo_Master& operator=(const Servo_Master&) = delete;
};

#define SERVO_MASTER_H
#endif