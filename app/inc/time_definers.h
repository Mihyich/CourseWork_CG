#ifndef TIME_DEFINERS_H
#define TIME_DEFINERS_H

#define TIME_FOR_24_UPD_PER_SEC  0.041666f
#define TIME_FOR_30_UPD_PER_SEC  0.033333f
#define TIME_FOR_60_UPD_PER_SEC  0.016666f
#define TIME_FOR_90_UPD_PER_SEC  0.011111f
#define TIME_FOR_144_UPD_PER_SEC 0.006944f
#define TIME_FOR_200_UPD_PER_SEC 0.005000f

#define TIME_PER_UPDATE TIME_FOR_30_UPD_PER_SEC
#define TIME_PER_FRAME  TIME_FOR_24_UPD_PER_SEC

#define MIN_PER_HOUR 60.f // Количество минут в часе
#define SEC_PER_MIN  60.f // Количество секунд в минуте

#define MILLISEC_PER_SEC 1e+3f // Количество миллисекунд в секунде
#define MICROSEC_PER_SEC 1e+6f // Количество микросекунд в секунде
#define NANOSEC_PER_SEC  1e+9f // Количество наносекунд в секунде

#define MICROSEC_PER_MILLISEC 1e+3f // Количество микросекунд в миллисекунде
#define NANOSEC_PER_MILLISEC  1e+6f // Количество наносекунд в миллисекунде

#define NANOSEC_PER_MICROSEC  1e+3f // Количество наносекунд в микросекунде

// конвертация в секунды =-=-=-=-=-=

// Перевести миллисекунды в секунды
#define MILLISEC_TO_SEC(millisec) (millisec / MILLISEC_PER_SEC)
// Перевести микросекунды в секунды
#define MICROSEC_TO_SEC(microsec) (microsec / MICROSEC_PER_SEC)
// Перевести наносекунды в секунды
#define NANOSEC_TO_SEC(nanosec) (nanosec / NANOSEC_PER_SEC)

// Конвертация в миллисекунды =-=-=-=-=-=

// Перевести микросекунды в миллисекунды
#define MICROSEC_TO_MILLISEC(microsec) (microsec / MICROSEC_PER_MILLISEC)
// Перевести наносекунды в миллисекунды
#define NANOSEC_TO_MILLISEC(nanosec) (nanosec / NANOSEC_PER_MILLISEC)

// Конвертация в микросекунды =-=-=-=-=-=

// Перевести наносекунды в микросекунды
#define NANOSEC_TO_MICROSEC(nanosec) (nanosec / NANOSEC_PER_MICROSEC)

#endif // !TIME_DEFINERS_H

