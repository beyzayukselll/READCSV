#ifndef SERVO_MASTER_BASE_H
#define SERVO_MASTER_BASE_H

#include "sim_common.h"

enum Servo_Axis
{
	AXIS_X = 0,
	AXIS_Y = 1,
	AXIS_Z = 2,
	NB_AXES
};

class Servo_Master_Base
{
public:
    virtual int discover_slaves(const char *eth_interface) = 0;

    virtual void set_state_pre_operation() = 0;
	virtual void set_state_safe_op() = 0;
	virtual void set_state_op() = 0;

	virtual int get_master_state() = 0;

	virtual char* get_error(Servo_Axis axis) = 0;

	virtual u16 get_status_word(Servo_Axis axis) = 0;
	virtual void set_control_word(Servo_Axis axis, i16 cw) = 0;
	
    virtual i16 get_mode_of_operation(Servo_Axis axis) = 0;
	virtual void set_mode_of_operation(Servo_Axis axis, i16 mode) = 0;
	
    virtual i32 get_actual_position(Servo_Axis axis) = 0;
	virtual void set_target_position(Servo_Axis axis, i32 position) = 0;
	
    virtual i32 get_actual_velocity(Servo_Axis axis) = 0;
	virtual void set_velocity_offset(Servo_Axis axis, i32 velocity) = 0;
	
    virtual void receive_pdo() = 0;
	virtual void publish_pdo() = 0;

public:
    Servo_Master_Base() = default;

private:
    Servo_Master_Base(const Servo_Master_Base&) = delete;
    Servo_Master_Base(const Servo_Master_Base&&) = delete;
    Servo_Master_Base& operator=(const Servo_Master_Base&) = delete;
};
#endif // SERVO_MASTER_BASE_H