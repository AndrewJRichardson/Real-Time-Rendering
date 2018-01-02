#include "DebugTools.h"


void DebugTools::StartTimeMeasure() {
	starttime = std::chrono::high_resolution_clock::now();
}
void DebugTools::EndTimeMeasure(std::string name) {
	endtime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> elapsed = endtime - starttime;
	std::cout << name << ": " << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count() << std::endl;
}

DebugTools::DebugTools()
{
}


DebugTools::~DebugTools()
{
}
