
#ifndef SERVO_FAKER_H
#define SERVO_FAKER_H

#include "servo_master.h"

struct fake_servo_data_t
{
    _1600_t pdo_output = {0};
    _1A00_t pdo_input = {0};
    ec_slavet slave;
};

class Servo_Faker : public Servo_Master_Base
{
    private:
        Servo_Faker();
        Servo_Faker(const Servo_Faker&) = delete;
        Servo_Faker& operator=(const Servo_Faker&) = delete;

    private:
        static struct fake_servo_data_t* fake_servo_data;

        static Servo_Faker *instance;
    
    public:
        // override all methods
        virtual int discover_slaves(const char *eth_interface) override;
        
        virtual void set_state_pre_operation() override;
        virtual void set_state_safe_op() override;
        virtual void set_state_op() override;
        
        virtual int get_master_state() override;

        virtual char* get_error(Servo_Axis axis) override;
        
        virtual void set_control_word(Servo_Axis axis, i16 cw) override;
        virtual u16 get_status_word(Servo_Axis axis) override;
        
        virtual i16 get_mode_of_operation(Servo_Axis axis) override;
        virtual void set_mode_of_operation(Servo_Axis axis, i16 mode) override;
        
        virtual i32 get_actual_position(Servo_Axis axis) override;
        virtual void set_target_position(Servo_Axis axis, i32 position) override;
        
        virtual i32 get_actual_velocity(Servo_Axis axis) override;
        virtual void set_velocity_offset(Servo_Axis axis, i32 velocity) override;
        
        virtual void receive_pdo() override;
        virtual void publish_pdo() override;

        static Servo_Faker *get_instance();
};

#endif