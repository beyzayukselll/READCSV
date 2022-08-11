#include "global_data_area.h"

Module_1_Inputs     Data_Area::g_Module_1_Inputs;
Module_1_Outputs	Data_Area::g_Module_1_Outputs;
Module_2_Inputs     Data_Area::g_Module_2_Inputs;
Module_2_Outputs	Data_Area::g_Module_2_Outputs;
Module_3_Inputs	    Data_Area::g_Module_3_Inputs;
Module_3_Outputs	Data_Area::g_Module_3_Outputs;

std::mutex			Data_Area::g_TrajectoryBufferMutex;
std::deque<Job>		Data_Area::g_TrajectoryBuffer;
