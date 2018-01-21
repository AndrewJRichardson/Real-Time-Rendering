#ifndef DEBUG_TOOLS_H
#define DEBUG_TOOLS_H

#include "Exports.h"

#include <iostream>
#include <chrono>
#include <string>

class DebugTools
{
private:
	std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<double>> starttime;
	std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::duration<double>> endtime;


public:
	REALTIME_API void StartTimeMeasure();
	REALTIME_API void EndTimeMeasure(std::string name);
	REALTIME_API DebugTools();
	REALTIME_API ~DebugTools();
};

#endif // !DEBUG_TOOLS_H



