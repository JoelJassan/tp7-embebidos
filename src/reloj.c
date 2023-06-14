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
    uint32_t ticks_per_sec;
    uint32_t current_tick;
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
    self->ticks_per_sec = tics_per_second;

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

void ClockRefresh(clock_t reloj, int size){
    reloj->current_tick++;

    // sumo unidad segundos
    if (reloj->current_tick >= reloj->ticks_per_sec) {
        reloj->current_tick = 0;
        reloj->hora_actual[size - 1] ++;
    }   

    // sumo decena segundos
    if (reloj->hora_actual[size - 1] >= 10) {
        reloj->hora_actual[size - 1] = 0;
        reloj->hora_actual[size - 2] ++;
    }

    // sumo unidad minutos
    if (reloj->hora_actual[size - 2] >= 6) {
        reloj->hora_actual[size - 2] = 0;
        reloj->hora_actual[size - 3] ++;
    }

    // sumo decena minutos
    if (reloj->hora_actual[size - 3] >= 10) {
        reloj->hora_actual[size - 3] = 0;
        reloj->hora_actual[size - 4] ++;
    }

    // sumo unidad horas
    if (reloj->hora_actual[size - 4] >= 6) {
        reloj->hora_actual[size - 4] = 0;
        reloj->hora_actual[size - 5] ++;
    }

    // sumo decena horas
    if ((reloj->hora_actual[size - 6]) != 2) 
        if (reloj->hora_actual[size - 5] == 10) {
            reloj->hora_actual[size - 5] = 0;
            reloj->hora_actual[size - 6] ++;
        }
    if ((reloj->hora_actual[size - 6]) >= 2) 
        if (reloj->hora_actual[size - 5] == 4) {
            reloj->hora_actual[size - 5] = 0;
            reloj->hora_actual[size - 6] = 0;
        }
        
} //No sabria como hacerlo solo para HH:MM



clock_t AlarmCreate(void){
    return ClockCreate(0);
}

bool AlarmGetTime(clock_t alarma, uint8_t * alarm_time, int size){
    return ClockGetTime(alarma, alarm_time, size);
}

bool AlarmSetTime(clock_t alarma, const uint8_t * alarm_time, int size){
    return ClockSetTime(alarma, alarm_time, size);
}

/*---  End of File  ---------------------------------------------------------------------------- */