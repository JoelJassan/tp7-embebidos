/**
 * @file reloj.h
 * @author Joel Jassan <joeljassan@hotmail.com>
 * @brief  Archivos de cabecera para reloj.c
 * @date 2023-06-10
 * 
 * @copyright Copyright (c) 2023. All rights reserved.
 * 
 */
/* --------------------------------------------------------------------------------------------- */ 



/*---  Includes  ------------------------------------------------------------------------------- */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

/* ---  Macros definitions  -------------------------------------------------------------------- */

// Puntero a la estructura de tipo clock_s
typedef struct clock_s * clock_t;

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Public Function Declaration  ------------------------------------------------------------ */

clock_t ClockCreate(int tics_per_second);

bool ClockGetTime(clock_t reloj, uint8_t * hora, int size);

bool ClockSetTime(clock_t reloj, const uint8_t * hora, int size);

/*---  End of File  ---------------------------------------------------------------------------- */






