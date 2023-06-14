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

#define POSICION_UNI_SS POSICION_DEC_SS + 1
#define POSICION_DEC_SS POSICION_UNI_MM + 1
#define POSICION_UNI_MM POSICION_DEC_MM + 1
#define POSICION_DEC_MM POSICION_UNI_HH + 1
#define POSICION_UNI_HH POSICION_DEC_HH + 1
#define POSICION_DEC_HH 0

#define LIMITE_DECENA 6
#define LIMITE_UNIDAD 10

struct alarm_s {
    uint8_t hora_alarma[ALARM_SIZE];
    bool active;
};

struct clock_s {
    uint8_t hora_actual[CLOCK_SIZE];
    uint32_t ticks_per_sec;
    uint32_t current_tick;
    bool valida;

    alarm_t alarma;
};

/*---  Private Data Declaration  --------------------------------------------------------------- */

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Private Function Declaration  ----------------------------------------------------------- */

/*---  Public Function Declaration  ------------------------------------------------------------ */

/*---  Private Data Definition  ---------------------------------------------------------------- */

static  struct clock_s self [1];
static  struct alarm_s self_alarm [1];

/*---  Public Data Definition  ----------------------------------------------------------------- */

/*---  Private Function Definition  ------------------------------------------------------------ */

/*---  Public Function Definition  ------------------------------------------------------------- */

/*---  Private Function Implementation  -------------------------------------------------------- */

/*---  Public Function Implementation  --------------------------------------------------------- */



clock_t ClockCreate(int tics_per_second){
    memset(self, 0, sizeof(self));
    memset(self_alarm, 0, sizeof(self_alarm));

    self->ticks_per_sec = tics_per_second;
    self->alarma = self_alarm;

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
        reloj->hora_actual[POSICION_UNI_SS] ++;
    }   

    // sumo decena segundos
    if (reloj->hora_actual[POSICION_UNI_SS] >= LIMITE_UNIDAD) {
        reloj->hora_actual[POSICION_UNI_SS] = 0;
        reloj->hora_actual[POSICION_DEC_SS] ++;
    }

    // sumo unidad minutos
    if (reloj->hora_actual[POSICION_DEC_SS] >= LIMITE_DECENA) {
        reloj->hora_actual[POSICION_DEC_SS] = 0;
        reloj->hora_actual[POSICION_UNI_MM] ++;
    }

    // sumo decena minutos
    if (reloj->hora_actual[POSICION_UNI_MM] >= LIMITE_UNIDAD) {
        reloj->hora_actual[POSICION_UNI_MM] = 0;
        reloj->hora_actual[POSICION_DEC_MM] ++;
    }

    // sumo unidad horas
    if (reloj->hora_actual[POSICION_DEC_MM] >= LIMITE_DECENA) {
        reloj->hora_actual[POSICION_DEC_MM] = 0;
        reloj->hora_actual[POSICION_UNI_HH] ++;
    }

    // sumo decena horas
    if (reloj->hora_actual[POSICION_UNI_HH] >= LIMITE_UNIDAD) {
        reloj->hora_actual[POSICION_UNI_HH] = 0;
        reloj->hora_actual[POSICION_DEC_HH] ++;
    }

    if ((reloj->hora_actual[POSICION_DEC_HH]) == 2 && reloj->hora_actual[POSICION_UNI_HH] == 4) {
        reloj->hora_actual[POSICION_DEC_HH] = 0;
        reloj->hora_actual[POSICION_UNI_HH] = 0;
    }
        
}




bool AlarmGetTime(clock_t reloj, uint8_t * alarm_time, int size){
    memcpy(alarm_time, reloj->alarma->hora_alarma, size);
    return reloj->alarma->active;
}

bool AlarmSetTime(clock_t reloj, const uint8_t * alarm_time, int size){
    memcpy(reloj->alarma->hora_alarma, alarm_time, size);
    reloj->alarma->active = true;
    return reloj->alarma->active;    
}

/*---  End of File  ---------------------------------------------------------------------------- */