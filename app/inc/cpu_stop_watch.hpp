#ifndef CPU_STOP_WATCH_HPP
#define CPU_STOP_WATCH_HPP

#include "cpu_timing.h"

// @brief Замерение времени на процессоре (секундомер)
class cpu_stop_watch : public cpu_timing
{
public:
	//временной интервал между двумя вызовами update() в секундах
	float duration;

	cpu_stop_watch()
	{
		duration = 0.f;
	}

	/// @brief Обносить временной интервал между двумя вызовами update()
	void update(void)
	{
		update_delta_ticks();
		duration = delta_time.count();
		// duration = static_cast<float>(delta_time_ticks) / static_cast<float>(ticks_frequency.QuadPart);
	}
}; 

#endif // CPU_STOP_WATCH_HPP

