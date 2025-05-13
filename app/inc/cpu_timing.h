#ifndef CPU_TIMING_H
#define CPU_TIMING_H

#define WIN32_LEAN_AND_MEAN 1 // Урезанный windows.h
#include <windows.h>
#include <chrono>
#include "time_definers.h"

/// @brief Основа процессорного замера времени
class cpu_timing
{
private:
	// LARGE_INTEGER start_time_ticks; // начальное время в тиках
	// LARGE_INTEGER end_time_ticks;   // конечное время в тиках
protected:
	// static LARGE_INTEGER ticks_frequency; // количество тиков процессора в секуду
	// LONGLONG delta_time_ticks; // Разница временных тиков

	// std::chrono::time_point<std::chrono::high_resolution_clock> last_clock;
	// std::chrono::time_point<std::chrono::high_resolution_clock> cur_clock;
	// std::chrono::duration<float> delta_time;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;
	std::chrono::duration<float> delta_time;


	/// @brief Отсечь новую временную разницу в тиках
	void update_delta_ticks(void);
public:
	/// @brief Конструктор
	cpu_timing();
};

#endif // CPU_TIMING_H