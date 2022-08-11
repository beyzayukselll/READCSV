#include "CLI.h"

#include "servo_faker.h"
#include "sim_config.h"

#include <cstdio>

extern CLI *cli;

struct fake_servo_data_t* Servo_Faker::fake_servo_data;

Servo_Faker *Servo_Faker::instance = nullptr;

Servo_Faker::Servo_Faker()
{
}

int Servo_Faker::discover_slaves(const char *eth_interface)
{
    fake_servo_data = new fake_servo_data_t[SERVO_COUNT];

    for(int i = 0; i < SERVO_COUNT; ++i)
    {        
        perm_line_t *pl = new perm_line_t;
        pl->generate_line = [i]() -> char* {
            char *line = new char[1024];
            sprintf(line, "WRITE: control_word: 0x%x target_pos: %d, velocity_offset: %d, mode_of_operation: 0x%x",
                fake_servo_data[i].pdo_output.control_word,
                fake_servo_data[i].pdo_output.target_position,
                fake_servo_data[i].pdo_output.velocity_offset,
                fake_servo_data[i].pdo_output.mode_of_operation);
            return line;
        };
        cli->add_perm_line(pl);

        pl = new perm_line_t;
        pl->generate_line = [i]() -> char* {
            char *line = new char[1024];
            sprintf(line, "READ : status_word: 0x%x act_pos: %d, act_vel: %d, mode_of_operation_display: 0x%x",
                fake_servo_data[i].pdo_input.status_word,
                fake_servo_data[i].pdo_input.actual_position,
                fake_servo_data[i].pdo_input.actual_velocity,
                fake_servo_data[i].pdo_input.mode_of_operation_display);
            return line;
        };
        cli->add_perm_line(pl);
    }

    return SERVO_COUNT;
}

void Servo_Faker::set_state_pre_operation()
{
    for(int i = 0; i < SERVO_COUNT; ++i)
    {
        fake_servo_data[i].slave.state = EC_STATE_PRE_OP;
    }
}

void Servo_Faker::set_state_safe_op()
{
    for(int i = 0; i < SERVO_COUNT; ++i)
    {
        fake_servo_data[i].slave.state = EC_STATE_SAFE_OP;
    }
}

void Servo_Faker::set_state_op()
{
    for(int i = 0; i < SERVO_COUNT; ++i)
    {
        fake_servo_data[i].slave.state = EC_STATE_OPERATIONAL;
    }
}

int Servo_Faker::get_master_state()
{
    // any of it
    return fake_servo_data[0].slave.state;
}

char* Servo_Faker::get_error(Servo_Axis axis)
{
    char *error = new char[9];
    sprintf(error, "No error");
    return error;
}

void Servo_Faker::set_mode_of_operation(Servo_Axis axis, i16 mode)
{
    fake_servo_data[axis].pdo_output.mode_of_operation = mode;
    fake_servo_data[axis].pdo_input.mode_of_operation_display = mode;
}

void Servo_Faker::set_control_word(Servo_Axis axis, i16 cw)
{
    fake_servo_data[axis].pdo_output.control_word = cw;
    fake_servo_data[axis].pdo_input.status_word = cw;
}

u16 Servo_Faker::get_status_word(Servo_Axis axis)
{
    return fake_servo_data[axis].pdo_input.status_word;
}

i16 Servo_Faker::get_mode_of_operation(Servo_Axis axis)
{
    return fake_servo_data[axis].pdo_input.mode_of_operation_display;
}

i32 Servo_Faker::get_actual_position(Servo_Axis axis)
{
    return fake_servo_data[axis].pdo_input.actual_position;
}

void Servo_Faker::set_target_position(Servo_Axis axis, i32 position)
{
    fake_servo_data[axis].pdo_output.target_position = position;
    fake_servo_data[axis].pdo_input.actual_position = position;
}

i32 Servo_Faker::get_actual_velocity(Servo_Axis axis)
{
    return fake_servo_data[axis].pdo_input.actual_velocity;
}

void Servo_Faker::set_velocity_offset(Servo_Axis axis, i32 velocity)
{
    fake_servo_data[axis].pdo_output.velocity_offset = velocity;
    fake_servo_data[axis].pdo_input.actual_velocity = velocity;
}

void Servo_Faker::publish_pdo()
{

}

void Servo_Faker::receive_pdo()
{
    
}

Servo_Faker* Servo_Faker::get_instance()
{
    if (instance == nullptr)
    {
        instance = new Servo_Faker();
    }
    return instance;
}