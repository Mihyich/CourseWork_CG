#include "cpu_timing.h"

// LARGE_INTEGER cpu_timing::ticks_frequency = { 0 };

void cpu_timing::update_delta_ticks(void)
{	
	// QueryPerformanceCounter(&end_time_ticks);
	// delta_time_ticks = end_time_ticks.QuadPart - start_time_ticks.QuadPart;
	// start_time_ticks = end_time_ticks;

	/*cur_clock = std::chrono::high_resolution_clock::now();
	delta_time = cur_clock - last_clock;
	last_clock = cur_clock;*/

	end = std::chrono::system_clock::now();
	// delta_time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	delta_time = end - start;
	start = end;
}

cpu_timing::cpu_timing()
{
	/*QueryPerformanceCounter(&start_time_ticks);
	end_time_ticks = start_time_ticks;

	if (!ticks_frequency.QuadPart)
		QueryPerformanceFrequency(&ticks_frequency);

	delta_time_ticks = 0;*/

	/*cur_clock = std::chrono::high_resolution_clock::now();
	delta_time = cur_clock - last_clock;
	last_clock = cur_clock;*/

	start = std::chrono::system_clock::now();
	start = end;
	delta_time = std::chrono::duration<float>(0.f);
}