#include <stdbool.h>
#include <stdint.h>


typedef struct clock_s * clock_t;

clock_t ClockCreate(int tics_per_second);

bool ClockGetTime(clock_t reloj, uint8_t * hora, int size);