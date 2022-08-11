#if !defined(MODULE_BASE_H)

#include "servo_master_base.h"

class Module_Base
{
public:
	virtual void initialize(Servo_Master_Base *) = 0;
	virtual void get_inputs() = 0;
	virtual void tick() = 0;
	virtual void set_outputs() = 0;
};

#define MODULE_BASE_H
#endif