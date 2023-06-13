/**
 * @file reloj.c
 * @author Joel Jassan <joeljassan@hotmail.com>
 * @brief  Funcionalidad de un reloj de 24 hs
 * @date 2023-06-10
 * 
 * @copyright Copyright (c) 2023. All rights reserved.
 * 
 */
/* --------------------------------------------------------------------------------------------- */ 



/* ---  Headers files inclusions   ------------------------------------------------------------- */

#include "reloj.h"

/* ---  Macros definitions  -------------------------------------------------------------------- */

struct clock_s {
    uint8_t hora_actual[6];
    bool valida;
};

/*---  Private Data Declaration  --------------------------------------------------------------- */

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Private Function Declaration  ----------------------------------------------------------- */

/*---  Public Function Declaration  ------------------------------------------------------------ */

/*---  Private Data Definition  ---------------------------------------------------------------- */

/*---  Public Data Definition  ----------------------------------------------------------------- */

/*---  Private Function Definition  ------------------------------------------------------------ */

/*---  Public Function Definition  ------------------------------------------------------------- */

/*---  Private Function Implementation  -------------------------------------------------------- */

/*---  Public Function Implementation  --------------------------------------------------------- */

clock_t ClockCreate(int tics_per_second){
    static  struct clock_s self [1];
    memset(self, 0, sizeof(self));

    return self;
}

bool ClockGetTime(clock_t reloj, uint8_t * hora, int size){
    memcpy(hora, reloj->hora_actual, size);

    return reloj->valida;
}

bool ClockSetTime(clock_t reloj, const uint8_t * hora, int size){
    memcpy(reloj->hora_actual, hora, size);
    reloj->valida = true;
    return reloj->valida;
}

void ClockAddTime(clock_t reloj, int size){
    
    if (reloj->hora_actual[size - 1] < 10)
        reloj->hora_actual[size - 1] ++;    // sumo unidad segundos

    if (reloj->hora_actual[size - 1] == 10) {
        reloj->hora_actual[size - 1] = 0;
        reloj->hora_actual[size - 2] ++;    // sumo decena segundos
    }

    if (reloj->hora_actual[size - 2] == 6) {
        reloj->hora_actual[size - 2] = 0;
        reloj->hora_actual[size - 3] ++;    // sumo unidad minutos
    }

    if (reloj->hora_actual[size - 3] == 10) {
        reloj->hora_actual[size - 3] = 0;
        reloj->hora_actual[size - 4] ++;    // sumo decena minutos
    }

    if (reloj->hora_actual[size - 4] == 6) {
        reloj->hora_actual[size - 4] = 0;
        reloj->hora_actual[size - 5] ++;    // sumo unidad horas
    }

    if ((reloj->hora_actual[size - 6]) != 2) 
        if (reloj->hora_actual[size - 5] == 10) {
            reloj->hora_actual[size - 5] = 0;
            reloj->hora_actual[size - 6] ++;    // sumo decena horas
        }
    if ((reloj->hora_actual[size - 6]) == 2) 
        if (reloj->hora_actual[size - 5] == 4) {
            reloj->hora_actual[size - 5] = 0;
            reloj->hora_actual[size - 6] = 0;
        }
        
}

/*---  End of File  ---------------------------------------------------------------------------- */