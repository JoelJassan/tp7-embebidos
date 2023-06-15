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
        uint8_t hora_alarma_nueva[ALARM_SIZE];
        bool active;
        bool ringing;
        bool canceled;
};

struct clock_s {
    uint8_t hora_actual[CLOCK_SIZE];
    uint32_t ticks_per_sec;
    uint32_t current_tick;
    bool valida;

    struct alarm_s alarma [1];
};

/*---  Private Data Declaration  --------------------------------------------------------------- */

/*---  Public Data Declaration  ---------------------------------------------------------------- */

/*---  Private Function Declaration  ----------------------------------------------------------- */

/*---  Public Function Declaration  ------------------------------------------------------------ */

/*---  Private Data Definition  ---------------------------------------------------------------- */

static struct clock_s self [1];

/*---  Public Data Definition  ----------------------------------------------------------------- */

/*---  Private Function Definition  ------------------------------------------------------------ */

/*---  Public Function Definition  ------------------------------------------------------------- */

/*---  Private Function Implementation  -------------------------------------------------------- */

/*---  Public Function Implementation  --------------------------------------------------------- */



clock_t ClockCreate(int tics_per_second){
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
        TriggerAlarm(reloj);
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
    //return true;
}

bool AlarmSetTime(clock_t reloj, const uint8_t * alarm_time, int size){
    memcpy(reloj->alarma->hora_alarma, alarm_time, size);
    memcpy(reloj->alarma->hora_alarma_nueva, alarm_time, size);
    return reloj->alarma->active;
}

bool ActivateAlarm(clock_t reloj){
    reloj->alarma->active = true;
    return reloj->alarma->active;
}

bool DeactivateAlarm(clock_t reloj){
    reloj->alarma->active = false;
    reloj->alarma->ringing = false;
    return reloj->alarma->active;
}

bool TriggerAlarm(clock_t reloj){
    if (!memcmp(reloj->alarma->hora_alarma_nueva,reloj->hora_actual,ALARM_SIZE)){
        if (reloj->alarma->active == true)
            reloj->alarma->ringing = true;
    }
    
    return reloj->alarma->ringing;
}

bool PostponeAlarm(clock_t reloj){
    if (reloj->alarma->ringing == true){
        reloj->alarma->ringing = false;
        reloj->alarma->hora_alarma_nueva [POSICION_UNI_MM] += 1; // posterga 1 minuto
    }
    return reloj->alarma->ringing;
} //falta la logica para que la postergada tenga hora correcta

bool CancelAlarm(clock_t reloj){
    if (reloj->alarma->ringing == true){
        reloj->alarma->ringing = false;
        memcpy(reloj->alarma->hora_alarma_nueva, reloj->alarma->hora_alarma, ALARM_SIZE);
    }
    return true;
}
/*---  End of File  ---------------------------------------------------------------------------- */