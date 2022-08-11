#include "CLI.h"

#include <unistd.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <errno.h>
#include <iostream>
#include <termio.h>
#include <deque>
#include "sim_functions.h"
#include "sim_instruction.h"
#include "module_base.h"
#include "module_1.h"
#include "module_2.h"

#include "servo_faker.h"
#include "servo_master.h"

CLI *cli;

#if FAKE_SERVO
Servo_Master_Base *servo_master = Servo_Faker::get_instance();
#else
Servo_Master_Base *servo_master = Servo_Master::get_instance();
#endif

typedef void(thread_work_t)(Module_Base *module);
struct Thread_Args
{
	unsigned long long update_us;
	Module_Base* module;
	Servo_Master_Base* servo_master;
};

static volatile int g_AbortRequest;
static std::mutex g_ExecuteMutex;
static std::condition_variable g_ExecuteCondition;

Thread_Args arg1;
Thread_Args arg2;

std::thread *t1 = nullptr;
std::thread *t2 = nullptr;

void* thread_work_wrapper(void* args)
{
	using clock = std::chrono::steady_clock;
	Thread_Args* t_arg = (Thread_Args*)args;
	auto chrono_us = std::chrono::microseconds(t_arg->update_us);

	{
		// "Start" barrier until all threads are ready.
		// TODO(batuhan): It's better to use a counting semaphore here.
		std::unique_lock<std::mutex> execute_lock(g_ExecuteMutex);
		g_ExecuteCondition.wait(execute_lock);
	}

	if(!g_AbortRequest)
		t_arg->module->initialize(t_arg->servo_master);

	while (true)
	{
		if (g_AbortRequest) break;

		auto begin = clock::now();
		if (t_arg->module)
		{
			t_arg->module->get_inputs();
			t_arg->module->tick();
			t_arg->module->set_outputs();
		}
		auto end = clock::now();

		auto time_passed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);

		// TODO(batuhan): This should be changed to a condition variable triggered by a scheduler/syncronizer.
		std::this_thread::sleep_for(chrono_us - time_passed_us);
	}

	return nullptr;
}

int main(int arg_count, const char** args)
{

	if(getuid() != 0)
	{
		std::cout << "This program must be run as root." << std::endl;
		return -1;
	}

	arg1 = {};
	arg1.update_us = 20000;
	arg1.module = new Module_1();
	arg1.servo_master = servo_master;

	arg2 = {};
	arg2.update_us = 1000;
	arg2.module = new Module_2();
	arg2.servo_master = servo_master;
	
	cli = CLI::get_cli();

	cli->on_open = []()
	{
		std::cout << "CLI opened." << std::endl;
	};

	cli->on_key_pressed = [](const int key)
	{
		switch (key)
		{
			case 's':
			{
				std::unique_lock<std::mutex> lock(g_ExecuteMutex);
				g_ExecuteCondition.notify_all();
			}
			break;

			case 'd':
			{
				((Module_1 *)(arg1.module))->start_cut();
			}
			break;

			case 'f':
			{
				((Module_1 *)(arg1.module))->stop_cut();
			}
			break;

			case 'p':
			{
				cli->log("%d", servo_master->get_master_state());
			}
			break;

			case 'e':
			{
				for( auto axis : ((Module_1 *)(arg1.module))->get_axes())
					cli->log(servo_master->get_error(axis));
			}
			break;

			case 'l':
			{
				((Module_1 *)(arg1.module))->load_test_trajectory();
			}
			break;
		}
	};

	cli->on_close = []()
	{
		g_AbortRequest = 1;
		g_ExecuteCondition.notify_all();

		((Module_2 *)(arg2.module))->deinitialize();

		if(t1->joinable())
		{
			t1->join();
		}
		delete t1;
		
		if(t2->joinable())
		{
			t2->join();
		}
		delete t2;

		std::cout << "CLI closed..." << std::endl;
		exit(0);
	};

	cli->enable_file_logging();
	cli->block_signals();
	cli->initMap();

	perm_line_t *pl = new perm_line_t;
	pl->generate_line = []() -> char* {
		char* line = new char[256];
		sprintf(line, "s - init | l - load trajectory | d - cut | f - stop | p - print master state | e - print error | <ESC> - safe exit");
		return line;
	};
	cli->add_perm_line(pl);

	auto found_slave_count = servo_master->discover_slaves(INTERFACE_NAME);
	cli->log("Found %d slaves.", found_slave_count);

	t1 = new std::thread(&thread_work_wrapper, &arg1);
	t2 = new std::thread(&thread_work_wrapper, &arg2);
	
	while (true)
	{
		cli->kb();
		cli->update();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	
	return 0;
}